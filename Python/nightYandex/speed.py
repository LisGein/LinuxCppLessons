import math


def find_speed(x, y, date_points):
    speed = []
    for i in range(len(x) - 1):
        range_way = math.sqrt(math.pow(x[i+1] - x[i], 2)
                              + math.pow(y[i+1] - y[i], 2))
        range_time = (date_points[i + 1] - date_points[i]).total_seconds()
        speed.append(range_way/range_time)
    return speed


def sort_coor(lat_points, lon_points, speed):
    sort_speed = []
    idx = 0

    sort_lat = []
    sort_lon = []
    for i in range(len(speed)-1):
        temp_lat_points = lat_points[i]
        temp_lon_points = lon_points[i]
        lat = []
        lon = []
        sp = []
        temp_speed_array = speed[i].copy()
        while len(temp_speed_array) != 0:
            min_speed = 100000
            for i in range(len(temp_speed_array)-1):
                if min_speed > temp_speed_array[i]:
                    min_speed = temp_speed_array[i]
                    idx = i
            sp.append((idx, temp_speed_array.pop(idx)))
            lat.append((temp_lat_points.pop(idx), temp_lat_points[idx]))
            lon.append((temp_lon_points.pop(idx), temp_lon_points[idx]))
        sort_lat.append(lat)
        sort_lon.append(lon)
        sort_speed.append(sp)


def mean_speed(speed, mean_stays_rounds):
    mean_speeds = 0
    for i in speed:
        mean_speed = 0
        for j in i:
            mean_speed += j
        mean_speeds += mean_speed/len(i)
    mean_speeds /= len(speed)
    eps = (mean_speeds/2)

    mean_speeds_rounds = []
    for i in range(len(speed) - 1):
        round_mean = []
        for j in range(len(speed[i]) - 1):
            if mean_speeds - eps < speed[i][j] < mean_speeds + eps:
                round_mean.append((mean_stays_rounds[i][j], mean_stays_rounds[i][j+1], speed[i][j]))
        if len(round_mean) > 0:
            mean_speeds_rounds.append(round_mean)

    return mean_speeds_rounds


__author__ = 'lisgein'
