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


def len_way(x1, y1, x2, y2):
    return math.pow(x2 - x1, 2) + math.pow(y2 - y1, 2)


def ways(x, y):
    ways_x = []
    ways_y = []
    idx_end = 0
    idx_start = 0
    end_round = False
    max_eps = 0.0002
    while 1:
        if idx_end + 3 >= len(x):
            ways_x.append(x[idx_start:len(x)])
            ways_y.append(y[idx_start:len(y)])
            break
        len_way_o = len_way(x[0], y[0], x[idx_end], y[idx_end])
        idx_end += 1
        len_way_s = len_way(x[0], y[0], x[idx_end], y[idx_end])
        idx_end += 1
        len_way_e = len_way(x[0], y[0], x[idx_end], y[idx_end])
        if end_round is False and len_way_o > max_eps and len_way_s > max_eps and len_way_e > max_eps:
            end_round = True
        elif end_round is True and len_way_o < max_eps and len_way_s < max_eps and len_way_e < max_eps:
            ways_x.append(x[idx_start:idx_end])
            ways_y.append(y[idx_start:idx_end])
            idx_start = idx_end
            end_round = False

    return ways_x, ways_y

__author__ = 'lisgein'
