#-*- coding: utf-8 -*-
import pygame
import planet


class SolarSystem:
    def __init__(self, width_app, height_app):
        self._width = width_app
        self._height = height_app
        self._sun = planet.Planet(width_app, height_app)
        self._mercury = planet.Planet(width_app, height_app)
        self._venus = planet.Planet(width_app, height_app)

        self._background_img = pygame.image.load("fon.jpg")
        self._background_img.convert()
        self._mercury_img = pygame.image.load("mercury.png")
        self._mercury_img.convert()
        self._sun_img = pygame.image.load("sun.png")
        self._sun_img.convert()
        self._venus_img = pygame.image.load("venus.png")
        self._venus_img.convert()

    def calc_data(self):
        # for sun:
        self._sun.set_mass(1.9891*pow(10, 30))
        self._sun.set_distance_to_sun(0)
        self._sun.set_diam(50)
        self._sun_img = pygame.transform.scale(self._sun_img, (self._sun.diam_, self._sun.diam_))

        # for mercury:
        self._mercury.set_mass(3.33022*pow(10, 23))
        self._mercury.set_distance_to_sun(70)
        self._mercury.set_diam(20)
        self._mercury_img = pygame.transform.scale(self._mercury_img, (self._mercury.diam_, self._mercury.diam_))

        #for venus:
        self._venus.set_mass(3.33022*pow(10, 23))
        self._venus.set_distance_to_sun(100)
        self._venus.set_diam(30)
        self._venus_img = pygame.transform.scale(self._venus_img, (self._venus.diam_, self._venus.diam_))

    def draw(self, screen):
        screen.blit(self._background_img, (0, 0))
        screen.blit(self._mercury_img, self._mercury.get_pos())
        screen.blit(self._sun_img, self._sun.get_pos())
        screen.blit(self._venus_img, self._venus.get_pos())

__author__ = 'lisgein'
