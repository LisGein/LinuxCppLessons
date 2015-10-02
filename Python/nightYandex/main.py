import pandas
import math

data = pandas.read_csv('data1.tsv', sep="\t")
route_to_stops_count = pandas.read_csv('route1.tsv', sep="\t")
debug = pandas.read_csv('debug1.tsv', sep="\t")
# names=['date', 'id', 'type', 'hash', 'latitude', 'longitude']


X = debug["latitude"].copy()
Y = debug["longitude"].copy()

mass = [(X, Y)]

new_mass_f = []
for i in range(len(mass)):
    X = mass[i][0]
    Y = mass[i][1]
    for j in range(len(X)):
        if len(new_mass_f) > 0:
            if (new_mass_f[len(new_mass_f)-1][0] != X[j]) or (new_mass_f[len(new_mass_f)-1][1]!=Y[j]):
                new_mass_f.append((X[j],Y[j]))
            else:
                print(new_mass_f[len(new_mass_f)-1][0], X[j])
                print(new_mass_f[len(new_mass_f)-1][1], Y[j])
        else:
            new_mass_f.append((X[j],Y[j]))
new_mass = []
X = []
Y = []
for i in range(len(new_mass_f)):
    X.append(new_mass_f[i][0])
    Y.append(new_mass_f[i][1])

mass = [(X, Y)]
eps = 0
for i in range(len(X) - 1):
    eps = max(math.sqrt(math.pow(X[i+1] - X[i], 2) + math.pow(Y[i+1] - Y[i], 2)), eps)

min_eps = 200
for i in range(len(X) - 1):
    min_eps = min(math.sqrt(math.pow(X[i+1] - X[i], 2) + math.pow(Y[i+1] - Y[i], 2)), min_eps)


while (min_eps < eps):
    new_mass = []
    for i in range(len(mass)):
        array_len = len(mass[i][0])
        if array_len > 3: #если больше двух точек в массиве
            X_f = []
            Y_f = []
            X_s = []
            Y_s = []
            half = array_len/2
            for f in range(array_len):
                if (f < half):
                    X_f.append(mass[i][0][f])
                    Y_f.append(mass[i][1][f])
                elif (f == half):
                    X_f.append(mass[i][0][f])
                    Y_f.append(mass[i][1][f])
                    X_s.append(mass[i][0][f])
                    Y_s.append(mass[i][1][f])
                else:
                    X_s.append(mass[i][0][f])
                    Y_s.append(mass[i][1][f])
            pow_x = math.pow(abs(X_f[len(X_f)-1] - X_f[0]), 2)
            pow_Y = math.pow(abs(Y_f[len(Y_f)-1] - Y_f[0]), 2)
            swap_x = math.sqrt(pow_x + pow_Y)
            if (swap_x <= eps):#если расстояние между крайними точками меньше eps, то оставляем только последние точки
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
    max_size = 0
    for i in range(len(new_mass[0])):
        for j in range(len(new_mass[i][0])):
            max_size = max(len(new_mass[i][0]), max_size)
    if max_size > 2:
        mass = new_mass
    else:
        new_mass_f = []
        for i in range(len(new_mass)):
            X = new_mass[i][0]
            Y = new_mass[i][1]
            for j in range(len(X)):
                if len(new_mass_f) > 0:
                    if (new_mass_f[len(new_mass_f)-1][0] != X[j]) or (new_mass_f[len(new_mass_f)-1][1]!=Y[j]):
                        new_mass_f.append((X[j],Y[j]))
                else:
                    new_mass_f.append((X[j],Y[j]))
        X = []
        Y = []
        for i in range(len(new_mass_f)):
            X.append(new_mass_f[i][0])
            Y.append(new_mass_f[i][1])
        mass = [(X, Y)]
        print(len(mass[0][0]), "end\n")
        min_eps = eps
        break
print(mass)


__author__ = 'lisgein'
