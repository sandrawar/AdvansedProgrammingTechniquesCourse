from pulp import *

# Jeden zestaw danych
weights = [382745, 799601, 909247, 729069, 467902, 44328, 34610, 698150, 823460, 903959,
853665, 551830, 610856, 670702, 488960, 951111, 323046, 446298, 931161, 31385, 496951,
264724, 224916, 169684]
prices = [25594, 1677009, 1676628, 1523970, 943972, 97426, 69666, 1296457, 1679693,
1902996, 1844992, 1049289, 1252836, 1319836, 953277, 2067538, 675367, 853655, 1826027,
65731, 901489, 577243, 466257, 369261]
carry_weight = 6404180

n = len(weights)
model = LpProblem(sense=LpMaximize)

# Zmienne binarne
variables = [LpVariable(name=f"x_{i}", cat=LpBinary) for i in range(n)]

# Ograniczenie wagowe
model += lpDot(weights, variables) <= carry_weight

# Funkcja celu
model += lpDot(prices, variables)

# Rozwiązanie
status = model.solve()

print("price:", model.objective.value())
print("take:", *[variables[i].value() for i in range(n)])
