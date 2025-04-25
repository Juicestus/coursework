#!/bin/python

#################################
#
# GRAPH GENERATOR SCRIPT
#
# pip install networkx pygraphviz matplotlib numpy
#
#

import networkx as nx
from networkx.drawing.nx_agraph import write_dot

import pygraphviz as pgv

import matplotlib.pyplot as plt
import numpy as np

from pathlib import Path
import os
import io
import random
from itertools import product

ARCHIVE_PATH = Path('graphs')

def add_binomial_dist_weights(G, n, p, symetric=False):

    edge_weights = np.random.binomial(n=n, p=p, size=G.number_of_edges())
    
    for ((u, v, data), weight) in zip(G.edges(data=True), edge_weights):
        if symetric and 'weight' in G.edges[v, u]:
            data['weight'] = G.edges[v, u]['weight']
        else:
            data['weight'] = weight

def to_directed_stochastic_dropout(G, p):
    D = G.to_directed()

    considered = set()

    for (u, v) in G.edges():

        indicator = (u, v) if u < v else (v, u)

        r = random.random()
        d = random.getrandbits(1)

        if indicator in considered:
            continue

        considered.add(indicator)

        if r > p:
            continue

        D.remove_edge(*((u, v) if d else (v, u)))
    
    return D

def write_edge(file, e, data):
    file.write(f' {e}({data["weight"]})')

def serialize_graph(G, file):
    
    for n, adjlist in G.adjacency():
        
        file.write(f'{n}: ')
        
        edges = adjlist.items()
        for i, (e, data) in enumerate(edges):

            write_edge(file, e, data)
            
            if i != len(edges) - 1:
                file.write(' ->')
        
        file.write('\n')

def save_serialized_graph(G, filename):

    with open(filename, 'w') as _file:

        serialize_graph(G, _file)


def serialize_all_shortest_paths(G, file, path_limit=500):
    all_paths = tuple(product(G, G))
    paths = random.sample(all_paths, min(path_limit, len(all_paths)))

    for (i, (v1, v2)) in enumerate(paths):

        file.write(f'{v1} {v2} : ')

        try:
            shortest_paths = list(nx.all_shortest_paths(G, source=v1, target=v2, weight='weight'))
        except nx.exception.NetworkXNoPath:
            shortest_paths = []
        
        for i, p in enumerate(shortest_paths):
            file.write(f'{" ".join(map(str, p))}')

            if i != len(paths) - 1:
                file.write(', ')
        
        file.write('\n')

def save_all_shortest_paths(G, filename, *args, **kargs):
    with open(filename, 'w') as file:
        serialize_all_shortest_paths(G, file, *args, **kargs)

def archive_graph(G, alias, base_path = ARCHIVE_PATH, path_limit=500):

    L = G.copy()

    for (u, v, data) in L.edges(data=True):
        data["label"] = data["weight"]
        del data["weight"]

    dir = base_path / alias
    try:
        os.mkdir(dir)
    except FileExistsError:
        pass

    A = nx.nx_agraph.to_agraph(L) 

    A.write(dir / f'{alias}.dot')

    for engine in ('dot', 'neato'):
        A.layout(prog=engine)
        A.draw(dir / f'{alias}_{engine}.svg')

    save_serialized_graph(G, dir / f'{alias}.dat')

    save_all_shortest_paths(G, dir / f'{alias}_shortest_paths.dat', path_limit=path_limit)

def generate_from_paramter_grid(alias, gen_fn, params, path_limit=500):    
    
    param_tuples = [list(product((l, ), v)) for l, v in params.items()]

    for cell in product(*param_tuples):

        cell_params = dict(cell)
        
        G = gen_fn(**cell_params)

        instance = alias + '-' + '_'.join(map(lambda kv : str(kv[0]) + '=' + str(kv[1]), cell))

        archive_graph(G, instance,path_limit=path_limit)


def complete_dropout_graph(size, dropout_p, weight_mean, weight_p):
    G = nx.complete_graph(size, nx.DiGraph())
    G = to_directed_stochastic_dropout(G, dropout_p)
    add_binomial_dist_weights(G, weight_mean, weight_p)
    return G

def directed_tree(branching, height, dropout_p, weight_mean, weight_p):
    G = nx.balanced_tree(branching, height)
    G = to_directed_stochastic_dropout(G, dropout_p)
    add_binomial_dist_weights(G, weight_mean, weight_p)
    return G

def complete_graph(size, weight_mean, weight_p):
    G = nx.complete_graph(size, nx.DiGraph())
    add_binomial_dist_weights(G, weight_mean, weight_p)
    return G

def internet_as_graph(n, weight_mean, weight_p):
    G = nx.random_internet_as_graph(n)
    G = G.to_directed()
    add_binomial_dist_weights(G, weight_mean, weight_p, symetric=True)
    return G

def gnp_dag(n, edge_p, weight_mean, weight_p):
    G = nx.fast_gnp_random_graph(n, edge_p, directed=True)
    G = nx.DiGraph([(u, v) for (u, v) in G.edges() if u < v])
    add_binomial_dist_weights(G, weight_mean, weight_p)

    return G

if __name__ == '__main__':

    G = internet_as_graph(300, 10, 0.25)
    archive_graph(G, 'internet')

    generate_from_paramter_grid(
        'complete_with_dropout', 
        complete_dropout_graph,
        {
            'size': [4, 8, 10],
            'dropout_p': [0.3, 0.5],
            'weight_mean': [10],
            'weight_p': [0.25, 0.5]
        }
    )

    generate_from_paramter_grid(
        'directed_tree', 
        directed_tree,
        {
            'branching': [2, 4, 6],
            'height': [2, 3, 4],
            'dropout_p': [0.1, 0.25],
            'weight_mean': [10],
            'weight_p': [0.25, 0.5]
        },
        path_limit=10
    )

    generate_from_paramter_grid(
        'complete_graph', 
        complete_graph,
        {
            'size': [4, 8, 10],
            'weight_mean': [10],
            'weight_p': [0.25, 0.5]
        }
    )

    generate_from_paramter_grid(
        'gnp_dag',
        gnp_dag,
        {
            'n': [20, 50, 100],
            'edge_p': [0.2, 0.4, 0.6],
            'weight_mean': [10],
            'weight_p': [0.25, 0.5]
        }
    )