import pygame as pg

import random

from Camera import Camera
from Particle import Particle
from helpers.Vec2 import *
from helpers.gui import draw_text, TextAlign

class Simulation:
    def __init__(self):
        self.particles: set[Particle] = set()

        self.paused = True

        self.run_time:float = 0

    def pause(self):
        self.paused = True
    def togglePause(self):
        self.paused = not self.paused

    def new_node(self, pos, strength):
        self.particles.add(Particle(pos, strength))
    def add_node(self, node:Particle):
        self.particles.add(node)

    def update(self, dt:float):
        if self.paused: return

        self.run_time += dt

        for i in self.particles:
            # Collision checking - NOTE: disabled
            # for j in self.nodes:
            #     if i.collides_with(j):
            #         i.handle_collision(j)
            # i.vy = -1.
            i.apply_acceleration(10, Vec2(0,-1), dt)

            # Standard update
            i.update(dt)
            

    def render(self, surf:pg.Surface, cam:Camera):
        surf.fill(pg.Color('gray'))

        for node in self.particles:
            node.render(surf, cam)

        draw_text(surf, f'runtime: {round(self.run_time, 1)}s', (surf.get_width()-10, 10), text_align=TextAlign.TOPRIGHT)

class Main:

    desFPS = 60
    default_screen_size = (960,640)
    viewport_height_m = 50

    def __init__(self):
        pg.init()
        self.clock = pg.Clock()
        self.window = pg.display.set_mode(self.default_screen_size, flags=pg.RESIZABLE)

        self.setup_sim()

    def setup_sim(self):
        self.camera = Camera(self.window.get_width(), self.window.get_height(), self.viewport_height_m)
        self.simulation = Simulation()

    def mainloop(self):
        while True:
            # Event loop
            for event in pg.event.get():
                if event.type == pg.QUIT:
                    pg.quit()
                    exit(0)
                if event.type == pg.MOUSEBUTTONDOWN:
                    if event.button == 1: # 1-left, 2-mid?, 3-right, 4==scrolldown, 5-scrollup
                        # self.simulation.new_node(pg.mouse.get_pos(), 3)
                        self.simulation.add_node(Particle(self.camera.screen_to_phys(pg.mouse.get_pos()), random.randint(7,20), pg.Color.from_normalized(random.random(),random.random(),random.random(),1)))
                if event.type == pg.KEYDOWN:
                    if event.key == pg.K_r:
                        self.setup_sim()
                    if event.key == pg.K_SPACE:
                        self.simulation.togglePause()

            # Updates
            self.simulation.update(self.clock.get_time()/1000)

            # Render
            self.simulation.render(self.window, self.camera)

            pg.display.update()
            self.clock.tick()

if __name__ == "__main__":
    Main().mainloop()