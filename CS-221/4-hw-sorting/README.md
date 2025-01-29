# Sorting & Comparing

One of the goals of this assignment is to implement the `O(n^2)` sorting algorithms using a similar interface to `std::sort`. These algorithms can be used to sort data structures which implement random access iterators. This includes the [`std::vector`](https://en.cppreference.com/w/cpp/container/vector) data structure you completed in the last assignment.

The other goal of this assignment is to expand your understanding of comparators by demonstrating how they might be implemented. You will use comparators in this PA and will continue to work with them in future PAs, so it is important that you understand how to work with them.

## Getting Started
Download this code by running the following command in the directory of your choice:
```sh
git clone git@github.com:tamu-edu-students/leyk-csce221-assignment-sorting.git && cd leyk-csce221-assignment-sorting
```

Open the code in your editor of choice. For instance, if you use VS Code:
```sh
code .
```
*Note:* On OSX you may need to enable the `code` command in VS Code with <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and typing "shell command." You can select the option to install the command, and then the above command will work.

## Assignment
### Implement Sorting Algorithms
You are to implement `bubble_sort()`, `insertion_sort()`, and `selection_sort()` using iterators. 

**HINT 1:** Implement `swap()` first. This is going to be used in all the sorting algorithms. Move operations are your friend.

**HINT 2:** Be careful to use move semantics whenever possible to avoid making unnecessary copies. The biggest area where students forget to do this is when **storing array elements** in temporary variables (as is done in some implementations of insertion sort). If you are failing the `sorts_efficient` test due to extra allocations or a segmentation fault, this could be a reason why.

#### You must implement the following functions:

`void swap(T & a, T & b) noexcept`

**Description**: Swaps the position of two elements. We want to do this efficiently, so be sure to use move semantics in order to avoid making unnecessary copies.

**Time Complexity**: *O(1)*

**Used in**: *bubble_comparisons*, *bubble_sorts*, *insertion_comparisons*, *insertion_sorts*, *selection_sorts*, *sorts_efficient*, *swap*

----

`void bubble(RandomIter begin, RandomIter end, Comparator comp = Comparator{})`

**Description**: Sorts elements in the range \[`begin`, `end`) using the bubble sort algorithm. This sort should be optimized so the runtime function is about 1/2 n<sup>2</sup> in the worst case. Compare elements using `comp`, which is std::less by default.

**Time Complexity**: *O(n<sup>2</sup>)*

**Used in**: *bubble_comparisons*, *bubble_sorts*, *sorts_efficient*

----

`void insertion(RandomIter begin, RandomIter end, Comparator comp = Comparator{})`

**Description**: Sorts elements in the range \[begin, end) using the insertion sort algorithm. Compare elements using `comp`, which is std::less by default.

**Time Complexity**: *O(n<sup>2</sup>)*

**Used in**: *insertion_comparisons*, *insertion_sorts*, *sorts_efficient*

----

`void selection(RandomIter begin, RandomIter end, Comparator comp = Comparator{})`

**Description**: Sorts elements in the range \[begin, end) using the selection sort algorithm. Compare elements using `comp`, which is std::less by default.

**Time Complexity**: *O(n<sup>2</sup>)*

**Used in**: *selection_comparisons*, *selection_sorts*, *sorts_efficient*

----

An additional 5 points is earned if you do not allocate memory during any of the sorting algorithms. You should not need to do this, so you can almost consider these points as "*free*".

It may be helpful for you to consult:
- Reference for Iterators: https://en.cppreference.com/w/cpp/iterator/iterator
- Reference for Sorts: https://en.cppreference.com/w/cpp/algorithm/sort
- Visualization of Sorting Algorithms: https://pulchroxloom.github.io/visualizing_sorts/
- Videos of Sorting Algorithms Visualized: https://youtu.be/kPRA0W1kECg

### Student.h
There are two functions to complete in `Student.h`. You can complete them in the order listed.

----
`GPAComparator::operator()`

**Description:** Describes an ordering ascending on GPA primarily and descending on ID secondly.

**Complexity: O(1)**

----
`KnownOrderComparator::operator()`

**Description:** Describes an ordering that matches the ordering of `_student_ranking`.

**Complexity: O(n)**

### Run The Tests

**First consult this guide: [`tests/README.md`](./tests/README.md)**

Execute the following commands from the `sorting-vectors` folder to accomplish what you need:

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

## Turn In
Submit the modified `sorting.h` and `Student.h` to Gradescope. In general, submit everything except `main.cpp` (if it exists).
