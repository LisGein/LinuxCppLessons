class Context:
    def __init__(self, win_width, win_height, world_width, world_height):
        self._scale = min([float(win_width)/world_width, float(win_height)/world_height])

    def scale(self, point):
        return self._scale*point

__author__ = 'lisgein'
