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
        #пропускаем близкие точки
        while distance(curr_point, first) < leave_radius and curr_id < len(points) - 1:
            round_points.append(points[curr_id])
            curr_id += 1
            curr_point = points[curr_id]
            
        #идем пока не не вернемся достаточно близко
        while distance(curr_point, first) > comeback_radius and curr_id < len(points) - 1:
            round_points.append(points[curr_id])
            curr_id += 1
            curr_point = points[curr_id]
            
        #находим ближайшую в круге
        round_end_id = find_closest(points, curr_id, first)
        round_points.extend(points[curr_id : round_end_id + 1])
        rounds.append(round_points)
        curr_id = round_end_id + 1
       
        if curr_id >= len(points) - 1:
            break;
            
        curr_point = points[curr_id]
            
        
    return rounds

        
            
            
        
