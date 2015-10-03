import pandas
import sort_coordinates
import math
import re
import time
from time import gmtime, strftime

def del_invalid_idx_X(X):
    x =[]
    for i in X:
        x.append(i)
    return x

def del_invalid_idx_Y(Y):
    x =[]
    for i in Y:
        x.append(i)
    return x

def find_round(X, Y, new_x, new_y):
    route_x = []
    route_y = []
    back_route_x = []
    back_route_y = []
    idx_item = 0
    for j in range(len(new_x)):
        if (new_x[j] == X[0]) and (new_y[j] == Y[0]):
            idx_item = j
    x = []
    y = []
    for j in range(len(new_x)-idx_item-1):
        x.append(new_x[j+idx_item+1])
        y.append(new_y[j+idx_item+1])
    new_x = x
    new_y = y
    route_x.append(X[0])
    route_y.append(Y[0])

    for i in range(len(X)):
        if (len(new_x) != 0):
            idx_item = 0
            for j in range(len(new_x)):
                if (new_x[j] == X[i]) and (new_y[j] == Y[i]):
                    idx_item = j
            x = []
            y = []
            for j in range(len(new_x)-idx_item-1):
                x.append(new_x[j+idx_item+1])
                y.append(new_y[j+idx_item+1])
            new_x = x
            new_y = y
            route_x.append(X[i])
            route_y.append(Y[i])
        else:
            break
            back_route_x.append(X[i])
            back_route_y.append(Y[i])


def sort_coordinates(X, Y):
    new_x = [(X.pop(0))]
    new_y = [(Y.pop(0))]
    X = del_invalid_idx_X(X)
    Y = del_invalid_idx_X(Y)
    idx = 0
    while len(X) != 0:
        next_eps = 100
        for i in range(len(X)):#поиск минимально удалёной точки в массиве
            min_eps = math.sqrt(math.pow(X[i] - new_x[len(new_x)-1], 2) + math.pow(Y[i] - new_y[len(new_y)-1], 2))
            if (min_eps < next_eps):
                next_eps = min_eps
                idx = i
        new_x.append(X.pop(idx))
        new_y.append(Y.pop(idx))
        X = del_invalid_idx_X(X)
        Y = del_invalid_idx_X(Y)
    array_coor = [new_x, new_y]
    return array_coor

def main():
    data = pandas.read_csv('data1.tsv', sep="\t")
    route_to_stops_count = pandas.read_csv('route1.tsv', sep="\t")
    debug = pandas.read_csv('debug1.tsv', sep="\t")
    # names=['date', 'id', 'type', 'hash', 'latitude', 'longitude']
    X = data["latitude"].copy()
    Y = data["longitude"].copy()
    eps = 0
    for i in range(len(X) - 1):
        eps = max(math.sqrt(math.pow(X[i+1] - X[i], 2) + math.pow(Y[i+1] - Y[i], 2)), eps)
    print(len(sort_coordinates(X, Y)))




