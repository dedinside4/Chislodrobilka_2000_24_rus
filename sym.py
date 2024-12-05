from sympy.printing import print_ccode
from sympy import cos, atan, symbols, Matrix
from sympy.physics.mechanics import (dynamicsymbols, ReferenceFrame,
                                     Particle, Point)
import sympy.physics.mechanics.system as system
from sympy.physics.vector import init_vprinting
from sympy.physics.mechanics import *
from sympy.codegen.ast import Assignment
from sympy import solve
import numpy as np


f1, f2 = dynamicsymbols('f1 f2')
f1d, f2d = dynamicsymbols('f1 f2', 1)
f1d2, f2d2 = dynamicsymbols('f1 f2', 2)

m1, m2, l1, l2, g = symbols('m1 m2 l1 l2 g')

T = (f1d**2 * l1**2 + f2d**2 * l2**2 + 2 * l1 * l2 * f1d * f2d * cos(f1 - f2)) * m2 / 2 + f1d**2 * l1**2 * m1 / 2

P = - m1 * g * l1 * cos(f1) - m2 * g * (cos(f1) * l1 + cos(f2) * l2)

L = T - P

LM = LagrangesMethod(L, [f1, f2])

func1 = solve(LM.form_lagranges_equations(), [f1d2, f2d2])[f1d2]

func2 = solve(LM.form_lagranges_equations(), [f1d2, f2d2])[f2d2]

print(func2)

#print(solve(LM.form_lagranges_equations(), [f1d2, f2d2], dict=False))
