import random
import collections

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
                        mutation = random.randint(0, 10)
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
                turn_state = 0
                if next_pos != 0:
                    turn_state = 1
                    ant.apple += 1

                state = ant.gen[self.current_state][turn_state]
                if state == 0:
                    step = (abs(ant.next_pos[0] - ant.pos[1]), abs(ant.next_pos[1] - ant.pos[1]))
                    ant.pos = ant.next_pos
                    ant.next_pos += step

                    if ant.next_pos[0] >= 10:
                       ant.next_pos[0] = 10 - ant.next_pos[0]
                    if ant.next_pos[1] >= 10:
                       ant.next_pos[1] = 10 - ant.next_pos[1]
                else:
                    if step[0] != 0:
                        ant.next_pos[1] = step[0]
                        ant.next_pos[0] = 0

                    else:
                        ant.next_pos[0] = step[1]*(-1)
                        ant.next_pos[1] = 0

                ant.move += 1
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
        self.pos = (0, 0)
        self.next_pos = (1, 0)

    def generate_gen(self):
        self.first_state = random.randint(0, 6)
        self.current_state = self.first_state
        for state in range(7):
            turn_true = random.randint(0, 1)
            true_state = random.randint(0, 7)
            if turn_true == 0:
                turn_false = 1
            else:
                turn_false = 0
            false_state = random.randint(0, 7)
            while false_state == true_state:
                false_state = random.randint(0, 7)
            state_ant = [(turn_true, true_state), (turn_false, false_state)]
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


if __name__ == '__main__':
    main()

__author__ = 'lisgein'
