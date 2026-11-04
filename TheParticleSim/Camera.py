from helpers.Vec2 import *

class Camera:
    def __init__(self, px_width:int, px_height:int, m_height:int):
        self.x = 0
        self.y = 0

        self.px_size:tuple[int,int] = (px_width, px_height)
        self.m_size:tuple[float,float] = (m_height, (px_width/px_height)*m_height)

        self.px_per_m:float = px_height/m_height
        self.m_per_px:float = 1/self.px_per_m

    def meters_to_pixels(self, val):
        return val * self.px_per_m
    def pixels_to_meters(self, val):
        return val * self.m_per_px

    def phys_to_screen(self, val:VecLike) -> tuple[float, float]:
        return (self.meters_to_pixels(val[0]), self.meters_to_pixels(val[1]))
    def screen_to_phys(self, val:VecLike) -> tuple[float, float]:
            return (self.pixels_to_meters(val[0]), self.pixels_to_meters(val[1]))
