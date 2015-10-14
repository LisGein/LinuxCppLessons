import math


def len_way(x1, y1, x2, y2):
    return math.pow(x2 - x1, 2) + math.pow(y2 - y1, 2)


def div_rounds(x, y, time):
    ways_x = []
    ways_y = []
    max_eps = 0.0001

    idx_end = 0
    while 1:
        idx_end += 1
        if idx_end >= len(x):
            idx_end = len(x) - 1
            break
        range_time = (time[idx_end] - time[0]).total_seconds()
        point_way = len_way(x[0], y[0], x[0], y[idx_end])
        if (range_time < 20*60) and point_way > max_eps:
            break
        elif idx_end >= len(x):
            idx_end = len(x)-1
            break

    idx_start = 0
    while 1:
        idx_end += 1
        if idx_end >= len(x):
            idx_end = len(x)-1
            ways_x.append(x[idx_start: idx_end])
            ways_y.append(y[idx_start: idx_end])
            break

        point_way = len_way(x[0], y[0], x[idx_end], y[idx_end])
        if point_way < max_eps:
            ways_x.append(x[idx_start: idx_end])
            ways_y.append(y[idx_start: idx_end])
            idx_start = idx_end
            while 1:
                idx_end += 1
                if idx_end >= len(x):
                    idx_end = len(x) - 1
                    break
                range_time = (time[idx_end] - time[idx_start]).total_seconds()

                point_way = len_way(x[0], y[0], x[idx_end], y[idx_end])
                if (range_time < 20*60) and point_way > max_eps:
                    break
                elif idx_end >= len(x):
                    idx_end = len(x)-1
                    break

    return ways_x, ways_y

__author__ = 'lisgein'
