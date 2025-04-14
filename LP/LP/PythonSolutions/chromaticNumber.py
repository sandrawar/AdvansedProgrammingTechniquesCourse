from pulp import *

vertices = [0, 1, 2, 3, 4]
edges = [(0, 1), (1, 2), (1, 3), (2, 3), (3, 4), (2, 4), (0, 4), (1, 4), (0, 2), (0, 3)]

n = len(vertices)

model = LpProblem("ChromaticNumber", LpMinimize)
vertexColorVariables = []

C = LpVariable(name = "C", cat = LpInteger)

model += C

for u in range(n):
    colorVariables = []
    for k in range(n):
        colorVariables.append(LpVariable(f"x_{u}_{k}", cat = LpBinary))
    vertexColorVariables.append(colorVariables)

for u in range(n):
    model += lpSum(vertexColorVariables[u]) == 1

for edge in edges:
    for k in range(n):
        model += vertexColorVariables[edges[0]][k] + vertexColorVariables[edges[1]][k] <= 1

for u in range(n):
    for k in range(n):
        model += (k + 1) * vertexColorVariables[u][k] <= C


status = model.solve()

print("Status:", LpStatus[status])
print("C = ", C.value())