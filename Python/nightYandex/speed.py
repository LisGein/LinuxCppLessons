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

__author__ = 'lisgein'
