import random
import collections


def check_max(x):
    if x >= 10:
        x = x % 10
    elif x < 0:
        x = 10 - abs(x%10)
    return x

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        x = check_max(self.x + other.x)
        y = check_max(self.y + other.y)
        return Point(x, y)

    def __sub__(self, other):
        x = check_max(self.x - other.x)
        y = check_max(self.y - other.y)
        return Point(x, y)

    def turn_right(self):
        if self.x == 0:
            self.y = -1*self.x
            self.x = 0
        else:
            self.y = self.x
            self.x = 0
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
                    separator = random.randint(1, 5)
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
                    new_ants.append(ant_boy)
                    new_ants.append(ant_girl)
        self.ants = new_ants
        print("new ants")

    def move(self):
        for ant in self.ants:
            world_ant = self.world
            while ant.move < 200:
                cell = ant.pos + ant.speed
                next_cell = world_ant[cell.y][cell.x]
                if next_cell == 2:
                    ant.current_state = ant.gen[ant.current_state][1][1]
                    ant.pos = cell
                    ant.apple += 1
                else:
                    #if ant.gen[ant.current_state][0][0] == 0:
                        #ant.pos = cell
                    #else:
                    ant.speed.turn_right()
                    ant.current_state = ant.gen[ant.current_state][0][1]
                ant.survival = ant.apple + (200 - ant.move)/200
                ant.move += 1
                world_ant[cell.y][cell.x] = 0
                if ant.apple >= self.apple:
                    break
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
        self.speed = Point(1, 0)

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
    for i in range(10):
        grid.move()
        grid.new_gen()

if __name__ == '__main__':
    main()

__author__ = 'lisgein'
