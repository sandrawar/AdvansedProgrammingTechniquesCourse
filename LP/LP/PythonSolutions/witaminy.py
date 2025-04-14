from pulp import *

# Tworzymy model minimalizacyjny
model = LpProblem("Dieta_witaminowa", LpMinimize)

# Zmienne decyzyjne (ciągłe, bo nie wymagamy całkowitości)
x1 = LpVariable("x1", lowBound=0)
x2 = LpVariable("x2", lowBound=0)
x3 = LpVariable("x3", lowBound=0)

# Funkcja celu: minimalizacja kosztu
model += 40 * x1 + 100 * x2 + 150 * x3, "Koszt całkowity"

# Ograniczenia na witaminy
model += 1 * x1 + 2 * x2 + 2 * x3 == 3, "Witamina_A"
model += 30 * x1 + 10 * x2 + 20 * x3 == 75, "Witamina_C"

# Rozwiązywanie modelu
status = model.solve()

# Wyświetlenie statusu i wyników
print("Status:", LpStatus[status])
print("x1 =", x1.value())
print("x2 =", x2.value())
print("x3 =", x3.value())
print("Koszt całkowity =", value(model.objective))
