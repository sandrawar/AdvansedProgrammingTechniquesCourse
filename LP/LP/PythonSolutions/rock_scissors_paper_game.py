from pulp import *

model = LpProblem("RPS_OptimalStrategy", LpMaximize)

x1 = LpVariable("x1", lowBound=0)  # Papier
x2 = LpVariable("x2", lowBound=0)  # Kamień
x3 = LpVariable("x3", lowBound=0)  # Nożyce
v = LpVariable("v")                

model += v

model += 0*x1 + (-2)*x2 + 1*x3 >= v
model += 2*x1 + 0*x2 + (-3)*x3 >= v
model += -1*x1 + 3*x2 + 0*x3 >= v

model += x1 + x2 + x3 == 1

model.solve()

print("Status:", LpStatus[model.status])
print("x1 (Papier) =", round(x1.varValue, 4))
print("x2 (Kamień) =", round(x2.varValue, 4))
print("x3 (Nożyce) =", round(x3.varValue, 4))
print("Wartość oczekiwana wypłaty (v) =", round(v.varValue, 4))
