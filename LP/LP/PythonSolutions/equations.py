from pulp import *

print("Podpunkt 1")

model1 = LpProblem("Example", LpMaximize)

x1 = LpVariable("x1", lowBound = 0, cat = "Continous")
x2 = LpVariable("x2", lowBound = 0, cat = "Continous")

model1 += x1 * 2 + x2

model1 += x1 + x2  <= 8
model1 += x1 - x2 <= 4
model1 += x1 >= 0
model1 += x2 >= 0

status = model1.solve()

print("Status:", LpStatus[status])
print("x1 = ", x1.value())
print("x2 = ", x2.value())


print("Podpunkt 2")

model2 = LpProblem("Example", LpMinimize)

y1 = LpVariable("y1", lowBound = 0, cat = "Continous")
y2 = LpVariable("y2", lowBound = 0, cat = "Continous")

model2 += y1 * 8 + y2 * 4

model2 += y1 + y2  >= 2
model2 += y1 - y2 >= 1
model2 += y1 >= 0
model2 += y2 >= 0

status = model2.solve()

print("Status:", LpStatus[status])
print("y1 = ", y1.value())
print("y2 = ", y2.value())


print("Podpunkt 3")

model3 = LpProblem("Example", LpMinimize)

x3_1 = LpVariable("x3_1", lowBound = 0, upBound = 4, cat = "Continous")
x3_2 = LpVariable("x3_2", lowBound = 0, upBound = 4, cat = "Continous")
x3_3 = LpVariable("x3_3", lowBound = 0, upBound = 4, cat = "Continous")
x3_4 = LpVariable("x3_4", lowBound = 0, upBound = 12, cat = "Continous")

model3 += x3_1 * 3 + x3_3

model3 += x3_1 + x3_2 + x3_3 + x3_4  == 10
model3 += x3_1 - x3_2 + x3_3 == 6
model3 += x3_1 >= 0
model3 += x3_2 >= 0
model3 += x3_3 >= 0
model3 += x3_4 >= 0
model3 += x3_1 <= 4
model3 += x3_2 <= 4
model3 += x3_3 <= 4
model3 += x3_4 <= 12

status = model3.solve()

print("Status:", LpStatus[status])
print("x3_1 = ", x3_1.value())
print("x3_2 = ", x3_2.value())
print("x3_3 = ", x3_3.value())
print("x3_3 = ", x3_4.value())

from pulp import *

print("Podpunkt 4")

model4 = LpProblem("Example", LpMinimize)

x4_1 = LpVariable("x4_1", lowBound=None, cat="Continuous")
x4_2 = LpVariable("x4_2", lowBound=None, cat="Continuous")
x4_3 = LpVariable("x4_3", lowBound=None, cat="Continuous")

abs_x4_1 = LpVariable("abs_x4_1", lowBound=0, cat="Continuous")
abs_x4_2 = LpVariable("abs_x4_2", lowBound=0, cat="Continuous")
abs_x4_3 = LpVariable("abs_x4_3", lowBound=0, cat="Continuous")

model4 += abs_x4_1 + abs_x4_2 + abs_x4_3

model4 += abs_x4_1 >= x4_1
model4 += abs_x4_1 >= -x4_1

model4 += abs_x4_2 >= x4_2
model4 += abs_x4_2 >= -x4_2

model4 += abs_x4_3 >= x4_3
model4 += abs_x4_3 >= -x4_3

model4 += x4_1 - 2 * x4_2 == 3
model4 += x4_3 - x4_1 <= 1

model4.solve()

print("Status:", LpStatus[model4.status])
print("x4_1 =", x4_1.value())
print("x4_2 =", x4_2.value())
print("x4_3 =", x4_3.value())


