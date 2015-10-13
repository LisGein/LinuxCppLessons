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


def div_way(x, y):
    ways_x = []
    ways_y = []

    max_eps = 0.005
    f_point = 0
    for j in range(len(x) - 6):
        idx = f_point+j+2
        if idx + 3 >= len(x):
            idx = len(x)
            print(idx, len(x))
            ways_x.append(x[f_point:idx])
            ways_y.append(y[f_point:idx])
            break
        else:
            way_f = len_way(x[0], y[0], x[idx], y[idx])
            idx += 1
            way_s = len_way(x[0], y[0], x[idx], y[idx])
            idx += 1
            way_t = len_way(x[0], y[0], x[idx], y[idx])
            if way_f > max_eps and way_s > max_eps and way_t > max_eps:
                while 1:
                    idx += 1
                    if idx == len(x):
                        idx -= 1
                        break
                    way_next = len_way(x[0], y[0], x[idx], y[idx])
                    if way_next < max_eps:
                        idx += 1
                        if idx == len(x):
                            idx -= 1

                        break

                idx += 1
                ways_x.append(x[f_point:idx])
                ways_y.append(y[f_point:idx])
                f_point = idx
                print(idx, len(x))
                if f_point + j + 6 >= len(x):
                    break
    return [ways_x, ways_y]


__author__ = 'lisgein'
