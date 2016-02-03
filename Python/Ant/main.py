import random
import collections


class Point:
    def __init__(self):
        self.x = 0
        self.y = 0

    def __add__(self, other):
        p = Point
        p.x = self.x + other.x
        p.y = self.y + other.y
        return p

    def __sub__(self, other):
        p = Point
        p.x = self.x - other.x
        p.y = self.y - other.y
        return p




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
            while ant.move < 100:
                next_pos = self.world[ant.next_pos[0], ant.next_pos[1]]
                step = (abs(ant.next_pos[0] - ant.pos[1]), abs(ant.next_pos[1] - ant.pos[1]))

                if next_pos == 0:
                    ant.next_pos = ant.pos + step
                    self.current_state = ant.gen[self.current_state][0]
                else:
                    self.current_state = ant.gen[self.current_state][1]
                    ant.pos = ant.next_pos
                    ant.next_pos += step

                if ant.next_pos[0] >= 10:
                    ant.next_pos[0] = 10 - ant.next_pos[0]
                if ant.next_pos[1] >= 10:
                    ant.next_pos[1] = 10 - ant.next_pos[1]

                ant.move += 1

                if next_pos == 2:
                    ant.apple += 1
                if ant.apple >= self.apple:
                    ant.survival = ant.apple + (100 - ant.move)/100
                    break



class Ant:
    def __init__(self):
        self.gen = []
        self.first_state = 1
        self.current_state = 1
        self.survival = 0
        self.move = 0
        self.apple = 0
        self.pos = Point()
        self.next_pos = Point()

    def generate_gen(self):
        self.next_pos.x = 1
        self.first_state = random.randint(0, 6)
        self.current_state = self.first_state
        for state in range(7):
            true_state = random.randint(0, 7)
            false_state = random.randint(0, 7)
            while false_state == true_state:
                false_state = random.randint(0, 7)
            state_ant = [(0, true_state), (1, false_state)]
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

    q = Point()
    w = Point()

    q = q - w
    print(q.x)


if __name__ == '__main__':
    main()

__author__ = 'lisgein'
