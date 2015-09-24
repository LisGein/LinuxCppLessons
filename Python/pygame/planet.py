class Planet:
    def __init__(self, width_app, height_app):
        self.speed_ = 0
        self.start_pos = (width_app/2, 0)
        self.width_app_ = width_app
        self.height_app_ = height_app

    def set_mass(self, mass):
        self.mass_ = mass

    def set_diam(self, diam):
        self.diam_ = diam

    def set_distance_to_sun(self, distance_to_sun):
        self.distance_to_sun_ = distance_to_sun
        self.start_pos = (self.width_app_/2, self.height_app_/2+distance_to_sun)

    def get_diam(self):
        return self.diam_

    def get_pos(self):
        return self.start_pos


__author__ = 'lisgein'
