import pygame as pg
from enum import Enum, auto

class TextAlign(Enum):
    TOPLEFT=auto()
    TOPRIGHT=auto()
    CENTER=auto()

TEXT_DEFAULTS = {'font_name':'', 'font_size':16, 'color':(255,255,255)}

def draw_text(surf, text, pos, data={}, text_align=TextAlign.TOPLEFT):
    """basic procedure to construct text and draw to pygame surfaces"""
    for arg in TEXT_DEFAULTS:
        if arg not in data:
            data[arg] = TEXT_DEFAULTS[arg]

    font = pg.font.SysFont(data['font_name'],data['font_size'])
    text_render = font.render(text,True,data['color'])
    rect = text_render.get_rect()
    match text_align:
        case TextAlign.TOPLEFT:
            rect.topleft = pos
        case TextAlign.TOPRIGHT:
            rect.topright = pos
        case TextAlign.CENTER:
            rect.center = pos
    surf.blit(text_render,rect)