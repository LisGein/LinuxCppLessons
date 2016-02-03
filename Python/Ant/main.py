import random
import collections


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        x = self.x + other.x
        y = self.y + other.y
        if x >= 10:
            x = 10 - x
        if y >= 10:
            y = 10 - y
        return Point(x, y)

    def __sub__(self, other):
        x = self.x - other.x
        y = self.y - other.y
        if x < 0:
            x += 10
        if y < 0:
            y += 10
        return Point(x, y)

    def check_max(self, coor):
        if coor > 1:
            coor = -1
        if coor < -1:
            coor = 1
        return coor

    def turn_right(self, prev_point):
        print("turn_right")
        print(prev_point.x, prev_point.y)
        print(self.x, self.y)
        turn_now = self - prev_point
        print(turn_now.x, turn_now.y)
        if turn_now.y != 0:
            turn_now.y = self.check_max(turn_now.y)
            print("turn_now.y", turn_now.y)
            self.x = turn_now.y * (-1) + prev_point.x
            print("self.x", self.x)
            self.y = prev_point.y
        else:
            turn_now.x = self.check_max(turn_now.x)
            self.x = prev_point.x
            self.y = turn_now.x + prev_point.y
        print(self.x, self.y)
        return self





class Grid:
    def __init__(self):
        self.world = [[0, 2, 2, 2, 2, 0, 0, 0, 0, 0],
                      [0, 0, 0, 0, 2, 0, 0, 0, 0, 0],
                      [2, 2, 2, 0, 2, 0, 2, 0, 1, 2],
                      [0, 0, 2, 2, 2, 0, 1, 0, 2, 0],
                      [0, 0, 0, 0, 0, 0, 2, 0, 2, 0],
                      [0, 0, 2, 2, 1, 1, 2, 0, 2, 0],
                      [0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
                      [0, 0, 2, 0, 0, 1, 2, 2, 1, 0],
                      [0, 0, 2, 0, 0, 2, 0, 0, 0, 0],
                      [0, 0, 1, 1, 2, 1, 0, 0, 0, 0]]
        self.ants = []
        self.apple = 0

    def sort_ants(self):
        d = {}
        for ant in self.ants:
            d[ant] = ant.survival
        od = collections.OrderedDict(sorted(d.items(), key=lambda x: x[1]))
        self.ants = [od[i][0] for i in range(od)]

    def new_gen(self):
        new_ants = []
        for father in self.ants:
            for mother in self.ants:
                if father != mother:
                    separator = random.randint(1, 6)
                    ant_boy = Ant()
                    ant_girl = Ant()
                    for state in range(7):
                        # mutation = random.randint(0, 10)
                        if state < separator:
                            ant_boy.gen.append(father.gen[state])
                            ant_girl.gen.append(mother.gen[state])
                        else:
                            ant_boy.gen.append(mother.gen[state])
                            ant_girl.gen.append(father.gen[state])
                    new_ants.append(ant_boy, ant_girl)

    def test_ants(self):
        for ant in self.ants:
            world_ant = self.world
            while ant.move < 100:
                cell = ant.next_pos
                next_pos = world_ant[cell.y][cell.x]
                step = ant.next_pos - ant.pos

                if next_pos == 0:
                    if ant.gen[ant.current_state][0][0] == 0:
                        ant.pos = ant.next_pos
                        ant.next_pos = ant.next_pos + step
                    else:
                        ant.next_pos = ant.next_pos.turn_right(ant.pos)
                    ant.current_state = ant.gen[ant.current_state][0][1]
                else:
                    ant.current_state = ant.gen[ant.current_state][1][1]
                    ant.pos = ant.next_pos
                    ant.next_pos = ant.next_pos + step


                ant.move += 1
                if next_pos == 2:
                    ant.apple += 1
                world_ant[cell.y][cell.x] = 0
                if ant.apple >= self.apple:
                    break
            ant.survival = ant.apple + (100 - ant.move)/100
            print(ant.survival)


class Ant:
    def __init__(self):
        self.gen = []
        self.first_state = 1
        self.current_state = 1
        self.survival = 0
        self.move = 0
        self.apple = 0
        self.pos = Point(0, 0)
        self.next_pos = Point(1, 0)

    def generate_gen(self):
        self.first_state = random.randint(0, 6)
        self.current_state = self.first_state
        for state in range(7):
            true_state = random.randint(0, 6)
            false_state = random.randint(0, 6)
            while false_state == true_state:
                false_state = random.randint(0, 6)
            false_turn = random.randint(0, 1)
            state_ant = [(false_turn, false_state), (0, true_state)]
            self.gen.append(state_ant)


def main():
    grid = Grid()
    for i in range(10):
        ant = Ant()
        ant.generate_gen()
        grid.ants.append(ant)

    for row in grid.world:
        for column in row:
            if column == 2:
                grid.apple += 1



    ant = Ant()
    ant.generate_gen()
    grid.ants.append(ant)
    ant_next = Ant()
    ant_next.generate_gen()
    grid.ants.append(ant_next)

    grid.test_ants()

if __name__ == '__main__':
    main()

__author__ = 'lisgein'
