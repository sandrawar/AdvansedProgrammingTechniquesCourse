from pulp import *

elements = [2, 3, 3, 8, 5, 7, 9, 5, 3, 2]

model = LpProblem("Subsets", LpMinimize)

n = len(elements)

x = [LpVariable(f"x_{i}", cat=LpBinary) for i in range(n)] 
diff = LpVariable(name = "diff", cat=LpBinary, lowBound=0)

sum_A = lpSum([elements[i] * x[i] for i in range(n)])
sum_B = lpSum([elements[i] * (1 - x[i]) for i in range(n)])

model += diff
model += sum_A - sum_B  == diff

model.solve()


setA = [elements[i] for i in range(n) if x[i].value() == 0]
setB = [elements[i] for i in range(n) if x[i].value() == 1]

print(f"Różnica: {abs(sum(setA) - sum(setB))}")
print(f"Podział: {setA} {setB}")