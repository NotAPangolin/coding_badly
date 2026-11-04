import numpy as np

import typing as tp

class Vec2:
    def __init__(self, x:float|VecLike, y:float|None=None):
        if type(x) in {float, int}:
            self.val = np.array((float(x),float(y)), dtype=float)
        elif type(x) is Vec2:
            self.val = x.val.copy()
        else:
            self.val = np.array(x, dtype=float)

    def dist(self, b:Vec2) -> float:
        return np.sqrt((b.x-self.x)**2 + (b.y-self.y)**2)
    def square_dist(self, b:Vec2) -> float:
        return (b.x-self.x)*(b.x-self.x) + (b.y-self.y)*(b.y-self.y)

    def copy(self) -> Vec2:
        return Vec2(self)

    @property
    def x(self):
        return self.val[0]
    @x.setter
    def x(self, val):
        self.val[0] = val

    @property
    def y(self):
        return self.val[1]
    @y.setter
    def y(self, val):
        self.val[1] = val

    def __getitem__(self, key):
        return self.val[key]

    def __str__(self):
        return f'({self.x}, {self.y})'

    @staticmethod
    def _value(value):
        return value.val if isinstance(value, Vec2) else value

    def __add__(self, b):
        return Vec2(self.val + self._value(b))
    def __radd__(self, b):
        return Vec2(self._value(b) + self.val)

    def __sub__(self, b):
        return Vec2(self.val - self._value(b))
    def __rsub__(self, b):
        return Vec2(self._value(b) - self.val)

    def __mul__(self, b):
        return Vec2(self.val * self._value(b))
    def __rmul__(self, b):
        return Vec2(self._value(b) * self.val)

    def __truediv__(self, b):
        return Vec2(self.val / self._value(b))
    def __rtruediv__(self, b):
        return Vec2(self._value(b) / self.val)

    def __floordiv__(self, b):
        return Vec2(self.val // self._value(b))
    def __rfloordiv__(self, b):
        return Vec2(self._value(b) // self.val)

    def __mod__(self, b):
        return Vec2(self.val % self._value(b))
    def __rmod__(self, b):
        return Vec2(self._value(b) % self.val)

    def __divmod__(self, b):
        quotient, remainder = divmod(self.val, self._value(b))
        return Vec2(quotient), Vec2(remainder)
    def __rdivmod__(self, b):
        quotient, remainder = divmod(self._value(b), self.val)
        return Vec2(quotient), Vec2(remainder)

    def __pow__(self, b):
        return Vec2(self.val ** self._value(b))
    def __rpow__(self, b):
        return Vec2(self._value(b) ** self.val)

    def __neg__(self):
        return Vec2(-self.val)
    def __pos__(self):
        return Vec2(+self.val)
    def __abs__(self):
        return Vec2(abs(self.val))

    def __iadd__(self, b):
        self.val = self.val + self._value(b)
        return self
    def __isub__(self, b):
        self.val = self.val - self._value(b)
        return self
    def __imul__(self, b):
        self.val = self.val * self._value(b)
        return self
    def __itruediv__(self, b):
        self.val = self.val / self._value(b)
        return self
    def __ifloordiv__(self, b):
        self.val = self.val // self._value(b)
        return self
    def __imod__(self, b):
        self.val = self.val % self._value(b)
        return self
    def __ipow__(self, b):
        self.val = self.val ** self._value(b)
        return self



VecLike = tp.Sequence[float] | np.ndarray | Vec2