import Image


class Resize:
    def __init__(self, max_scale, height):
        self.max_scale_ = max_scale
        self.height_ = height

    def image(self, name, width_resize):
        image_file = Image.open("fon.jpg")
        image_file.thumbnail((width_resize, width_resize))
        image_file.save(name)

    def coordinates(self, point):
        return float(point)/self.max_scale_*self.height_

__author__ = 'lisgein'