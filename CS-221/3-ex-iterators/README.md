# Exercise - Iterators
If you've worked with pointers and dynamic memory, you've probably noticed that working directly with the heap can be difficult and sometimes problematic. You've also likely worked with `std::vector` before, which uses dynamic memory but does not have the same issues. Why is this? This is because the C++ STL is designed in such a way that lower-level interactions are abstracted to provide memory and data safety. The most consistent way this is done for C++ data structures is through iterators. Iterators essentially act as a wrapper class around a pointer to give the user access to only the most necessary features of the structure, as well as provide a general way for moving through containers.

For example:

Method 1: Using pointers
```cpp
// Iterating through an array
int* array = new int[5];
int* arrayNext = ++array;

// Iterating through a linked list
Node<int>* n = new Node<int>(4, new Node<int>(5, nullptr));
Node<int>* nextNode = n->next;
```
**NOTE**: You will learn about how to navigate through other data structures throughout the semester, and you will quickly find that all of these ways are fairly different.

Method 2: Using STL and iterators
```cpp
// Iterating through an array
std::vector<int> v(5);
auto arrayNext = ++v.begin();

// Iterating through a linked list
std::list<int> l = {4, 5};
auto nextNode = ++l.begin();

// Iterating through a hash set (You will learn about these later)
std::unordered_set<int, int> m = {1, 2, 3}
auto nextVal = ++m.begin();
```

The C++ STL is organized in such a way that algorithms that work on data structures can be generalized assuming that the container has iterators defined for it. It is with this in mind that one of the goals of this course is to familiarize you with how iterators work and how to use them.

