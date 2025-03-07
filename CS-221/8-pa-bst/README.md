# Binary Search Tree

This Programming Assignment is the first where we are not implementing an STL class. There is no `std::binary_search_tree`. The function names attempt to mimic those of the STL.

> [!TIP]
> There is a [helpful video](https://youtu.be/wgzNIJBFgRs) for this assignment.

## Table of Contents
[Getting Started](#getting-started)

[Assignment](#assignment)

- [Implement Binary Search Tree](#implement-binary-search-tree)

- [Print Level By Level](#print-level-by-level)

- [Disclaimer About Comparator](#disclaimer-about-comparator)

[Run Tests](#run-tests)

[Incremental Testing and Debugging](#incremental-testing-and-debugging)

- [Visualizing Trees](#visualizing-trees)

- [Custom Assertions](#custom-assertions)

[Turn In](#turn-in)

## Getting started

Download this code by running the following command in the directory of your choice:
```sh
git clone git@github.com:tamu-edu-students/leyk-csce221-assignment-binary-search-tree.git && cd leyk-csce221-assignment-binary-search-tree
```
Open the code in your editor of choice. For instance, if you use VS Code:
```sh
code .
```
*Note:* On OSX you may need to enable the `code` command in VS Code with <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and typing "shell command." You can select the option to install the command, and then the above command will work.

## Assignment

### Implement Binary Search Tree

From your textbook:
> The property that makes a binary tree into a binary search tree is that for every node, *X*, in the tree, the values of all the items in its left subtree are smaller than the item in *X*, and the values of all the items in its right subtree are larger than the item in *X*.

All keys should be compared using the strict partial order defined by the comparator `comp`. In the event that you are attempting to insert a value and see a duplicate key, update the value stored at the key with the new value you are attempting to insert. Then `return`.

#### Implement the following functions:

----

## Implement Binary Search Tree


```cpp
// Default Constructor
BinarySearchTree();
```

**Description:** Constructs an empty Binary Search Tree.

**Parameters**: *None*

**Returns**: *None*

**Time Complexity:** *O(1)* &ndash; Constant Time

**Tests:** `constructor_default`, *commonly utilized*

----

```cpp
// Copy Constructor
BinarySearchTree( const BinarySearchTree & rhs );
```
**Description:** *Clones* all the elements from `rhs`. Preserves the same tree structure.

**Parameters**:
- `rhs` The Binary Search Tree to copy into a new tree.

**Returns**: *None*

**Time Complexity:** *O(`rhs.size()`)*

**Tests:** `constructor_copy`

----

```cpp
// Move Constructor
BinarySearchTree( BinarySearchTree && rhs );
```

**Description:** *Moves* the elements from `rhs` into a new binary search tree. `rhs` should be left empty after moving its elements.

**Parameters**:
- `rhs` The Binary Search Tree whose contents should be moved into a new tree.

**Returns**: *None*

**Time Complexity:** *O(1)* &ndash; Constant Time

**Tests:** `constructor_move`

----

```cpp
// Destructor
~BinarySearchTree();
```

**Description:** Destroys all of the objects in the Binary Search Tree.

**Parameters**: *None*

**Returns**: *None*

**Time Complexity:** *O(`size()`)*

**Tests:** *commonly utilized*

----
```cpp
const_reference root() const;
```

**Description:** Returns a `const` reference to the `pair` contained in the `_root` node.

**Parameters**: *None*

**Returns**: A `const_reference` to the key-value pair stored in the root node.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Tests:** - `root`

----
```cpp
bool empty() const;
```

**Description:** Returns whether the Binary Search Tree is empty.

**Parameters**: *None*

**Returns**:
- `true` if the tree is empty.
- `false` if the tree has elements.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Tests:** `clear_and_empty`

----

```cpp
size_type size() const;
```

**Description:** Returns the number of elements in the Binary Search Tree.

**Parameters**: *None*

**Returns**: The number of nodes/elements in the tree.

**Time Complexity:** *O(1)* &ndash; Constant Time

**Tests:** *commonly utilized*

----
```cpp
// Copy Assignment Operator
BinarySearchTree & operator=( const BinarySearchTree & rhs );
```

**Description:** *Clones* all the elements of `rhs` into an existing tree. You should make sure that the tree has been emptied before copying elements into it.

**Parameters**:
- `rhs` The Binary Search Tree whose elements should be copied.

**Returns**: A reference to the tree that has been copied into.

**Time Complexity:** *O(`size()` + `rhs.size()`)*

**Tests:** `operator_copy`

----

```cpp
// Move Assignment Operator
BinarySearchTree & operator= ( BinarySearchTree && rhs);
```

**Description:** *Moves* the elements of `rhs` into an existing tree. You should make sure that the tree has been emptied before moving elements into it. `rhs` should be left empty after its elements have been moved.

**Parameters**:
- `rhs` The Binary Search Tree whose elements should be moved.

**Returns**: A reference to the tree that has been moved into.

**Time Complexity:** *O(`size()`)*

**Tests:** `operator_move`

----

```cpp
void insert( const_reference x, node_ptr & t );
```

**Description:** Private `insert` helper. Recursively seeks the correct position to insert into the tree, and then constructs a new node containing the key-value pair `x`. If the key of `x` is already in the tree, replaces the value with the value of `x`. The contents of `x` should be *copied* into the tree. Nodes should be added as leaves to the tree.

**Parameters**:
- `x` The key-value pair to add to the tree. If the key already exists in the tree, update the value. Should be **copied** into the tree. *Note*: when searching for the key, the elements in nodes are key-value pairs. This means that `x.first` should be compared with the first value of the pair (can be accessed with `element.first`). When updating the value, you can use `element.second`.
- `t` A pointer to the current node in the tree. Should navigate from this node and recursively call the algorithm on child nodes.

**Returns**: *None*

**Time Complexity:** Approaches *O(`size()`)* for an unbalanced tree. Typically *O(log(`size()`))*

**Tests:** `insert_and_count`, `insert_and_find`,  *commonly utilized* - tested through `void insert( const_reference x );`

----

```cpp
void insert( pair && x, node_ptr & t );
```

**Description:** Private `insert` helper. Recursively seeks the correct position to insert into the tree, and then constructs a new node containing the key-value pair `x`. If the key of `x` is already in the tree, replaces the value with the value of `x`. The contents of `x` should be *moved* into the tree. Nodes should be added as leaves to the tree.

**Parameters**:
- `x` The key-value pair to add to the tree. If the key already exists in the tree, update the value. Should be **moved** into the tree. *Note*: when searching for the key, the elements in nodes are key-value pairs. This means that `x.first` should be compared with the first value of the pair (can be accessed with `element.first`). When updating the value, you can use `element.second`.
- `t` A pointer to the current node in the tree. Should navigate from this node and recursively call the algorithm on child nodes.

**Returns**: *None*

**Time Complexity:** *O(`size()`)* for an unbalanced tree. Typically *O(log(`size()`))*

**Tests:** `insert_and_count`, `insert_and_find`,  *commonly utilized* - tested through `void insert( pair && x );`

----

```cpp
void erase( const key_type & x, node_ptr & t);
```

**Description** Private `erase` helper. Starting at `root`, recursively seeks the correct position in the tree to erase (the node with key `x`). Once the node `t` to delete has been found, destroy `t`, reconnecting the surrounding nodes as required to maintain the structure of a BST.

**Parameters**:
- `x` The key to remove from the tree. *Note*: when searching for the key, the elements in nodes are key-value pairs. This means that `x` should be compared with the first value of the pair (can be accessed with `element.first`)
- `t` A pointer to the current node in the tree. Should navigate from this node and recursively call the algorithm on child nodes.

**Returns**: *None*

**Time Complexity:** *O(`size()`)* for an unbalanced tree. Typically *O(log(`size()`))*

**Tests:** `erase` - tested through `void erase( const key_type & x );`

----

```cpp
const_node_ptr min( const_node_ptr t ) const;
```

**Description:** Private `min` helper. Seeks the correct position of the minimum node and returns a pointer to that node. You could do this recursively or non-recursively.

**Parameters**:
- `t` A pointer to the current node in the tree. Should navigate from this node and recursively call the algorithm on child nodes.

**Returns**: A `const_node_ptr` to the node with the smallest key.

**Time Complexity:** *O(`size()`)* for an unbalanced tree. Typically *O(log(`size()`))*

**Tests:** `min` - tested through `const_reference min() const;`

----

```cpp
const_node_ptr max( const_node_ptr t ) const;
```

**Description:** Private `max` helper. Seeks the correct position of the maximum node and returns a pointer to that node. You could do this recursively or non-recursively.

**Parameters**:
- `t` A pointer to the current node in the tree. Should navigate from this node and recursively call the algorithm on child nodes.

**Returns**: A `const_node_ptr` to the node with the largest key.

**Time Complexity:** *O(`size()`)* for an unbalanced tree. Typically *O(log(`size()`))*

**Tests:** `max` - tested through `const_reference max() const;`

----

```cpp
bool contains( const key_type & x, const_node_ptr t ) const;
```

**Description:** Private `contains` helper. Finds if there is a node with key `x` in the tree. *Note*: when searching for the key, the elements in nodes are key-value pairs. This means that `x` should be compared with the first value of the pair (can be accessed with `element.first`).

**Parameters**:
- `x` The key to search for in the tree.
- `t` A pointer to the current node in the tree. Should navigate from this node and recursively call the algorithm on child nodes.

**Returns**:
- `true` If the key exists in the tree.
- `false` If the key does not exist in the tree.

**Time Complexity:** *O(`size()`)* for an unbalanced tree. Typically *O(log(`size()`))*

**Tests:** `insert_and_contains`, *frequently utilized* - tested through `bool contains( const key_type & x ) const;`

----

```cpp
node_ptr find( const key_type & key, node_ptr t );
```

**Description:** Private `find` helper. Seeks the correct position of the node with key `key`. Returns a pointer to the node if it exists in the tree and `nullptr` otherwise. *Note*: when searching for the key, the elements in nodes are key-value pairs. This means that `key` should be compared with the first value of the pair (can be accessed with `element.first`).

**Parameters**:
- `key` The key to search for in the tree.
- `t` A pointer to the current node in the tree. Should navigate from this node and recursively call the algorithm on child nodes.

**Returns**: A `node_ptr` to the node with key `key`. Returns `nullptr` if the key is not found.

**Time Complexity:** *O(`size()`)* for an unbalanced tree. Typically *O(log(`size()`))*

**Tests:** `insert_and_find`, *frequently utilized* - tested through `value_type & find( const key_type & key );`

----

```cpp
const_node_ptr find( const key_type & key, const_node_ptr t ) const;
```

**Description:** Private `find` helper. Seeks the correct position of the node with key `key`. Returns a `const` pointer to the node if it exists in the tree and `nullptr` otherwise. *Note*: when searching for the key, the elements in nodes are key-value pairs. This means that `key` should be compared with the first value of the pair (can be accessed with `element.first`).

**Parameters**:
- `key` The key to search for in the tree.
- `t` A pointer to the current node in the tree. Should navigate from this node and recursively call the algorithm on child nodes.

**Returns**: A `const_node_ptr` to the node with key `key`. Returns `nullptr` if the key is not found. This one is const, meaning that the returned pointer cannot be used to modify the node.

**Time Complexity:** *O(`size()`)* for an unbalanced tree. Typically *O(log(`size()`))*

**Tests:** `insert_and_find`, *frequently utilized* - tested through `const value_type & find( const key_type & key ) const;`

----

```cpp
void clear( node_ptr & t );
```

**Description:** Private `clear` helper. Recursively destroys every node in the Binary Search Tree and resets the `_size`.

**Parameters**:
- `t` A pointer to the current node in the tree. Should navigate from this node and recursively call the algorithm on child nodes.

**Returns**: *None*

**Time Complexity:** *O(`size()`)*

**Test Names:** `clear_and_empty` - tested through `void clear( node_ptr & t )`

----

```cpp
node_ptr clone ( const_node_ptr t ) const;
```

**Description:** Private `clone` helper. Recursively clones every node at and under `t`, and returns the node at the root of the cloned subtree. This function is used in Copy Construction and Copy Assignment.

**Parameters**:
- `t` A pointer to the root of the tree to clone. Should navigate from this node and recursively call the algorithm on child nodes.

**Returns**: A `node_ptr` to the root of the cloned subtree.

**Time Complexity:** *O(`rhs.size()`)* (From the copy constructor/assignment)

**Tests:** *private, untested*

----

```cpp
void printLevelByLevel( std::ostream & out ) const;
```

**Description:** Prints the tree in a pretty manner, with each level of the tree on its own line. See [this section of the document](#print-level-by-level) for more details.

**Parameters**:
- `out` The output stream to print to.

**Returns**: *None*

**Time Complexity:** *O(`size()`)*

**Tests:** `print_level_by_level`

----

#### Print Level By Level

You will write a method to perform a level-by-level traversal of a tree, printing nodes:

```
         7
        / \
       4   9
      / \ / \
     1  x 8  x
    /
   0
```

This traversal visits all nodes with the same depth value ("same level") before visiting any nodes on a lower level (with a greater depth.) Our version will iterate though the nodes from left to right. With regards to the tree pictured above, this would translate into the following visitation order: 7, 4, 9, 1, 8, 0

```
level 0 - 7
level 1 - 4, 9
level 2 - 1, 8
level 4 - 0
```

The printLevelByLevel function will require that you both perform the tranversal, print key value pairs, and print the null nodes:
```
(7, 0)
(4, 1) (9, 2)
(1, 3) null (8, 4) null
(0, 5) null null null null null null null
```

The elements are printed in (key, value) form. Nulls are represented by the string "null". Notice that each null child on level `(n - 1)` results in two null children on level `n` to proprly align the tree. 

To achieve this, you can use the [Breadth-First Search (BFS)](https://en.wikipedia.org/wiki/Breadth-first_search) algorithm for a tree. BFS involves traversing a tree level by level, and you can keep track of nodes to visit on a level using a queue. Add the children of nodes to the queue and only move to the next level when all current level nodes have been visited. You don't need separate queues for different levels; all nodes can go into a single queue. The front of the queue always points to the next node in the traversal. When you finish a level, it will point to the first node of the next level, provided you add the left node to the queue before the right node.

To ensure alignment in our triangular-like pattern for trees, upon dequeueing a null node, we should enqueue two more null nodes. This maintains alignment and distinguishes left and right subtrees. The algorithm stops when the next level has all NULL nodes, which can be determined by tracking non-null nodes on the next level. If we see a non-null node on the next level, we must continue to traverse; if there is not a non-null node we are done.

Print all nodes on a single level on a single line. To know when to insert the end-of-line delimiter `\n`, we must use an external counter that maintains the number of nodes encountered during the current level. If that counter is a power of 2 (2^1, 2^2, 2^3, ...) we are finished with that level. Upon reaching that end, we can insert that end-of-line deliiter and if the next level contains only null nodes, exit the loop.

[You may wish to use an STL queue in your solution](https://en.cppreference.com/w/cpp/container/queue)

----

#### Disclaimer About Comparator

Comparators are used to traverse the tree, as any tree node is based on comparisons to allow for easy traversal in this data strcture, like binary search would. You should call comparator in functions requiring a search, such as `find`, `insert`, and `erase` as opposed to using `<` or `>`.

The test cases check that you are not making unnecessary comparisons as you traverse through a binary search tree, as one of the key benefits of a binary search tree is its approximate `O(log(n))` search time. You should make sure that you are using the comparator a **max of two times** for every node traversed in the tree. Not doing so can cause the test cases to fail.

----

#### Further Reading
- [Binary Search Tree - GeeksforGeeks](https://www.geeksforgeeks.org/binary-search-tree-data-structure/)
- [Binary search tree - Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree)
- [Data Structure - Binary Search Tree](https://www.tutorialspoint.com/data_structures_algorithms/binary_search_tree.htm)
- Your textbook Chapter 4 Section 3 (page 132)
- [Class template bstree - 1.78.0](https://www.boost.org/doc/libs/1_78_0/doc/html/boost/intrusive/bstree.html) &ndash; Boost header with detailed reference at the bottom.

## Run Tests

To run the tests, you need to rename [`main.cpp`](./src/main.cpp) or you need to rename the `int main` function within that file.

Execute the following commands from the `assignment-binary-search-tree` folder to accomplish what you need:

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
make -C tests -j12 -k
```

**Debugging tests** 
```sh
make -C tests -j12 build-all -k
cd tests/build
gdb <test-name>
cd ../..
```
> Alex recommends you use `cgdb` which has the same commands as `gdb` but a better user interface. You can install it with `sudo apt install cgdb` on `WSL` or `brew install cgdb` on `MacOS` (provided you have [brew](https://brew.sh))

The first command builds the tests, the next enters the folder where the tests were build. The third invokes `gdb` (**use `lldb` if on Mac OSX**) which is used to debug the program by examining Segmentation Faults and running code line-by-line. Finally, the last command takes you back to the top-level directory.


## Incremental Testing and Debugging:

The ADT interface you build in this assignment effectively encapsulates the binary search tree. Users of the binary search tree cannot access the memory directly or traverse the underlying  tree. Normally, an iterator would be provided to access the elements sequentially. While many implementations of binary search trees provide an iterator, we have elected to exclude it from the assignment to simplify it. This means we are required to test it though the public interface provided by the ADT - largely through membership tests. This means that the `insert`, `find`, and `contains` tests, while complicated, are used extensively to test the other functions. We recommend you follow the following testing procedure to mitigate the high level of interdependence between test cases.

#### 1. Establishing Roots

First, complete `root()`, `size()`, and the default constructor `BinarySearchTree()`. If you have completed this trio correctly, `constructor_default.cpp` will pass. 

#### 2. The First Few Leafs

After passing `constructor_default.cpp` you should write your `insert` methods. `insert` can only be tested extensively in concert with membership tests (contains, find). Once `insert` is written, the `insert_and_count` test should pass without additional dependencies. This test will count the number of comparisons made on the path to an insertion ensuring it is bounded reasonably (verifying the insert method is placing items at the correct depth.) `insert_and_count` also expects that you will free the memory allocated during an insert. Thus, a destructor is required for test completion.

#### 3. Uptake (Traversing the Tree)

After completing the `find` method, the `insert_and_find` method passes. After this test case passes, the `insert_and_move` and the `insert_find_and_count` methods should be tested. The former will require the move variant of the `insert` method to be implemented. The latter should pass the `find` and `insert` methods are properly written. The `insert_and_contains` method should also be completed at this stage.

#### 4. Pruning, Flowering & Reseeding

All further methods are able to be completed assuming the dependencies above are fully working.

### Debugging:

#### Visualizing Trees:

There are two methods we provide to visualize trees. The first, `printTree`, is a simple helper function which will print the tree to a debug stream. The tree is printed on its side - indentation indicates increasing depth. There is a more complicated function, `vizTree` which prints out the tree in a standard format called Graphviz. It can be copied and pasted into an [online viewer](http://dreampuf.github.io/GraphvizOnline) to render a full image of the tree.

```
BinarySearchTree<int, int> bst;
bst.insert({ 0, 2 });
printTree(bst); // Print tree
vizTree(bst); // Print Graphviz
```

#### Debug Trees in Test Cases:

Some test cases will optionally print the offending tree when a failure occurs. This is disabled by default but can be enabled by adding special preprocessor directives to the BinarySearchTree.h header file (by convention, they are grouped at the top of the file with the includes): 

To enable this, you must specify the output format. You can either use Graphviz or ASCII but not both concurrently. Pick whichever line suits you better:

```
// Print out debug trees in Graphviz format
#define TREE_ASSERT_VIZ
// Print out debug trees in ascii using tabular depth
#define TREE_ASSERT_PRINT
```

By default, trees will not be printed if they have more than 15 nodes. This limit is adjustable and can also be overridden with a define:

```
// Increase the limit to 50 nodes
#define TREE_ASSERT_PRINT_SZ_LIMIT 50
``` 

#### Custom Assertions:

If you read through the testing code, you may see custom test assertions. They are defined in `tree_assert.h` in `include`. Here a brief summary of their behavior:

- `ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(pairs, tree)` - Ensures all (key, value) pairs are in the tree. This is done by first checking if `contains` succeeds. If it reports the value is contained in the tree, a `find` is attempted.

- `INSERT_AND_ASSERT_COMPARISONS_BETWEEN(lower_bound, upper_bound, tree, pair)` - injects a custom comparator to ensure the number of comparisons made with the comparator is between [lower_bound, upper_bound] inclusive. This allows us to ensure you are inserting the pair at the correct depth.

- `ASSERT_VALUE_IN_TREE(expected_value, tree, key)` - attempts a `find` to ensure the value is in the tree.

## Main.cpp:
In `main.cpp`, the code attempts to build and print a tree. Note that the names are used as the keys rather than the integers. This means that the binary tree is lexicographically ordered by the string key (not strictly numerically.)

You can compile and run main to see the output of the tree against your print level by level code. You can also use this to test your own code. If you encounter any errors with `make` or tests delete the executable made in compilation.

## Turn In

Submit the following file **and no other files** to Gradescope:
- [ ] [`BinarySearchTree.h`](src/BinarySearchTree.h)
