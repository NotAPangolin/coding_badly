import numpy as np
import typing as tp

import pygame as pg

from helpers.Vec2 import *
from helpers.gui import draw_text
from Camera import Camera

def weighted_avg(x1,w1,x2,w2): # works for anything that supports mult by all other inputs
    return (w1*x1+w2*x2)/(w1+w2)

class Particle:
    def __init__(self, pos:VecLike, mass:float=1.0, color:pg.typing.ColorLike=pg.Color('white')):
        self.pos:Vec2 = Vec2(pos)
        self.vel:Vec2 = Vec2(0.,0.)
        self.mass:float = mass
        self.radius:float = mass
        self.color:pg.Color = pg.Color(color)

    @property
    def x(self) -> float:
        return self.pos.x
    @x.setter
    def x(self, val:float):
        self.pos.x = val
    @property
    def y(self) -> float:
        return self.pos.y
    @y.setter
    def y(self, val:float):
        self.pos.y = val

    @property
    def vx(self) -> float:
        return self.vel.x
    @vx.setter
    def vx(self, val:float):
        self.vel.x = val
    @property
    def vy(self) -> float:
        return self.vel.y
    @vy.setter
    def vy(self, val:float):
        self.vel.y = val

    def update(self, time:float):
        # prev = self.pos.copy()
        self.x += self.vx * time
        self.y -= self.vy * time#inverted for -  ->  down
        # # print(f'applied velocity with change: {self.pos - prev}')

    def apply_acceleration(self, magnitude:float, direction:Vec2|float, time:float):
        self.apply_force(magnitude*self.mass, direction, time)

    def apply_force(self, magnitude:float, direction:Vec2|float, time:float):
        '''
        applies a force to the object according to F=ma

        :param direction: should be a normalized vector
        '''
        accel = magnitude / self.mass
        print(f'mag:{magnitude} / mas:{self.mass} = accel:{accel}')
        self.vel += (direction * accel * time)
        print(f'time:{time} vel:{self.vel}')

    def collides_with(self,other:Particle) -> bool:
        '''checks if collides with other particle'''
        return (self.pos.square_dist(other.pos)) <= self.radius*self.radius + other.radius*other.radius

    def render(self, surf:pg.Surface, cam:Camera):
        pg.draw.circle(surf, self.color, cam.phys_to_screen(self.pos), self.radius)

        draw_text(surf, f'p: {self.pos}\nps: {cam.phys_to_screen(self.pos)}\nv: {self.vel}', (20,20))