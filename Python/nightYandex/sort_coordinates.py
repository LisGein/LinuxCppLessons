import math


def del_invalid_idx(old_array):
    x = []
    for i in old_array:
        x.append(i)
    return x


def sort_coordinates(x, y):
    new_x = [(x.pop(0))]
    new_y = [(y.pop(0))]
    x = del_invalid_idx(x)
    y = del_invalid_idx(y)
    while len(x) != 0:
        idx = 0
        next_eps = 100
        for i in range(len(x)):#поиск минимально удалёной точки в массиве
            min_eps = math.sqrt(math.pow(x[i] - new_x[len(new_x)-1], 2) + math.pow(y[i] - new_y[len(new_y)-1], 2))
            if min_eps < next_eps:
                next_eps = min_eps
                idx = i
        new_x.append(x.pop(idx))
        new_y.append(y.pop(idx))
        x = del_invalid_idx(x)
        y = del_invalid_idx(y)
    array_coordinates = [new_x, new_y]
    return array_coordinates

__author__ = 'lisgein'
