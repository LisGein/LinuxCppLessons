import pandas
import math
import datetime
import sort_coordinates
import rounds



def main():
    data = pandas.read_csv('data1.tsv', sep="\t")
    id_unique = data["id"].unique()
    date_points = []
    lat_points = []
    lon_points = []
    format_date = "%Y-%m-%d %H:%M:%S"

    for i in id_unique:
        str_date = data[data["id"] == i]["date"].copy()
        datepstr = []
        for s in str_date:
            t = datetime.datetime.strptime(s, format_date)
            datepstr.append(t)
        date_points.append(datepstr)
        lat = sort_coordinates.del_invalid_idx(data[data["id"] == i]["latitude"].copy())
        lat_points.append(lat)
        lon = sort_coordinates.del_invalid_idx(data[data["id"] == i]["longitude"].copy())
        lon_points.append(lon)
    lat = []
    lon = []
    for i in range(len(lon_points)):
        x, y = rounds.div_rounds(lat_points[i], lon_points[i], date_points[i])
        for idx in range(len(x)):
            lat.append(x[idx])
            lon.append(y[idx])

if __name__ == "__main__":
    main()

__author__ = 'lisgein'
