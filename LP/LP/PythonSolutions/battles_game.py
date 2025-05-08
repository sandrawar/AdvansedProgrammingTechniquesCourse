from pulp import *
from itertools import product
import numpy as np

def all_distributions(total_units, num_battles):
    if num_battles == 1:
        yield (total_units,)
    else:
        for i in range(total_units + 1):
            for tail in all_distributions(total_units - i, num_battles - 1):
                yield (i,) + tail

def payoff_a(strategy_a, strategy_b):
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

def colonel_blotto_strategy(total_units_a, total_units_b, num_battles):
    strategies_a = list(all_distributions(total_units_a, num_battles))
    strategies_b = list(all_distributions(total_units_b, num_battles))
    n = len(strategies_a)
    m = len(strategies_b)
    
    model = LpProblem("ColonelBlotto", LpMaximize)

    p = [LpVariable(f"p_{i}", lowBound=0) for i in range(n)]
    v = LpVariable("v")  

    model += v

    model += lpSum(p) == 1

    for j, opp in enumerate(strategies_b):
        expected_payoff = lpSum([p[i] * payoff_b(our, opp) for i, our in enumerate(strategies_a)])
        model += expected_payoff >= v

    model.solve()

    mixed_strategy = {strategies_a[i]: p[i].varValue for i in range(n) }
    best_strategy = max(mixed_strategy, key=mixed_strategy.get)

    print("Najlepsza strategia (z najwyższym prawdopodobieństwem):", best_strategy)
    print("Wartość oczekiwana gry:", v.varValue)
    print("\nPełny rozkład prawdopodobieństw:")
    for strat, prob in sorted(mixed_strategy.items()):
        print(f"{strat} -> {round(prob, 5)}")
    
    return best_strategy, v.varValue


strategy, expected_value = colonel_blotto_strategy(4, 3, 2)

print("Najleosza startegia: ", strategy)
print("Wartość oczekiwana gry:", expected_value)

