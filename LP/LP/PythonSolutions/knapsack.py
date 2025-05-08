from pulp import *

weights1 = [12, 7, 11, 8, 9]
prices1 = [24, 13, 23, 15, 16]
carry_weight1 = 26

weights2 = [23, 31, 29, 44, 53, 38, 63, 85, 89, 82]
prices2 = [92, 57, 49, 68, 60, 43, 67, 84, 87, 72]
carry_weight2 = 165

weights3 = [382745, 799601, 909247, 729069, 467902, 44328, 34610, 698150, 823460, 903959,
 853665, 551830, 610856, 670702, 488960, 951111, 323046, 446298, 931161, 31385, 496951,
 264724, 224916, 169684]
prices3 = [825594, 1677009, 1676628, 1523970, 943972, 97426, 69666, 1296457, 1679693,
 1902996, 1844992, 1049289, 1252836, 1319836, 953277, 2067538, 675367, 853655, 1826027,
 65731, 901489, 577243, 466257, 369261]
carry_weight3 = 6404180

def solve_knapsack_problem(weights, prices, carry_weight):

    n = len(weights)
    model = LpProblem(sense=LpMaximize)

    variables = [LpVariable(name=f"x_{i}", cat=LpBinary) for i in range(n)]

    model += lpDot(weights, variables) <= carry_weight

    model += lpDot(prices, variables)

    status = model.solve()

    print("price:", model.objective.value())
    print("take:", *[variables[i].value() for i in range(n)])

solve_knapsack_problem(weights1, prices1, carry_weight1)
#solve_knapsack_problem(weights2, prices2, carry_weight2)
#solve_knapsack_problem(weights3, prices3, carry_weight3)
