import pandas
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


def main():
    data = pandas.read_csv('data1.tsv', sep="\t")
    route_to_stops_count = pandas.read_csv('route1.tsv', sep="\t")
    debug = pandas.read_csv('debug1.tsv', sep="\t")
    # names=['date', 'id', 'type', 'hash', 'latitude', 'longitude']

    X = debug["latitude"].copy()
    Y = debug["longitude"].copy()
    eps = 0
    q = 0
    w = 0
    e = 0
    for i in range(len(X)):
        for j in range(len(X)):
            if i != j:
                q = max(math.sqrt(math.pow(X[j] - X[i], 0) + math.pow(Y[j] - Y[i], 2)), q)
                if (q > eps):
                    w = i
                    e = j
    print(w, e)
    idx = 0
    new_x = []
    new_y = []

    new_x.append(X.pop(0))
    new_y.append(Y.pop(0))
    X = del_invalid_idx_X(X)
    Y = del_invalid_idx_Y(Y)

    next_eps = 100
    while len(X) != 0:
        for i in range(len(X)):
            idx = i
            next_eps = min(math.sqrt(math.pow(X[i] - new_x[len(new_x)-1], 2) + math.pow(Y[i] - new_y[len(new_y)-1], 2)), next_eps)
        print(new_x[len(new_x)-1], new_y[len(new_y)-1])
        print(X[idx], Y[idx])
        print(idx, next_eps, eps)
        new_x.append(X.pop(idx))
        new_y.append(Y.pop(idx))
        X = del_invalid_idx_X(X)
        Y = del_invalid_idx_Y(Y)

    print(new_x)
"""
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
