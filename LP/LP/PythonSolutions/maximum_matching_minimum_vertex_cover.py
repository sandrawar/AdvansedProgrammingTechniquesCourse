from pulp import *
import random

def generate_random_bipartite_graph(n_a, n_b, m, seed=None):
    """
    Generuje losowy graf dwudzielny z:
    - n_a wierzchołków w części A (oznaczenia 0 ... n_a-1)
    - n_b wierzchołków w części B (oznaczenia n_a ... n_a + n_b - 1)
    - m losowych krawędzi pomiędzy A i B
    """
    if seed is not None:
        random.seed(seed)

    A = list(range(n_a))
    B = list(range(n_a, n_a + n_b))

    possible_edges = [(a, b) for a in A for b in B]
    m = min(m, len(possible_edges)) 

    E = random.sample(possible_edges, m)
    V = A + B

    return V, E


V = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
E =  [(0, 1), (0, 4), (0, 5), (1, 2), (1, 6), (2, 3), (2, 7), (3, 4), (3, 8), (4, 9), (5, 7),
 (5, 8), (6, 8), (6, 9), (7, 9)]
V0 = [0, 1, 2, 3]
E0 = [(0,1), (1,2), (2,3)]
V1 = [0, 1, 2, 3, 4]
E1 = [(0, 1), (1, 2), (1, 3), (2, 3), (3, 4), (2, 4), (0, 4), (1, 4), (0, 3), (0, 3)]
V2 = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
E2 = [(0, 1), (0, 4), (0, 5), (1, 2), (1, 6), (2, 3), (2, 7), (3, 4), (3, 8), (4, 9), (5, 7),
(5, 8), (6, 8), (6, 9), (7, 9)]
V3 = [0, 1, 2, 3, 4, 5]
E3 = [(0, 1), (2, 1), (2, 3), (3, 4), (4, 5)]

def solve_vertex_cover_rel(V, E):

    n = len(V)

    model = LpProblem("VertexCover", LpMinimize)

    x = [LpVariable(f"x_{i}", cat=LpContinuous, lowBound=0) for i in range(n)]

    model += lpSum(x)

    for edge in E:
        model += x[edge[0]] + x[edge[1]] >= 1

    model.solve()

    cover = [i for i in V if value(x[i]) >= 0.5]

    print("Optymalne pokrycie:", cover)
    print("Optimum:", value(model.objective))
    print("Rozmiar:", len(cover))



def solve_maximun_matching(V, E):
    n = len(V)
    m = len(E)

    model = LpProblem("MaximumMatching", LpMaximize)

    x = [LpVariable(f"x_{i}", cat=LpBinary, lowBound=0, upBound=1) for i in range(m)]

    model += lpSum(x)

    for vertex in V:
        model += lpSum(x[i] for i in range(m) if vertex in E[i]) <= 1

    model.solve()

    matching = [E[i] for i in range(m) if value(x[i]) == 1]

    print("Matched edges:", matching)
    print("Size: ", len(matching))

def solve_vertex_cover(V, E):

    n = len(V)

    model = LpProblem("VertexCover", LpMinimize)

    x = [LpVariable(f"x_{i}", cat=LpBinary, lowBound=0, upBound=1) for i in range(n)]

    model += lpSum(x)

    for edge in E:
        model += x[edge[0]] + x[edge[1]] >= 1

    model.solve()

    cover = [i for i in V if value(x[i]) == 1]

    print("Optymalne pokrycie:", cover)
    print("Optimum:", value(model.objective))
    print("Rozmiar:", len(cover))



(V_random, E_random) = generate_random_bipartite_graph(60, 40, 20)
#solve_maximun_matching(V0, E0)
#solve_vertex_cover_rel(V1, E1)
#solve_vertex_cover(V1, E1)
#solve_vertex_cover_rel(V_random, E_random)
solve_vertex_cover(V_random, E_random)
solve_maximun_matching(V_random, E_random)
