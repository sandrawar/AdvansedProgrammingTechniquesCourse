from pulp import *

model = LpProblem("GameStrategy", LpMaximize)

x1 = LpVariable("x1", lowBound=0, cat="Continuous")
x2 = LpVariable("x2", lowBound=0, cat="Continuous")
v = LpVariable("v", cat="Continuous")

model += v  

model += 2*x1 - 3*x2 >= v
model += 4*x2 - 3*x1 >= v
model += x1 + x2 == 1

model.solve()

print("Status:", LpStatus[model.status])
print("x1 =", x1.varValue)
print("x2 =", x2.varValue)
print("v =", v.varValue)
