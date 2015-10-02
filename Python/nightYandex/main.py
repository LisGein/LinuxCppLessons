import pandas
import math

data = pandas.read_csv('data1.tsv', sep="\t")
route_to_stops_count = pandas.read_csv('route1.tsv', sep="\t")
debug = pandas.read_csv('debug1.tsv', sep="\t")
# names=['date', 'id', 'type', 'hash', 'latitude', 'longitude']


X = debug["latitude"].copy()
Y = debug["longitude"].copy()

#X = [1, 3, 6, 8, 20]
#Y = [0, 4, 6, 7, 10]
eps = 0
for i in range(len(X) - 1):
    eps = max(math.sqrt(math.pow(X[i+1] - X[i], 2) + math.pow(Y[i+1] - Y[i], 2)), eps)

min_eps = 200
for i in range(len(X) - 1):
    min_eps = min(math.sqrt(math.pow(X[i+1] - X[i], 2) + math.pow(Y[i+1] - Y[i], 2)), min_eps)

mass = [(X, Y)]
x = 0
y = 0
idx = 0
while (min_eps < eps):
    new_mass = []
    for i in range(len(mass)):
        array_len = len(mass[i][0])
        if array_len > 2: #если больше дух точек в массиве
            X_f = []
            Y_f = []
            X_s = []
            Y_s = []
            half = array_len/2
            for f in range(array_len):
                if (f < half):
                    X_f.append(mass[i][0][f])
                    Y_f.append(mass[i][1][f])
                else:
                    X_s.append(mass[i][0][f])
                    Y_s.append(mass[i][1][f])
            pow_x = math.pow(abs(X_f[len(X_f)-1] - X_f[0]), 2)
            pow_Y = math.pow(abs(Y_f[len(Y_f)-1] - Y_f[0]), 2)
            swap_x = math.sqrt(pow_x + pow_Y)
            if (swap_x <= eps):#если расстояние между последними точками меньше eps, то оставляем только последние точки
                X_new = [X_f[0], X_f[len(X_f)-1]]
                Y_new = [Y_f[0], Y_f[len(Y_f)-1]]
                new_mass.append((X_new, Y_new))
                new_mass.append((X_s, Y_s))
            else:#иначе делим на 2 новых массива
                for j in range(len(mass)):
                    if (j == i):
                        new_mass.append((X_f, Y_f))
                        new_mass.append((X_s, Y_s))
                    else:
                        new_mass.append(mass[j])
        else:#иначе не трогаем этот массив
            new_mass.append(mass[i])
    mass = new_mass
    min_eps = eps
    max_len = 0
    for e in new_mass:
        max_len = max(len(e), max_len)
        X = e[0]
        Y = e[1]
        for r in range(len(X) - 1):
            min_eps = min(math.sqrt(math.pow(X[r+1] - X[r], 2) + math.pow(Y[r+1] - Y[r], 2)), min_eps)
    if max_len <= 2:
        break
mass = []
for e in new_mass:
    X = e[0]
    Y = e[1]
    for z in range(len(e[0])):
        mass.append((X[z], Y[z]))
__author__ = 'lisgein'
