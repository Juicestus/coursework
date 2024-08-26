import sympy as sp

t=sp.symbols('t')
x=2*sp.sin(t)
y=3*sp.cos(t)
sp.plot_parametric(x,y,(t,0,2*sp.pi))