## Table of Contents
[Getting Started](#getting-started)

[Assignment](#assignment)

- [Implement a Vector Iterator](#implement-a-vector-iterator)

    - [Aliases](#aliases)
    
    - [Data Members](#data-members)
    
    - [Implement the Following functions](#implement-the-following-functions)
    
- [Implement Vector Functions for Iterating](#implement-vector-functions-for-iterating)

- [Further Reading](#further-reading)

[Using Iterators](#using-iterators)

[Run Tests](#run-tests)

[Turn In](#turn-in)

## Getting started

Download this code by running the following command in the directory of your choice:
```sh
git clone git@github.com:tamu-edu-students/leyk-csce221-exercise-iterators && cd leyk-csce221-exercise-iterators
```

Open the code in your editor of choice. For instance, if you use VS Code:
```sh
code .
```
*Note:* On OSX you may need to enable the `code` command in VS Code with <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and typing "shell command." You can select the option to install the command, and then the above command will work.

## Assignment
The assignment provides you with a very limited `Vector_Basic` data structure, which covers the basic necessities for creating a vector iterator. It is your goal to design an iterator for a vector using the provided functions. If done correctly, this code can be used in the first programming
assignment.

### Implement a Vector Iterator
#### Aliases
Aliases in C++ are a way of giving custom names to types. This is especially useful if a type is long and you would like to give it a shorter name, or if you want to define characteristics for a class. For the `iterator` class, these aliases are used for storing information about the iterator.

| Type | Alias | Description |
| ---- | ----- | ----------- |
| `iterator_category` | `std::random_access_iterator_tag` | This defines the iterator as as random access iterator. This is a category of iterators that can use indexing to access elements. |
| `value_type` | `T` | The type for elements that the iterator points to. This is because it depends on what the container holds. |
| `difference_type` | `ptrdiff_t` | The type for differences between iterators. This is just the difference between pointers. |
| `pointer` | `T*` | The type for addressing elements that the iterator points to. This is because it should be the memory address of elements in the container. |
| `reference` | `T&` | The type for referencing elements that the iterator points to. This is because it should be a reference to elements in the container. |

These aliases are used mainly for determining characteristics about the iterator and elements in the container.

For example, if I was given an iterator of type `iter`, I might want to know the type of elements it holds.

```cpp
// This returns the sum of the elements pointed to by the iterators
// Because the return type must match the value returned, we need to
// know what the iterators point to
// We can get the type by accessing the value_type alias of the iter type.
iter::value_type addElements(iter& i1, iter& i2) {
    return (*i1) + (*i2);
}
```

#### Data Members
Your iterator needs to have some kind of private member to keep track of what the iterator is pointing to. This needs to be general enough to fit whatever the container holds.

#### Implement the Following Functions
These methods need to be implemented for the `Vector_Basic` iterator.

```cpp
iterator()
```

**Description**: Creates a default iterator.

**Parameters**: *None*

**Returns**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
[[nodiscard]] reference operator*() const noexcept
```

**Description**: Accesses the element the iterator points to.

**Parameters**: *None*

**Returns**: A reference to the element the iterator points to.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
[[nodiscard]] pointer operator->() const noexcept
```

**Description**: Accesses a member or method of the element the iterator points to.

**Parameters**: *None*

**Returns**: A pointer to the element the iterator points to.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
iterator& operator++() noexcept
```

**Description**: Prefix increment (++i). The iterator should be advanced forward by one element and returned.

**Parameters**: *None*

**Returns**: A reference to the advanced iterator.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
iterator operator++(int) noexcept
```

**Description**: Postfix increment (i++). The iterator should be advanced forward by one element, but a copy of before it was advanced should be returned.

**Parameters**: *None*

**Returns**: A copy of the iterator before it was advanced.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
iterator& operator--() noexcept
```

**Description**: Prefix decrement (--i). The iterator should be retreated backward by one element and returned.

**Parameters**: *None*

**Returns**: A reference to the retreated iterator.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
iterator operator--(int) noexcept
```

**Description**: Postfix decrement (i--). The iterator should be retreated backward by one element, but a copy of before it was retreated should be returned.

**Parameters**: *None*

**Returns**: A copy of the iterator before it was retreated.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
iterator& operator+=(difference_type offset) noexcept
```

**Description**: Advances the iterator forward by an offset.

**Parameters**:
- `offset` How far to advance the iterator.

**Returns**: A reference to the iterator after it was advanced `offset` forward.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
[[nodiscard]] iterator operator+(difference_type offset) const noexcept
```

**Description**: Returns a copy of the iterator advanced forward by an offset.

**Parameters**:
- `offset` How far the copy should be ahead of the iterator.

**Returns**: An iterator `offset` ahead of the current iterator.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
iterator& operator-=(difference_type offset) noexcept
```

**Description**: Retreats the iterator backwards by an offset.

**Parameters**:
- `offset` How far to retreat the iterator.

**Returns**: A reference to the iterator after it was retreated `offset` backwards.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
[[nodiscard]] iterator operator-(difference_type offset) const noexcept
```

**Description**: Returns a copy of the iterator retreated backwards by an offset.

**Parameters**:
- `offset` How far the copy should be behind the iterator.

**Returns**: An iterator `offset` behind the current iterator.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
[[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept
```

**Description**: Finds how far apart two iterators are. Used as `iter1 - iter2`.

**Parameters**:
- `rhs` The iterator to compare with the current iterator

**Returns**: The distance between the the current iterator and `rhs`.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
[[nodiscard]] reference operator[](difference_type offset) const noexcept
```

**Description**: Gets a reference an element offset from the iterator.

**Parameters**:
- `offset` How far from the iterator the desired element is.

**Returns**: The element `offset` ahead of the iterator.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
[[nodiscard]] bool operator==(const iterator& rhs) const noexcept
```

**Description**: Checks if two iterators are equal.

**Parameters**:
- `rhs` The iterator to compare the current iterator to.

**Returns**: 
- `true` If the two iterators are equal
- `false` If they are not

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
[[nodiscard]] bool operator!=(const iterator& rhs) const noexcept
```

**Description**: Checks if two iterators are **not** equal.

**Parameters**:
- `rhs` The iterator to compare to.

**Returns**: 
- `true` If the two iterators are not equal
- `false` If they are equal

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
[[nodiscard]] bool operator<(const iterator& rhs) const noexcept
```

**Description**: Checks if an iterator comes before another.

**Parameters**:
- `rhs` The iterator to compare to.

**Returns**: 
- `true` If the current iterator comes before `rhs`
- `false` If it does not

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
[[nodiscard]] bool operator>(const iterator& rhs) const noexcept
```

**Description**: Checks if an iterator comes after another.

**Parameters**:
- `rhs` The iterator to compare to.

**Returns**:
- `true` If the current iterator comes after `rhs`
- `false` If it does not

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
[[nodiscard]] bool operator<=(const iterator& rhs) const noexcept
```

**Description**: Checks if an iterator comes before **or** is equal to another.

**Parameters**:
- `rhs` The iterator to compare to.

**Returns**: 
- `true` If the current iterator comes before or is equal to `rhs`
- `false` If it is not

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
[[nodiscard]] bool operator>=(const iterator& rhs) const noexcept
```

**Description**: Checks if an iterator comes after **or** is equal to another.

**Parameters**:
- `rhs` The iterator to compare to.

**Returns**: 
- `true` If the current iterator comes after or is equal to `rhs`
- `false` If it is not

**Time Complexity**: *O(1)* &ndash; Constant Time

----

### Implement Vector Functions for Iterating
The following functions should be implemented to get iterators for a `Vector_Basic` container.

```cpp
iterator begin() noexcept
```

**Description**: Gets an iterator to the first element in the container. If the container is empty, this should be equivalent to `end()`.

**Parameters**: *None*

**Returns**: An `iterator` pointing to the first element in the container.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
iterator end() noexcept
```

**Description**: Gets an iterator past the last element in the container. If the container is empty, this should be equivalent to `begin()`.

**Parameters**: *None*

**Returns**: An `iterator` pointing past the last element in the container.

**Time Complexity**: *O(1)* &ndash; Constant Time

----

### Further Reading
Feel free to read about `const_iterator` and `reverse_iterator` in C++. However, you need only implement `iterator` for this assignment.

It may be helpful for you to consult:
- Reference for Iterators: https://en.cppreference.com/w/cpp/iterator/iterator
- Reference for Vector Begin: https://en.cppreference.com/w/cpp/container/vector/begin
- Reference for Vector End: https://en.cppreference.com/w/cpp/container/vector/end

## Using Iterators
For this assingment, you were tasked with creating an iterator for a simplistic vector. But what can these iterators actually be used for? The most common way they are used is for iterating through elements in a container.

```cpp
using vec_iter = std::vector<int>::iterator;

std::vector<int> v = {1, 2, 3, 4};

for (vec_iter i = v.begin(); i != v.end(); ++i) {
    std::cout << *i << std::endl;
}
```

This is a method of iterating through a vector using iterators. Much like pointers, you can access the elements pointed to by dereferencing the iterator. You probably also notice that working with iterators seems to require a lot more typing than just using indexing, so why even bother? This may be true for something like `std::vector`, but not all containers have indexing. Other containers like `std::list`, `std::map`, and `std::unordered_map` don't have indexing, so this is not a generalized option for all C++ data structures. By using iterators, we can have generic acessing of elements like for the below code snippet:

```cpp
template <class Container>
void printAll(const Container& c) {
    for (auto i = c.begin(); i != c.end(); ++i) {
        std::cout << *i << std::endl;
    }
}
```

This function will successfully print all contents of a container as long as it has iterators defined for it, thus making iterators very useful for working with an C++ data structure.

**NOTE**: You may have noticed the change from using an alias for the iterator type to using `auto`. `auto` is a C++ keyword that allows for type deduction. This can be useful for replacing long type names or for figuring out types you don't know. While it may seem nice and simple, it shouldn't be used carelessly. The compiler will do its best to guess the correct type, but sometimes it can guess wrong, leading to possible overflow or other such type-dependent errors. 

Another feature of using iterators is the use of range-based for loops, sometimes called for-each or enhanced for loops in other languages. This feature works for any container that has iterators defined, as it uses them behind-the-scenes.

```cpp
std::vector<int> v = {1, 2, 3, 4};

for (int& elem: v) {
    std::cout << elem << std::endl;
}
```

This performs the same operation as above by getting a reference to every element in the vector. This allows for easy accessing of every element in a container, and can even be used to change the elements of the container. For example, we could double every element in the vector with the following code:

```cpp
for (int& elem: v) {
    elem *= 2;
}
```

By getting a reference to every element in the vector, any changes to it affect the actual value in memory. This can be prevented by either taking a copy instead of a reference of every element in the container, or by taking a const reference of the elements.

## Run Tests

Execute the following commands from the `leyk-csce221-exercise-iterators` folder to accomplish what you need:

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

**Debugging tests** &ndash;
```sh
make -C tests -j12 build-all -k
cd tests/build
gdb <test-name>
cd ../..
```
> Alex recommends you use `cgdb` which has the same commands as `gdb` but a better user interface. You can install it with `sudo apt install cgdb` on `WSL` or `brew install cgdb` on `MacOS` (provided you have [brew](https://brew.sh))

The first command builds the tests, the next enters the folder where the tests were build. The third invokes `gdb` (**use `lldb` if on Mac OSX**) which is used to debug the program by examining Segmentation Faults and running code line-by-line. Finally, the last command takes you back to the top-level directory.

## Turn In

Submit the following file **and no other files** to Gradescope:
- [ ] [`Vector_Basic.h`](src/Vector_Basic.h)
