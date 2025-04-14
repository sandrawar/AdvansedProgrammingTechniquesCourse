from pulp import *
import itertools
import numpy as np

triangular_distance = [[0],
[633,   0],
[257, 390,   0],
[ 91, 661, 228,   0],
[412, 227, 169, 383,   0],
[150, 488, 112, 120, 267,   0],
[ 80, 572, 196,  77, 351,  63,   0],
[134, 530, 154, 105, 309,  34,  29,   0],
[259, 555, 372, 175, 338, 264, 232, 249,   0],
[505, 289, 262, 476, 196, 360, 444, 402, 495,   0],
[353, 282, 110, 324,  61, 208, 292, 250, 352, 154,   0],
[324, 638, 437, 240, 421, 329, 297, 314,  95, 578, 435,   0],
[ 70, 567, 191,  27, 346,  83,  47,  68, 189, 439, 287, 254,   0],
[211, 466,  74, 182, 243, 105, 150, 108, 326, 336, 184, 391, 145,   0],
[268, 420,  53, 239, 199, 123, 207, 165, 383, 240, 140, 448, 202,  57,   0],
[246, 745, 472, 237, 528, 364, 332, 349, 202, 685, 542, 157, 289, 426, 483,   0],
[121, 518, 142,  84, 297,  35,  29,  36, 236, 390, 238, 301,  55,  96, 153, 336,   0]]



n = len(triangular_distance)
distance = np.zeros((n, n), dtype=int)
for i in range(n):
    for j in range(i + 1):
        distance[i][j] = distance[j][i] = triangular_distance[i][j]

model = LpProblem("TSP", LpMinimize)

x = [[LpVariable(f"x_{i}_{j}", cat=LpBinary) for i in range(n)] for j in range(n)] 
u = [LpVariable(f"u_{i}", cat=LpInteger, lowBound=0) for i in range(n)]

model += lpDot(x, distance)

for i in range(n):
    model += lpSum(x[i][j] for j in range(n) if i != j) == 1
    model += lpSum(x[j][i] for j in range(n) if i != j) == 1

#less optimal condition
#fullset = list(range(n))
#for r in range(2, n):
#    for subset in combination(fullset, r): 
#        S = set(subset)s
#        not_S = set(fullset) - S

#        model += lpSum(x[i][j] for i in S for j in not_S) >= 1

for i in range(n):
    for j in range(1, n):
        if i != j:
            model += u[i] - u[j] + n * x[i][j] <= n - 1


model.solve()
print("Status:", LpStatus[model.status])
print("Optimum:", value(model.objective))

#trasa = [0]
#current = 0
#visited = {0}
#while len(trasa) < n:
#    for j in range(n):
#        if value(x[current][j]) == 1 and j not in visited:
#            trasa.append(j)
#            visited.add(j)
#            current = j
#            break
#trasa.append(0)
#print("Trasa", trasa)