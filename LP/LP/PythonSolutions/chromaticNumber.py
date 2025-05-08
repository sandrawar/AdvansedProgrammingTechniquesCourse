from pulp import *

vertices1 = [0, 1, 2, 3, 4]
edges1 = [(0, 1), (1, 2), (1, 3), (2, 3), (3, 4), (2, 4), (0, 4), (1, 4), (0, 3), (0, 3)]
vertices2 = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
edges2 = [(0, 1), (0, 4), (0, 5), (1, 2), (1, 6), (2, 3), (2, 7), (3, 4), (3, 8), (4, 9), (5, 7),
 (5, 8), (6, 8), (6, 9), (7, 9)]
vertices3 = [0, 1, 2, 3, 4, 5]
edges3 = [(0, 1), (2, 1), (2, 3), (3, 4), (4, 5)]

def solve_chromatic_num(vertices, edges):
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

    for (u, v) in edges:
        for k in range(n):
            model += vertexColorVariables[u][k] + vertexColorVariables[v][k] <= 1
            
    for u in range(n):
        for k in range(n):
            model += (k + 1) * vertexColorVariables[u][k] <= C

    status = model.solve()

    print("Status:", LpStatus[status])
    print("C = ", C.value())

#solve_chromatic_num(vertices1, edges1)
#solve_chromatic_num(vertices2, edges2)
solve_chromatic_num(vertices3, edges3)