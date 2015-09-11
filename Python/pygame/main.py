#-*- coding: utf-8 -*-
import pygame
import sys
import gtk
import solar_system


def actions():
        events = pygame.event.get()
        for event in events:
            if event.type == pygame.QUIT:
                sys.exit(0)


def main():
    window = gtk.Window()
    window_screen = window.get_screen()
    pygame.init()
    screen = pygame.display.set_mode((window_screen.get_width()-50, window_screen.get_height()-50))
    s = solar_system.SolarSystem(window_screen.get_width()-50, window_screen.get_height()-50)
    s.calc_data()
    while 1:
        actions()
        s.draw(screen)
        pygame.display.update()

if __name__ == "__main__":
    main()

__author__ = 'lisgein'
