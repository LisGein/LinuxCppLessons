import pandas
import math
import datetime
import sort_coordinates
import rounds
from speed import find_speed



def main():
    data = pandas.read_csv('data1.tsv', sep="\t")
    id_unique = data["id"].unique()
    timestamps = []
    lat_points = []
    lon_points = []
    format_date = "%Y-%m-%d %H:%M:%S"

    for i in id_unique:
        str_date = data[data["id"] == i]["date"].copy()
        datepstr = []
        for s in str_date:
            t = datetime.datetime.strptime(s, format_date)
            datepstr.append(t)
        timestamps.append(datepstr)
        lat = sort_coordinates.del_invalid_idx(data[data["id"] == i]["latitude"].copy())
        lat_points.append(lat)
        lon = sort_coordinates.del_invalid_idx(data[data["id"] == i]["longitude"].copy())
        lon_points.append(lon)
    lat = []
    lon = []
    times = []
    for i in range(len(lon_points)):
        x, y, time = rounds.div_rounds(lat_points[i], lon_points[i], timestamps[i])
        for idx in range(len(x)):
            lat.append(x[idx])
            lon.append(y[idx])
            times.append(time[idx])

    len_data_round = len(lat)

    speeds = []
    for i in range(len(lat) - 1):
        speeds.append(find_speed(lat[i], lon[i], times[i]))

    points_x = []
    points_y = []
    speed_points = []
    for i in range(len(lat) - 1):
        point_x, point_y, speed = rounds.min_speed_points(lat[i], lon[i], speeds[i])
        points_x.extend(point_x)
        points_y.extend(point_y)
        speed_points.extend(speed)


if __name__ == "__main__":
    main()

__author__ = 'lisgein'
