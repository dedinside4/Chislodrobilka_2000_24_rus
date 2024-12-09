from sympy.printing import print_ccode
from sympy import sin, cos, atan, symbols, Matrix
from sympy.physics.mechanics import (dynamicsymbols, ReferenceFrame,
                                     Particle, Point)
import sympy.physics.mechanics.system as system
from sympy.physics.vector import init_vprinting
from sympy.physics.mechanics import *
from sympy.codegen.ast import Assignment
from sympy import solve
import numpy as np


f, a = dynamicsymbols('f a')
fd, ad = dynamicsymbols('f a', 1)


m, l, g, n = symbols('m l g n')

T = m * l**2 * fd**2 / 2 + m * l * ad * sin(f) * fd + m * ad**2 / 2

P = - m * g * (l * cos(f) + a)

L = T - P

LM = LagrangesMethod(L, [f, a])

#func1 = solve(LM.form_lagranges_equations(), [f1d2, f2d2])[f1d2]

#func2 = solve(LM.form_lagranges_equations(), [f1d2, f2d2])[f2d2]

print(LM.form_lagranges_equations()[1])

#print(solve(LM.form_lagranges_equations(), [f1d2, f2d2], dict=False))
