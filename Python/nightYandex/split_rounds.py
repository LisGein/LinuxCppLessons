def distance(a, b):
    return ((b[0] - a[0]) ** 2 + (b[1] - a[1]) ** 2) ** 0.5

comeback_radius = 0.02
leave_radius = 0.04


def find_closest(points, id_from, first):
    curr_point = points[id_from]
    curr_id = id_from
    min_dist = distance(curr_point, first)
    round_end_id = id_from

    while distance(curr_point, first) < leave_radius and curr_id < len(points) - 1:
        curr_id += 1
        curr_point = points[curr_id]
        curr_dist = distance(curr_point, first)
        if curr_dist < min_dist:
                min_dist = curr_dist
                round_end_id = curr_id
        
    return round_end_id
        
        
def split_rounds(xs, ys, timestamps):
    points = list(zip(xs, ys, timestamps))
    rounds = []

    curr_point = points[0]
    curr_id = 0
    first = curr_point
    
    while True:
        round_points = []
        # пропускаем близкие точки
        while distance(curr_point, first) < leave_radius and curr_id < len(points) - 1:
            round_points.append(points[curr_id])
            curr_id += 1
            curr_point = points[curr_id]
            
        # идем пока не не вернемся достаточно близко
        while distance(curr_point, first) > comeback_radius and curr_id < len(points) - 1:
            round_points.append(points[curr_id])
            curr_id += 1
            curr_point = points[curr_id]
            
        # находим ближайшую в круге
        round_end_id = find_closest(points, curr_id, first)
        round_points.extend(points[curr_id : round_end_id + 1])
        rounds.append(round_points)
        curr_id = round_end_id + 1
       
        if curr_id >= len(points) - 1:
            break
            
        curr_point = points[curr_id]

    return rounds


def mean_stay(rounds):
    mean_stays = sum(map(len, rounds), 0.) / len(rounds)
    eps = int(mean_stays/2)

    mean_stays_rounds = []
    for i in rounds:
        if mean_stays - eps < len(i) < mean_stays + eps:
            mean_stays_rounds.append(i)
    return mean_stays_rounds


def distance_line(point, line):
    a = [line[0][0] - point[0], line[0][1] - point[1]]
    b = [line[1][0] - point[0], line[1][1] - point[1]]
    return distance(a, b)/distance([point[0], line[0][0]], [point[1], line[0][1]])


def filter_rounds_by_len(start_point, lines):
    len_way = 0
    ways = []
    for i in lines:
        len_way += distance(start_point, i[0])
        ways.append([len_way, i])
        len_way += distance(i[0], i[1])
        start_point = i[1]

    return ways