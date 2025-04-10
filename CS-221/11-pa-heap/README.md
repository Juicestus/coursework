# Priority Queue

While a Priority Queue can be implemented in a variety of ways, in practice they are often implemented as a form of a heap. For the purposes of this assignment you are to implement a [Binary Max-Heap](https://github.com/pulchroxloom/binary-heaps/raw/main/Binary%20Heaps%20-%20Dante.pdf).

## Getting started

Download this code by running the following command in the directory of your choice:
```sh
git clone git@github.com:tamu-edu-students/leyk-csce221-assignment-priority-queue.git && cd leyk-csce221-assignment-priority-queue
```

Open the code in your editor of choice. For instance, if you use VS Code:
```sh
code .
```
*Note:* On OSX you may need to enable the `code` command in VS Code with <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and typing "shell command." You can select the option to install the command, and then the above command will work.

## Assignment

### Implement Binary Heap

You are to implement the below `PriorityQueue` functions keeping in mind the comparator `comp` and the container `c` within the class.

In C++, `PriorityQueue` uses the `std::less<T>` comparator by default, and this comparator is used to implement a Max-Heap. Ensure that your heap is a Max-Heap if you use `std::less<T>` and a Min-Heap if you use `std::greater<T>`. This is demonstrated by the [`main.cpp`](src/main.cpp) file.

#### Implement the following functions:

**Note:** *These instructions are replicated in the Header File so that one does not need to constantly reference this README file for a guide. You can delete the comments when you're done or if you'd rather not use them.*

----

`void upheap(size_type index);` &ndash; Private Helper

**Description:** Recursively (or Iteratively) swap the value at index `index` up the heap until it is in the correct position. This should result in the heap properties being restored.

**Time Complexity:** Logarithmic in the number of elements in `*this`.

**Used By:** `push( const value_type& )`, `push( value_type&& )`

----

`void downheap(size_type index);` &ndash; Private Helper

**Description:** Recursively (or Iteratively) swap the value at index `index` down the heap until it is in the correct position. This should result in the heap properties being restored.

**Time Complexity:** Logarithmic in the number of elements in `*this`.

**Used By:** `pop()`

----

`const_reference top() const;`

**Description:** Return a const reference to the element at the top of the heap.

**Time Complexity:** Constant.

**Test Names:** *push_and_top*, *push_pop_and_top*

----

`bool empty() const;`

**Description:** Return whether the heap is empty. This is the same as whether the underlying container, `c`, is empty.

**Time Complexity:** Constant.

**Test Names:**  *push_and_empty*

----

`size_type size() const;`

**Description:** Return the number of elements in the heap. This is the same as the number of elements in the underlying container, `c`.

**Time Complexity:** Constant.

**Test Names:** *utilized often*

----

`void push( const value_type& value );`

**Description:** Inserts element using copy semantics and uses `upheap` to restore the heap properties of the underlying container, `c`.

**Time Complexity:** Logarithmic in the number of elements in `*this`.

**Uses:** `upheap( size_t )`

**Test Names:**  most strenuously *push_and_top*, *push_pop_and_top*, *push_and_count*

----

`void push( value_type&& value );`

**Description:** Inserts element using move semantics and uses `upheap` to restore the heap properties of the underlying container, `c`.

**Time Complexity:** Logarithmic in the number of elements in `*this`.

**Uses:** `upheap( size_t )`

**Test Names:**  *push_and_empty*, *push_and_top*, *push_move_and_efficent*

----

`void pop();`

**Description:** Removes the top element by replacing it with the last element in the container, then deleting the last element. `downheap` should then be called on the new top to restore the heap properties of the underlying container, `c`.

**Time Complexity:** Logarithmic in the number of elements in `*this`.

**Uses:** `downheap( size_t )`

**Test Names:** *push_pop_and_top*

----

#### Further Reading
- [Dante's Binary Heap Slides](https://github.com/pulchroxloom/binary-heaps/raw/main/Binary%20Heaps%20-%20Dante.pdf)
- [Binary Heap - GeeksforGeeks](https://www.geeksforgeeks.org/binary-heap/)
- [Binary heap - Wikipedia](https://en.wikipedia.org/wiki/Binary_heap)
- [Design and Analysis Binary Heap - Tutorialspoint](https://www.tutorialspoint.com/design_and_analysis_of_algorithms/design_and_analysis_of_algorithms_binary_heap.htm)
- Your textbook Chapter 6 Section 3 (page 247)
- [Binary Heaps - andrew.cmu.ed](https://www.andrew.cmu.edu/course/15-121/lectures/Binary%20Heaps/heaps.html) &ndash; Carnegie Mellon University page on Binary Heaps.

### To Be Determined (Application of Binary Heaps)

Binary Heaps are used to handle sorting data and retrieving it efficiently. They can be used in scheduler applications among many others. We will see usage of Priority Queues later in the course with Dijkstra's Algorithm whose time complexity depends on how efficiently a Priority Queue can be implemented. It turns out that Binary Heaps are not the very best way to do a Priority Queue (for Dijkstra's Algorithm).

## Run Tests

**First consult this guide: [`tests/README.md`](./tests/README.md)**

To run the tests, you need to rename [`main.cpp`](./src/main.cpp) or you need to rename the `int main` function within that file.

Execute the following commands from the `leyk-csce221-assignment-priority-queue` folder to accomplish what you need:

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

This assignment is fairly simple to test. The `size`, `empty`, and `top` functions are simple and are utilized often. These should be implemented first. `push` is required by all tests. After these functions, `push_and_count`, `push_and_empty`, and `push_and_top` will pass. After implementing `pop`, `push_move_and_efficent` and `push_pop_and_top` will pass.

## Main.cpp:
In `main.cpp`, the code creates a min-heap and a max-heap and pushes and pops a series of small numbers. The numbers are printed as they are popped with a prompt indicating the expected ordering. If the ordering matches, the code should be run against more sophisticated tests.

## Turn In

Submit the following file **and no other files** to Gradescope:
- [ ] [`PriorityQueue.h`](src/PriorityQueue.h)
