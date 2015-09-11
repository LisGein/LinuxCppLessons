#-*- coding: utf-8 -*-
import pygame
import sys
import planet
import resize


class SolarSystem:
    def __init__(self, width_app, height_app):
        self.max_scale_ = 227900000
        self.width_ = width_app
        self.height_ = height_app
        self.sun_ = planet.Planet(width_app, height_app)
        self.mercury_ = planet.Planet(width_app, height_app)
        self.resize_ = resize.Resize(self.max_scale_, self.height_)
        # /self.max_scale_*self.height_

        self.background_img_ = pygame.image.load("fon.jpg")
        self.background_img_.convert()
        self.mercury_img_ = pygame.image.load("mercury.png")
        self.mercury_img_.convert()
        self.sun_img_ = pygame.image.load("sun.png")
        self.sun_img_.convert()

    def calc_data(self):
        # for sun:
        self.sun_.set_mass(1.9891*pow(10, 30))
        self.sun_.set_distance_to_sun(0)
        self.sun_.set_diam(1000000)
        # self.resize_.image("sun.png", self.resize_.coordinates(self.sun_.diam_/2))

        # for mercury:
        self.mercury_.set_mass(3.33022*pow(10, 23))
        self.mercury_.set_distance_to_sun(self.resize_.coordinates(self.sun_.diam_/2+self.sun_.get_diam()/2+57910000))
        self.mercury_.set_diam(4879.4)
        # self.resize_.image("mercury_.png", self.resize_.coordinates(self.mercury_.diam_/2))
        print(self.resize_.coordinates(self.mercury_.diam_)) # Солнце размера == 1

    def draw(self, screen):
        screen.blit(self.background_img_, (0, 0))
        screen.blit(self.mercury_img_, self.mercury_.get_pos())
        screen.blit(self.sun_img_, self.sun_.get_pos())

__author__ = 'lisgein'
