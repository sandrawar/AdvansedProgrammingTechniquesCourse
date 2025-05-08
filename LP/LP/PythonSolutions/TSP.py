from pulp import *
import numpy as np

triangular_distance = [[ 0],
[29,  0],
[82, 55,  0],
[46, 46, 68,  0],
[68, 42, 46, 82,  0],
[52, 43, 55, 15, 74,  0],
[72, 43, 23, 72, 23, 61,  0],
[42, 23, 43, 31, 52, 23, 42,  0],
[51, 23, 41, 62, 21, 55, 23, 33,  0],
[55, 31, 29, 42, 46, 31, 31, 15, 29,  0],
[29, 41, 79, 21, 82, 33, 77, 37, 62, 51,  0],
[74, 51, 21, 51, 58, 37, 37, 33, 46, 21, 65,  0],
[23, 11, 64, 51, 46, 51, 51, 33, 29, 41, 42, 61,  0],
[72, 52, 31, 43, 65, 29, 46, 31, 51, 23, 59, 11, 62,  0],
[46, 21, 51, 64, 23, 59, 33, 37, 11, 37, 61, 55, 23, 59,  0]]


n = len(triangular_distance)
distance = np.zeros((n, n), dtype=int)
for i in range(n):
    for j in range(i + 1):
        distance[i][j] = distance[j][i] = triangular_distance[i][j]

model = LpProblem("TSP", LpMinimize)

x = [[LpVariable(f"x_{i}_{j}", cat=LpContinuous, lowBound=0, upBound=1) for j in range(n)] for i in range(n)] 
u = [LpVariable(f"u_{i}", cat=LpContinuous, lowBound=0) for i in range(n)]

model += lpDot(x, distance)

for i in range(n):
    model += lpSum(x[i][j] for j in range(n) if i != j) == 1
    model += lpSum(x[j][i] for j in range(n) if i != j) == 1

for i in range(n):
    for j in range(1, n):
        if i != j:
            model += u[i] - u[j] + n * x[i][j] <= n - 1

model.solve()
print("Status:", LpStatus[model.status])
print("Optimum:", value(model.objective))

x_values = np.array([[value(x[i][j]) for j in range(n)] for i in range(n)])

def greedy_tsp_maximum(x_values, n):
    path = [0]  
    visited = [False] * n
    visited[0] = True  
    current_city = 0  
    
    while len(path) < n:
        nearest_city = None
        max_value = -1 
        
        for j in range(n):
            if not visited[j] and x_values[current_city][j] > max_value:
                nearest_city = j
                max_value = x_values[current_city][j]
        
        if nearest_city is None:
            raise ValueError(f"No valid city found from city {current_city}. Check x_values.")
        
        path.append(nearest_city)
        visited[nearest_city] = True
        current_city = nearest_city
    
    path.append(0)
    return path


path = greedy_tsp_maximum(x_values, n)
print("Trasa (Greedy):", path)

def calculate_total_distance(path, distance):
    total_distance = 0
    for i in range(len(path) - 1):  
        total_distance += distance[path[i]][path[i+1]]
    return total_distance

total_distance = calculate_total_distance(path, distance)
print("Całkowity koszt podróży (Greedy):", total_distance)
