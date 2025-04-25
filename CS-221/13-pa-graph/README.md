# Graph Algorithms
In this assignment, the Graph data structure is provided. We also provide many helper functions. The only four functions you have to write are:

- Topological Sort
  - `computeIndegree` (located in `top-sort-helpers.h`)
  - `topologicalSort` (located in `graph-algorithms.h`)
- Dijkstra's Algorithm
  - `relax` (located in `dijkstras-helpers.h`)
  - `dijkstrasAlgorithm` (located in `graph-algorithms.h`)

Pseudocode for these functions is provided below. (Search for `PSEUDOCODE` to find easily!)

This is intended to be a fairly easy Programming Assignment to end the semester, but there are a few new concepts which we will describe below.

### `std::unordered_set`
This is similar to a `std::unordered_map`, but where a map maintains key-value pairs, the set maintains only keys. Its role is to add and remove elements quickly and to quickly determine whether an element is present in the set.

It is used in Dijkstra's algorithm to manage the set of visited nodes `s` (sometimes referred to as the "cloud" in lecture).

### `std::optional`
This type is a container that can either have an object or will not have anything. We fill the optionals with nothing (`std::nullopt`) and then can replace that data with `value_type<T>` as part of the `relax` function.

Useful functions for optionals are:
```cpp
std::optional o; // optional
// ... do domething with o
if (o.has_value()) // returns true if o has a value
    o.value() // fetch the value from o, fails if no value
```

## Getting started

Download this code by running the following command in the directory of your choice:
```sh
git clone git@github.com:tamu-edu-students/leyk-csce221-assignment-graph-algorithms.git && cd leyk-csce221-assignment-graph-algorithms
```

Open the code in your editor of choice. For instance, if you use VS Code:
```sh
code .
```
*Note:* On OSX you may need to enable the `code` command in VS Code with <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and typing "shell command." You can select the option to install the command, and then the above command will work.

