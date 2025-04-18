from graphviz import Digraph

def draw_dfa():
    dot = Digraph()
    dot.attr(rankdir='LR')

    states = ['q0', 'q1', 'q2', 'q3', 'q4', 'q5', 'q_reject']
    accept_states = ['q0', 'q1', 'q2', 'q3', 'q4', 'q5']  # reject only q_reject
    for state in states:
        if state == 'q0':
            dot.node(state, shape='doublecircle', style='filled', fillcolor='lightgreen')  # Start + accept
        elif state in accept_states:
            dot.node(state, shape='doublecircle')
        else:
            dot.node(state, shape='circle')

    dot.edge('', 'q0', label='start')

    transitions = {
        'q0': {'0': 'q1', '1': 'q0'},
        'q1': {'0': 'q1', '1': 'q2'},
        'q2': {'0': 'q1', '1': 'q3'},
        'q3': {'0': 'q4', '1': 'q3'},
        'q4': {'0': 'q4', '1': 'q5'},
        'q5': {'0': 'q4', '1': 'q_reject'},
        'q_reject': {'0': 'q_reject', '1': 'q_reject'}
    }

    for state, trans in transitions.items():
        for input_char, next_state in trans.items():
            dot.edge(state, next_state, label=input_char)

    dot.render('dfa_graph', format='png', cleanup=False)
    print("DFA graph rendered as 'dfa_graph.png'")

draw_dfa()

