import pulp

def read_graph_from_file(filename):
    with open(filename, 'r') as f:
        lines = [line.strip() for line in f if line.strip() and not line.strip().startswith('EOF')]

    edges = {}
    nodes = set()
    source = sink = None

    i = 0
    while i < len(lines):
        if lines[i] == 'SECTION Graph':
            i += 1
            while i < len(lines) and lines[i] != 'END':
                tokens = lines[i].split()
                if tokens[0] == 'E' and len(tokens) == 4:
                    _, u, v, c = tokens
                    u, v, c = int(u), int(v), float(c)
                    edges[(u, v)] = c
                    nodes.update([u, v])
                i += 1
        elif lines[i] == 'SECTION SOURCE SINK':
            i += 1
            while i < len(lines) and lines[i] != 'END':
                tokens = lines[i].split()
                if tokens[0] == 'SOURCE':
                    source = int(tokens[1])
                elif tokens[0] == 'SINK':
                    sink = int(tokens[1])
                i += 1
        i += 1  

    return nodes, edges, source, sink


def solve_max_flow(filename):
    nodes, edges, s, t = read_graph_from_file(filename)
    model = pulp.LpProblem("MaxFlow", pulp.LpMaximize)

    f = pulp.LpVariable.dicts("flow", edges, lowBound=0)

    model += pulp.lpSum([f[(s, v)] for (u, v) in edges if u == s]), "TotalFlow"

    for (u, v), c in edges.items():
        model += f[(u, v)] <= c, f"Capacity_{u}_{v}"

    for node in nodes:
        if node != s and node != t:
            inflow = pulp.lpSum(f[(u, v)] for (u, v) in edges if v == node)
            outflow = pulp.lpSum(f[(u, v)] for (u, v) in edges if u == node)
            model += inflow == outflow, f"FlowConservation_{node}"

    model.solve()
    print("Status:", pulp.LpStatus[model.status])
    print("Max flow: ", pulp.value(model.objective))
    for (u, v) in edges:
        if(f[(u,v)].varValue > 0):
            print(f"Flow {u} -> {v}: {f[(u,v)].varValue}")

def solve_min_cut(filename):

    nodes, edges, source, sink = read_graph_from_file(filename)
    
    model = pulp.LpProblem("MinCut", pulp.LpMinimize)

    x = pulp.LpVariable.dicts("x", nodes, lowBound=0, upBound=1)
    y = pulp.LpVariable.dicts("y", edges, lowBound=0, upBound=1)

    model += x[source] == 0, "SourceIsZero"
    model += x[sink] == 1, "SinkIsOne"

    for (u, v) in edges:
        model += y[(u, v)] >= x[v] - x[u], f"CutEdge_{u}_{v}"

    model += pulp.lpSum(edges[(u, v)] * y[(u, v)] for (u, v) in edges), "TotalCutCapacity"

    model.solve()

    print("Status:", pulp.LpStatus[model.status])
    print("Minimalna pojemność przekroju: ", pulp.value(model.objective))

    print("Krawędzie w przekroju:")
    for (u, v) in edges:
        if y[(u, v)].varValue > 0.5:
            print(f"{u} -> {v} (capacity {edges[(u,v)]})")



solve_max_flow("instance0.txt")
#solve_min_cut("instance4.txt")