## Assignment
The assignment provides you with a working `WeightedGraph` data structure, which you can use to complete the two tasks:
- [Implement Topological Sort](#implement-topological-sort) &ndash; Medium Difficulty
- [Implement Dijkstra's Algorithm](#implement-dijkstras-algorithm) &ndash; Hard Difficulty

### Understand Weighted Graph
#### Overall Structure

The general structure of the graph can be thought of as a hash map of hash maps. For the overall map, this stores pairs of `(vertex, adjacency_list)`. Each `adjacency_list` is a hash map containing pairs of `(end_vertex, weight_of_edge)`.

For example, if there is a graph with 3 vertices (`A`, `B`, and `C`) and the edges `(A, B)` (weight of 4), `(A, C)` (weight of 1), `(B, C)` (weight of 3), and `(C, A)` (weight of 7). If we represent pairs as `()` and maps as `[]`, this would look like:

```
[
    (A, [(B, 4), (C, 1)]),
    (B, [(C, 3)]),
    (C, [(A, 7)])
]
```

#### Types

| Type | Alias | Description |
| ---- | ----- | ----------- |
| `value_type` | `T` | The values stored in the vertices. Commonly used in the functions you'll write. |
| `weight_type` | `int` | The type for edge weights. This is `int` for all graphs by default. The only requirement is that it is numeric. |
| `vertex_type` | `const value_type` | The type for vertices. It's a `const` form of `value_type`. Because of it being `const`, you can't use it for most of the functions you write. Use `value_type` instead. |
| `edge_type` | `std::pair<vertex_type, weight_type>` | A type for edges. The edges are really key value pairs within the adjacency list map. It is not necessary, but you may use it if you want. |
| `adjacency_list` | `std::unordered_map<value_type, weight_type>` | The type of the adjacency list for a given source vertex. We use a `map` to associate destination vertices (`value_type`) to the weight (`weight_type`) of the edge connecting from the source. |
| `container_type` | `std::unordered_map<value_type, adjacency_list>` | The type of the container that manages the vertices (`value_type`) and their associated adjacency lists (`adjacency_list`). We use a `map` to handle the association. |
| `size_type` | `typename container_type::size_type` | We steal `size_type` from the `container`. It is likely `std::size_t` in most cases. |
| `iterator` | `typename container_type::iterator` | Our main iterator which allows us to check the vertices and/or adjacency lists is the iterator for the `container`. |
| `const_iterator` | `typename container_type::const_iterator` | We also get the `const_iterator` from the container. |
| `edge_iterator` | `typename adjacency_list::iterator` | We define an `edge_iterator` which allows us to iterate over all of the edges from a given source node. In other words, we iterate over every entry in the adjacency list for a given vertex. |
| `const_edge_iterator` | `typename adjacency_list::const_iterator` | We also get the `const_edge_iterator` which behaves similarly. |

These types were redefined in the [`graph-types.h`](src/graph-types.h) header. To use them from the header, write the type's name and supply a template argument. For example, `value_type<int>` or `weight_type<T>`.

#### Methods

```cpp
bool empty() const
```

**Description**: Determine whether the vertex set is empty.

**Parameters**: *None*

**Returns**:
- `true` if there are no vertices (and thus, no edges)
- `false` otherwise

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
bool empty(const vertex_type& vertex) const
```

**Description**: Determine whether the adjacency list associated with `vertex` is empty.

**Parameters**:
- `vertex` a vertex in the graph to test

**Returns**:
- `true` if there are no edges sourced from that vertex
- `false` otherwise

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
size_type size() const
```

**Description**: Get the size of the vertex set.

**Parameters**: *None*

**Returns**: the number of vertices in the graph

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
size_type size(const vertex_type& vertex) const
```

**Description**: Get the size of the adjacency list associated with `vertex`.

**Parameters**:
- `vertex` a vertex in the graph to test

**Returns**: the number of edges in the graph that start at `vertex`

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const adjacency_list& at(const vertex_type& vertex) const
```

**Description**: Get constant access to the adjacency list of `vertex`.

**Parameters**:
- `vertex` a vertex in the graph to access

**Returns**: a constant reference to the adjacency list for vertex `vertex`

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
std::pair<iterator, bool> push_vertex(const vertex_type& vertex)
```

**Description**: Adds `vertex` to the vertex set if it is not already there.

**Parameters**:
- `vertex` a vertex to add to the graph

**Returns**:
- an `iterator` to the inserted vertex, or existing vertex if the vertex already existed
- `true` if the `vertex` was just inserted for the first time
- `false` if the `vertex` already existed in the graph

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
size_type pop_vertex(vertex_type& vertex)
```

**Description**: Removes `vertex` from the vertex set if it exists and from the adjacency lists of all other vertices in the set if it exists in their lists.

**Parameters**:
- `vertex` a vertex to remove from the graph

**Returns**: the sum of the number of edges to `vertex` and the number of vertices with label `vertex` that existed in graph prior to removing `vertex`

**Throws**: *None*

**Time Complexity**: *O(n)* &ndash; Linear Time (Average Case); *O(nm)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
std::pair<edge_iterator, bool> push_edge(const vertex_type& source, const vertex_type& destination, const weight_type& weight)
```

**Description**: Adds a given edge to the graph if no such edge already exists between `source` and `destination`.

**Parameters**:
- `source` a vertex in the graph at which the edge will begin
- `destination` a vertex at which the edge will end (need not yet exist in the graph)
- `weight` the weight of the newly created edge

**Returns**:
- an `iterator` to the inserted edge within the adjacency list of source, or existing edge if the edge already existed
- `true` if the edge was just inserted for the first time
- `false` if the vertex already existed in the graph

**Throws**:
- `std::out_of_range` if `source` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average Case); *O(n+m)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
size_type pop_edge(const vertex_type& source, const vertex_type& destination)
```

**Description**: Removes the given edge from the graph it exists.

**Parameters**:
- `source` a vertex in the graph at which the edge will begin
- `destination` a vertex at which the edge will end (need not exist in the graph)

**Returns**:
- `0` if the edge did not exist in the graph
- `1` if the edge existed in the graph

**Throws**:
- `std::out_of_range` if `source` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average Case); *O(n+m)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
iterator begin()
```

**Description**: Gets a `iterator` to the beginning of the vertex set.

**Parameters**: *None*

**Returns**: `iterator` to the beginning vertex in the graph. This could be any given vertex within the graph, because `unordered_map` can order the vertices however it likes.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
const_iterator begin() const
```

**Description**: Gets a `const_iterator` to the beginning of the vertex set.

**Parameters**: *None*

**Returns**: `const_iterator` to the beginning vertex in the graph. This could be any given vertex within the graph, because `unordered_map` can order the vertices however it likes.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
const_iterator cbegin() const
```

**Description**: Gets a `const_iterator` to the beginning of the vertex set.

**Parameters**: *None*

**Returns**: `const_iterator` to the beginning vertex in the graph. This could be any given vertex within the graph, because `unordered_map` can order the vertices however it likes.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
iterator end()
```

**Description**: Gets an `iterator` to the end of the vertex set.

**Parameters**: *None*

**Returns**: `iterator` past the last vertex in the graph. This is the same `end` iterator we've seen for `unordered_map`.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
const_iterator end() const
```

**Description**: Gets a `const_iterator` to the end of the vertex set.

**Parameters**: *None*

**Returns**: `const_iterator` past the last vertex in the graph. This is the same `end` iterator we've seen for `unordered_map`.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
const_iterator cend() const
```

**Description**: Gets a `const_iterator` to the end of the vertex set.

**Parameters**: *None*

**Returns**: `const_iterator` past the last vertex in the graph. This is the same `cend` iterator we've seen for `unordered_map`.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
edge_iterator begin(const vertex_type& vertex)
```

**Description**: Gets an `edge_iterator` to the beginning of `vertex`'s adjacency list.

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `edge_iterator` to the beginning of the adjacency list for `vertex` in the graph. This could be any given edge within the list, because `unordered_map` can order the edges however it likes.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const_edge_iterator begin(const vertex_type& vertex) const
```

**Description**: Gets a `const_edge_iterator` to the beginning of `vertex`'s adjacency list.

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `const_edge_iterator` to the beginning of the adjacency list for `vertex` in the graph. This could be any given edge within the list, because `unordered_map` can order the edges however it likes.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const_edge_iterator cbegin(const vertex_type& vertex) const
```

**Description**: Gets a `const_edge_iterator` to the beginning of `vertex`'s adjacency list.

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `const_edge_iterator` to the beginning of the adjacency list for `vertex` in the graph. This could be any given edge within the list, because `unordered_map` can order the edges however it likes.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
edge_iterator end(const vertex_type& vertex)
```

**Description**: Gets an `edge_iterator` to the end of `vertex`'s adjacency list.

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `edge_iterator` past the last edge in the adjacency list of `vertex` in the graph. This is the same `end` iterator we've seen for `unordered_map`.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const_edge_iterator end(const vertex_type& vertex) const
```

**Description**: Gets a `const_edge_iterator` to the end of `vertex`'s adjacency list.

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `const_edge_iterator` past the last edge in the adjacency list of `vertex` in the graph. This is the same `end` iterator we've seen for `unordered_map`.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const_edge_iterator cend(const vertex_type& vertex) const
```

**Description**: Gets a `const_edge_iterator` to the end of `vertex`'s adjacency list.

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `const_edge_iterator` past the last edge in the adjacency list of `vertex` in the graph. This is the same `cend` iterator we've seen for `unordered_map`.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
void clear()
```

**Description**: Clears every vertex and its corresponding adjacency list from the graph. Resets the graph to an empty state.

**Parameters**: *None*

**Returns**: *None*

**Throws**: *None*

**Time Complexity**: *O(nm)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
void clear(const vertex_type& vertex)
```

**Description**: Clears every edge from the adjacency list of `vertex`. Resets the adjacency list of `vertex` to an empty state.

**Parameters**:
- `vertex` a vertex in the graph to test

**Returns**: *None*

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(n+m)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
template <typename T>
std::ostream &operator<<(std::ostream &o, const WeightedGraph<T> &graph)
```

**Description**: Prints `graph` to `o`.

**Parameters**:
- `o` stream to receive the graph
- `graph` the graph to print

**Returns**: `o` to be used for stream chaining: `std::cout << graph << std::endl;`

**Throws**: *None*

**Time Complexity**: *O(nm)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
template <typename T>
std::istream &readEdge(std::istream &i, value_type<T> &vertex, weight_type<T> &weight)
```

**Description**: Reads `vertex` and `weight` from `i`.

**Parameters**:
- `i` stream to read the edge from
- `vertex` the vertex to save
- `weight` the weight to save

**Returns**: `i` to be used for stream chaining.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
template <typename T>
std::istream &operator>>(std::istream &i, WeightedGraph<T> &graph)
```

**Description**: Reads `graph` from `i`.

**Parameters**:
- `i` stream to read the graph from
- `graph` the graph to save

**Returns**: `i` to be used for stream chaining.

**Throws**: *None*

**Time Complexity**: *O(nm)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

#### Iterating Through Graph

There are many different ways to iterate through all edges in the adjaceny list, and we have provided some possible ways below. Feel free to decide which to use based on what makes the most sense to you. You can even use a combination of these or come up with your own way of iterating through the graph.

For all of these techniques, we will be iterating through the each vertex, then for each vertex we will iterate through its adjacency list. This leads to a nested-loop structure. If you want to iterate through all of the vertices, you can isolate the outer loop. If you want to iterate through the adjacency list of a single vertex, you can isolate the inner loop.

##### Using Iterators

There are two main types of iterators in our graph: `iterator`/`const_iterator` and `edge_iterator`/`const_edge_iterator`. As expected, `iterator`/`const_iterator` is used to iterate through the vertices in the graph and `edge_iterator`/`const_edge_iterator` is used to iterate through a single vertex's adjacency list. Below are 3 possible ways to iterate through the graph using iterators. The first version takes advantaged of the `begin(vertex)` and `end(vertex)` functions provided by the weighted graph class. The second version instead directly accesses the adjacency list through the `at(vertex)` function provided by the weighted graph class. The final version is very similar to the second, except this version extracts the adjacency list through the iterator instead of the `at(vertex)` function.

**Version 1**
```cpp
for (const_iterator<T> i = graph.begin(); i != graph.end(); ++i) {
    vertex_type<T> u = i->first;

    for (const_edge_iterator<T> j = graph.begin(u); j != graph.end(u); ++j) {
        vertex_type<T> v = j->first;
        weight_type<T> w = j->second;

        // Do Stuff With Edge (u, v, w)
    }
}
```

**Version 2**
```cpp
for (const_iterator<T> i = graph.begin(); i != graph.end(); ++i) {
    vertex_type<T> u = i->first;
    const adjacency_list<T>& adj_list = graph.at(u);

    for (const_edge_iterator<T> j = adj_list.begin(); j != adj_list.end(); ++j) {
        vertex_type<T> v = j->first;
        weight_type<T> w = j->second;

        // Do Stuff With Edge (u, v, w)
    }
}
```

**Version 3**
```cpp
for (const_iterator<T> i = graph.begin(); i != graph.end(); ++i) {
    vertex_type<T> u = i->first;
    const adjacency_list<T>& adj_list = i->second;

    for (const_edge_iterator<T> j = adj_list.begin(); j != adj_list.end(); ++j) {
        vertex_type<T> v = j->first;
        weight_type<T> w = j->second;

        // Do Stuff With Edge (u, v, w)
    }
}
```

##### Using Range-Based/For-Each Loop

In addition to using the iterator, you may be interested in using something called [range-based for loops](https://en.cppreference.com/w/cpp/language/range-for). You may also here these called for-each loops. You likely saw the Python equivalent in ENGR 102, with the syntax `for elem in arr`. The format in C++ is very similar, with `for (int i : arr)` meaning to iterate through each `int` in the container `arr`, copying each value into a variable `i` for use in the local scope of the loop. This syntax can be very succinct, and an example of iterating through the graph using for-each loops can be seen below.

**Version 4**
```cpp
for (const std::pair<value_type<T>, adjacency_list<T>>& vert_pair : graph) {
    vertex_type<T> u = vert_pair.first;
    const adjacency_list<T>& adj_list = vert_pair.second;

    for (const std::pair<value_type<T>, weight_type<T>>& edge_pair : adj_list) {
        vertex_type<T> v = edge_pair.first;
        weight_type<T> w = edge_pair.second;

        // Do Stuff With Edge (u, v, w)
    }
}
```

On top of using range-based for loops, we can take advantage of a neat syntactical trick known as [structured binding](https://en.cppreference.com/w/cpp/language/structured_binding). This allows us to easily decompose each pair directly into a key and value for an even more succinct syntax. Below is an example of how range-based for loops and structured binding can be combined to iterate through the graph.

**Version 5**
```cpp
for (const auto& [u, adj_list] : graph) {
        for (const auto& [v, w] : adj_list) {
            // Do Stuff With Edge (u, v, w)
        }
    }
```

### Implement Topological Sort

#### Helpers

```cpp
template <typename T>
void computeIndegrees(const WeightedGraph<T>& graph, std::unordered_map<value_type<T>, int>& indegrees)
```

**Description**: Associates the `indegrees` for each vertex in the `graph` with the values for the indegrees.

**Parameters**:
- `graph` graph to compute from
- `indegrees` the mapping of a vertex to its indegree 

**Returns**: *None*

**Throws**:
- Possibly `std::out_of_range` if the `graph` is malformed

**Tests for This Function**: *N/A* (Untested Helper Function Used in `topologicalSort()`)

**Functions Required by Tests**: *N/A*

**Time Complexity**: *O(n + m)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the number of edges

**Pseudocode**:
```
Default Indegree of Each Vertex to 0

For Every Edge:
    Increment Indegree of Ending Vertex
```

#### Topological Sort

```cpp
template <typename T>
std::list<value_type<T>> topologicalSort(const WeightedGraph<T>& graph)
```

**Description**: Creates a list of vertices in a valid, topological order if one exists. If not such ordering exists (perhaps because of a cycle), then it returns an empty list.

**Parameters**:
- `graph` graph to compute a topological ordering

**Returns**: List of vertices in a valid topological ordering

**Throws**:
- Possibly `std::out_of_range` if the `graph` is malformed

**Tests for This Function**: `topological_sort`

**Functions Required by Tests**: `topologicalSort()` (`computeIndegrees()` Not Required But Highly Recommended)

**Time Complexity**: *O(n + m)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the number of edges

**Pseudocode**:
```
Initialize Empty List (Stores Top Sort Ordering)

Compute Indegree of All Vertices

Initialize Empty Queue (Tracks Discovered Vertices)
Add All Vertices with Indegree 0 to Queue

While Queue is Not Empty (i.e. Still Nodes to Process):
    Pop Front of Queue (u) and Add to End of List
    
    For Each Edge (u, v) in Adjacency List of u:
        Decrement Indegree of v
        Add v to Queue if Indegree Becomes 0

If Some Vertices Were Not Added to Top Sort Ordering (List):
    A Cycle Was Detected, Meaning There is No Valid Top Sort Ordering of the Graph (Only Valid for DAGs)
    Because of This, Return an Empty List

Otherwise, Return the List (A Valid Top Sort Ordering)
```

### Implement Dijkstra's Algorithm

#### Helpers

```cpp
template <typename T>
weight_type<T> infinity()
```

**Description**: Gets the largest possible (infinite) weight. `weight_type<T>` must always be numeric or this fails to compile.

**Parameters**: *None*

**Returns**: Infinite Weight Value.

**Throws**: *None*

**Tests for This Function**: *N/A* (Already Implemented For You)

**Functions Required by Tests**: *N/A*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Invocation**:
```cpp
infinity<T>();
```

----

```cpp
template <typename T>
void initializeSingleSource(const WeightedGraph<T>& graph, vertex_type<T> initial_node,
std::unordered_map<value_type<T>, weight_type<T>>& distances,
std::unordered_map<value_type<T>, std::optional<value_type<T>>>& predecessors)
```

**Description**: Sets all distances to infinity except the initial node which is set to 0. Also sets all predecessors to `nullopt`. This indicates that there are no predecessors initially.

**Parameters**:
- `graph` the graph to initialize the distances
- `initial_node` the first node in the graph to source the search from
- `distances` the mapping of vertices to their distances from the source
- `predecessors` a lookup table telling the predecessor to the current node along the shortest path from the source

**Returns**: *None*

**Throws**: *None*

**Tests for This Function**: *N/A* (Already Implemented For You)

**Functions Required by Tests**: *N/A*

**Time Complexity**: *O(n + m)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the number of edges

----

```cpp
template <typename T>
class DijkstraComparator
```

**Description**: Compares two vertices by their distance from the source vertex.

**Tests for This Function**: *N/A* (Already Implemented For You)

**Functions Required by Tests**: *N/A*

----

```cpp
template <typename T>
void updateHeap(std::priority_queue<value_type<T>, std::vector<value_type<T>>, DijkstraComparator<T>>& q,
std::unordered_map<value_type<T>, weight_type<T>>& distances)
```

**Description**: Reorders the heap based on changes to the distances after relaxation.

**Parameters**:
- `q` the priority queue to reorganize
- `distances` the mapping of vertices to their distances from the source

**Returns**: *None*

**Throws**: *None*

**Tests for This Function**: *N/A* (Already Implemented For You)

**Functions Required by Tests**: *N/A*

**Time Complexity**: *O(n)* &ndash; Linear Time
- *n* is the queue size

----

```cpp
template <typename T>
bool relax(value_type<T> u, value_type<T> v, weight_type<T> w,
std::unordered_map<value_type<T>, weight_type<T>>& distances,
std::unordered_map<value_type<T>, std::optional<value_type<T>>>& predecessors)
```

**Description**: Relaxes the edge from `u` to `v` given `w` and the distances. If the relaxation occurs, the `distances` and `predecessors` are updated.

**Parameters**:
- `u` the node at the start of the edge
- `v` the node at the end of the edge
- `w` the weight of the edge from `u` to `v`
- `distances` the mapping of vertices to their distances from the source
- `predecessors` the mapping of vertices to their predecessors along the shortest path from the source

**Returns**:
- `true` the edge was relaxed
- `false` otherwise

**Throws**: *None*

**Tests for This Function**: *N/A* (Untested Helper Function Used in `dijkstrasAlgorithm()`)

**Functions Required by Tests**: *N/A*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Pseudocode**:
```
If the New Distance to v (Through u) is Shorter Than the Current Distance to v:
    Update Distance to v and Predecessor of v Accordingly
    Return True (Found Shorter Path)

Otherwise, Return False (Did Not Find Shorter Path)
```

**Invocation**:
```cpp
relax<T>(u, v, w, distances, predecessors);
```

#### Dijkstra's Algorithm

```cpp
template <typename T>
std::list<value_type<T>> dijkstrasAlgorithm(const WeightedGraph<T>& graph, vertex_type<T> initial_node, vertex_type<T> destination_node)
```

**Description**: Performs [Dijkstra's Algorithm](https://canvas.tamu.edu/courses/136654/files/35930572/preview) (Slide 16) on `graph` starting at `initial_node` and returns a list with every node visited along the path from `initial_node` to `destination_node`.

**Parameters**:
- `graph` graph to find a path through
- `initial_node` the starting node in the graph
- `destination_node` the ending node in the graph

**Returns**: A list of all of the vertices along the shortest path from `initial_node` to `destination_node` or an empty list if no path exists.

**Throws**:
- `std::out_of_range` if either `initial_node` or `destination_node` are not in `graph`.

**Tests for This Function**: `dijkstra-complete_graph`, `dijkstra-complete_with_dropout`, `dijkstra-directed_tree`, `dijkstra-gnp_dag`, and `dijkstra-internet`

**Functions Required by Tests**: `dijkstrasAlgorithm()` (`relax()` Not Required But Highly Recommended)

**Time Complexity**: *O(nlog(n) + nm)* &ndash; Polynomial Time (Updating of Heap is *O(n)* not *O(log(n))* for Our Implementation)
- *n* is the number of vertices
- *m* is the number of edges

**Pseudocode**:
```
// Note: The Following 4 Lines are Already Completed in Starter Code
Initialize Empty Distances Map
Initialize Empty Predecessors Map
Initialize Empty Set (Stores Finalized Vertices, Sometimes Referred to as the "Cloud")
Initialize Empty Priority Queue (Tracks "Closest" Unfinalized Vertices)


// PART 1: Running Dijkstra's Algorithm
Initialize Distances and Predecessors (Hint: Look At Provided Helper Functions)

Add All Vertices to Priority Queue

While Priority Queue is Not Empty (i.e. Still Vertices Not in Cloud)
    Pop Top of Priority Queue (u)

    If Distance to u is Infinity:
        There Are No More Vertices Outside the Cloud That Are Reachable From the Starting Node
        Break From Loop, Completing Dijkstra's

    Add u to Cloud
    
    For Each Edge (u, v, w) in Adjacency List of u:
        If v is Already in Cloud:
            Vertex v Has Already Been Finalized, So There is Nothing to Update
            Continue to Next Edge

        If Relaxation of Edge (u, v, w) is Successful:
            Update Priority Queue (Hint: Look At Provided Helper Functions)


// PART 2: Finding Shortest Path to Destination Vertex of Interest
Initialize Empty List (Stores Shortest Path)

Start at the Destination Vertex of Interest
While Current Node Has a Predecessor:
    Add Current Node to Beginning of Shortest Path List
    Move on to Predecessor of Current Node

If Shortest Path List is Empty AND the Initial and Destination Nodes are Not the Same:
    There is No Path From the Initial Node to the Destination Node
    Return an Empty List

Otherwise, Add Initial Node to Beginning of Shortest Path List and Return the List
```

### Further Reading
#### Topological Sort
- [Topological sorting - Wikipedia](https://en.wikipedia.org/wiki/Topological_sorting)
- [Topological sorting - GeeksforGeeks](https://www.geeksforgeeks.org/topological-sorting/)

#### Dijkstra's Algorithm
- [Dijkstra's algorithm - Wikipedia](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
- [Dijkstra's algorithm - GeeksforGeeks](https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/)


### Application of Graphs & Graph Algorithms
Graphs are not commonly used directly by programmers to solve problems but properties of graphs are often used. You will learn much more about graphs in CSCE 411 - Design and Analysis of Algorithms.

## Run Tests

**First consult this guide: [`tests/README.md`](./tests/README.md)**

To run the tests, you need to rename [`main.cpp`](./src/main.cpp) or you need to rename the `int main` function within that file.

Execute the following commands from the `leyk-csce221-assignment-graph-algorithms` folder to accomplish what you need:

**Build all of the tests**
```sh
make -C tests -j12 build-all
```

**Run the test called `<test-name>`.** Replace `<test-name>` with the name of any `.cpp` file in the [`./tests/tests`](./tests/tests) folder.
```sh
make -C tests -j12 run/<test-name>
```

**Run every test** in the [`./tests/tests`](./tests/tests) folder.
```sh
make -C tests -j12 run-all -k
```

**Debugging tests** &ndash; For a detailed view, see [./tests/README.md](./tests/README.md).
```sh
make -C tests -j12 build-all -k
cd tests/build
gdb <test-name>
cd ../..
```
> Alex recommends you use `cgdb` which has the same commands as `gdb` but a better user interface. You can install it with `sudo apt install cgdb` on `WSL` or `brew install cgdb` on `MacOS` (provided you have [brew](https://brew.sh))

The first command builds the tests, the next enters the folder where the tests were build. The third invokes `gdb` (**use `lldb` if on Mac OSX**) which is used to debug the program by examining Segmentation Faults and running code line-by-line. Finally, the last command takes you back to the top-level directory.


## Incremental Testing:



## Turn In

Submit the following file **and no other files** to Gradescope:
- [ ] [`dijkstras-helpers.h`](src/dijkstras-helpers.h)
- [ ] [`top-sort-helpers.h`](src/top-sort-helpers.h)
- [ ] [`graph-algorithms.h`](src/graph-algorithms.h)
- [ ] ['graph-types.h'](src/graph-types.h)
- [ ] ['weighted-graphs.hpp'](src/weighted-graphs.hpp)