"""
    q = time.strptime("12:34:54", "%H:%M:%S")
    w = time.strptime("2:54:54", "%H:%M:%S")
    print(q.tm_hour - w.tm_hour)
    data = pandas.read_csv('data1.tsv', sep="\t")
    route_to_stops_count = pandas.read_csv('route1.tsv', sep="\t")
    debug = pandas.read_csv('debug1.tsv', sep="\t")
    # names=['date', 'id', 'type', 'hash', 'latitude', 'longitude']

    X = debug["latitude"].copy()
    Y = debug["longitude"].copy()
    new_x = [(X.pop(0))]
    new_y = [(Y.pop(0))]

    x = []
    for i in X:
        x.append(i)
    X = x
    y = []
    for i in Y:
        y.append(i)
    Y = y

    while len(X) != 0:
        next_eps = 100
        for i in range(len(X)):
            min_eps = math.sqrt(math.pow(X[i] - new_x[len(new_x)-1], 2) + math.pow(Y[i] - new_y[len(new_y)-1], 2))
            if (min_eps < next_eps):
                next_eps = min_eps
                idx = i
        new_x.append(X.pop(idx))
        new_y.append(Y.pop(idx))
        x =[]
        for i in X:
            x.append(i)
        X = x
        y =[]
        for i in Y:
            y.append(i)
        Y = y

    route_x = []
    route_y = []
    back_route_x = []
    back_route_y = []
    X = debug["latitude"].copy()
    Y = debug["longitude"].copy()
    idx_item = 0
    for j in range(len(new_x)):
        if (new_x[j] == X[0]) and (new_y[j] == Y[0]):
            idx_item = j
    x = []
    y = []
    for j in range(len(new_x)-idx_item-1):
        x.append(new_x[j+idx_item+1])
        y.append(new_y[j+idx_item+1])
    new_x = x
    new_y = y
    route_x.append(X[0])
    route_y.append(Y[0])

    for i in range(len(X)):
        if (len(new_x) != 0):
            idx_item = 0
            for j in range(len(new_x)):
                if (new_x[j] == X[i]) and (new_y[j] == Y[i]):
                    idx_item = j
            x = []
            y = []
            for j in range(len(new_x)-idx_item-1):
                x.append(new_x[j+idx_item+1])
                y.append(new_y[j+idx_item+1])
            new_x = x
            new_y = y
            route_x.append(X[i])
            route_y.append(Y[i])
        else:
            back_route_x.append(X[i])
            back_route_y.append(Y[i])
    #
    eps = 0
    for i in range(len(route_x) - 1):
        eps = max(math.sqrt(math.pow(route_x[i+1] - route_x[i], 2) + math.pow(route_y[i+1] - route_y[i], 2)), eps)

    new_route_x = [route_x[0]]
    new_route_y = [route_y[0]]
    for i in range(len(route_x)-1):
        dist = math.sqrt(math.pow(route_x[i+1] - new_route_x[len(new_route_x)-1], 2) +
                         math.pow(route_y[i+1] - new_route_y[len(new_route_y)-1], 2))
        if dist >= eps:
            new_route_x.append(route_x[i+1])
            new_route_y.append(route_y[i+1])

eps = 0
idx = 0
for i in range(len(X) - 1):
    idx = i
    eps = max(math.sqrt(math.pow(X[i+1] - X[i], 2) + math.pow(Y[i+1] - Y[i], 2)), eps)
print(idx)

coor = []
for i in range(len(c_array[0][0])-3):
    dist = math.sqrt(math.pow(c_array[0][0][len(c_array[0][0]) - i-3] - c_array[0][0][0], 2)
                         + math.pow(c_array[0][1][len(c_array[0][0]) - i-3] - c_array[0][1][0], 2))
    if (dist <= eps):
        l_array = []
        r_array = []
        for f in range(len(c_array[0][0])-3):
            if f < (len(c_array[0][0]) - i-2):
                l_array.append((c_array[0][0][f], c_array[0][1][f]))
            else:
                r_array.append((c_array[0][0][f], c_array[0][1][f]))

        coor.append(l_array)
        coor.append(r_array)
print(coor)





import pandas
import math

def break_array(c_array, eps):
    new_coor = []
    for i in range(len(c_array[0])-1):
        dist = math.sqrt(math.pow(c_array[0][len(c_array) - i-1] - c_array[0][0], 2)
                         + math.pow(c_array[1][len(c_array) - i-1] - c_array[1][0], 2))
        if (dist <= eps):
            l_array = []
            r_array = []
            for f in range(i):
                l_array.append(c_array[f])
            for f in range(c_array):
                r_array.append(c_array[f])

            new_coor.append(l_array)
            new_coor.append(r_array)
            return new_coor
    new_coor = [c_array]
    return new_coor



def main():
    data = pandas.read_csv('data1.tsv', sep="\t")
    route_to_stops_count = pandas.read_csv('route1.tsv', sep="\t")
    debug = pandas.read_csv('debug1.tsv', sep="\t")
    # names=['date', 'id', 'type', 'hash', 'latitude', 'longitude']


    X = debug["latitude"].copy()
    Y = debug["longitude"].copy()

    c_array = []
    c_array.append((X, Y))

    eps = 0
    for i in range(len(X) - 1):
        eps = max(math.sqrt(math.pow(X[i+1] - X[i], 2) + math.pow(Y[i+1] - Y[i], 2)), eps)

    coor = break_array(c_array[0], eps)
    print(coor)
    c_array = coor[1]
    dist = math.sqrt(math.pow(c_array[c_array.size()-1].first - c_array[0].first , 2) + math.pow(c_array[c_array.size()-1].second - c_array[0].second, 2))
    new_coor = []
    while (dist > eps):
        new_coor.push_back(coor[0])
        coor = break_array(coor[1], eps)
        c_array = coor[1]
        dist = math.sqrt(math.pow(c_array[c_array.size()-1].first - c_array[0].first , 2) + math.pow(c_array[c_array.size()-1].second - c_array[0].second, 2))

    print(new_coor)

"""
if __name__ == "__main__":
    main()

__author__ = 'lisgein'
