from pulp import *
import numpy as np

def all_distributions(total_units, num_battles):
    if num_battles == 1:
        yield (total_units,)
    else:
        for i in range(total_units + 1):
            for tail in all_distributions(total_units - i, num_battles - 1):
                yield (i,) + tail

def payoff(strategy_a, strategy_b):
    score = 0
    for a, b in zip(strategy_a, strategy_b):
        if a > b:
            score += 1
        elif a < b:
            score -= 1
    return score

def payoff_b(strategy_a, strategy_b):
    score = 0
    for a, b in zip(strategy_a, strategy_b):
        if a > b:
            score += b + 1
        elif a < b:
            score -= (a + 1)
    return score

def blotto(total_units_a, total_units_b, num_battles):
    strategies_a = list(all_distributions(total_units_a, num_battles))
    strategies_b = list(all_distributions(total_units_b, num_battles))

    n = len(strategies_a)
    m = len(strategies_b)

    payoff_matrix = np.zeros((n, m))
    for i, sa in enumerate(strategies_a):
        for j, sb in enumerate(strategies_b):
            payoff_matrix[i, j] = payoff_b(sa, sb)

    model = LpProblem("Blotto_MatrixForm", LpMaximize)

    p = [LpVariable(f"p_{i}", lowBound=0) for i in range(n)] 
    v = LpVariable("v")  

    model += v  
    model += lpSum(p) == 1

    for j in range(m):
        model += lpSum([p[i] * payoff_matrix[i][j] for i in range(n)]) >= v

    model.solve()

    strategy = {strategies_a[i]: p[i].varValue for i in range(n)}
    best_strategy = max(strategy, key=strategy.get)

    print("Najlepsza czysta strategia A:", best_strategy)
    print("Wartość oczekiwana gry:", round(v.varValue, 3))
    print("\nStrategia mieszana gracza A:")
    for strat, prob in sorted(strategy.items(), key=lambda x: x[1], reverse=True):
        print(f"{strat} -> {round(prob, 3)}")

    return best_strategy, v.varValue, payoff_matrix

blotto(4, 3, 2  )
