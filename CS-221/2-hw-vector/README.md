# Vector
The overall goal of this assignment is to begin programming data structures by implementing your own slimmed-down [`vector`](https://en.cppreference.com/w/cpp/container/vector).

A walkthrough video for this programming assignment can be found [here](https://www.youtube.com/watch?v=_3OtTkszAzs), and serves as an additional resource to this README.

## Table of Contents
[Getting Started](#getting-started)

[Assignment](#assignment)

- [Implement Vector](#implement-vector)

    - [You must implement the following functions for `Vector`](#you-must-implement-the-following-functions-for-vector)
    
- [Implement the Vector's Iterator](#implement-the-vectors-iterator)
    
    - [You must implement the following functions for `iterator`](#you-must-implement-the-following-functions-for-iterator)
    
- [One Last Function](#one-last-function)

- [Further Reading](#further-reading)

[Run Tests](#run-tests)

[Turn In](#turn-in)

## Getting Started
Use `CTRL+SHIFT+V` in VSCode to read the formatted version of this .md, or you can use the GitHub assignment repo.

Download this code by running the following command in the directory of your choice:

`git clone git@github.com:tamu-edu-students/leyk-csce221-assignment-vector.git`

Open the code in your editor of choice. For instance, if you use VS Code:

`code .`

*Note* on On OSX you may need to enable the `code` command in VS Code with `Cmd+Shift+P` and typing "shell command." You can select the option to install the command, and then the above command will work.

## Assignment
### Implement Vector
You are to implement `Vector`. A `Vector` is a dynamic array; a contiguous structure which dynamically updates its **capacity** as needed - following a doubling resize strategy. As a result, most operations take constant time to complete. However, the amount of wasted space (`capacity - size`) is often equivalent to the amount used. Therefore, when compared to other containers, `Vector` is not a particularly spatially efficient storage structure.

You may have already used `std::vector` in previous assignments, so your `Vector` should behave similarly. The big difference is that `std::vector` decreases its capacity when enough `pop_back` operations occur, whereas your `Vector` <u>does not ever need to reduce its capacity</u>.

### Iterators
A container is a data structure which holds a collection of elements, such as `std::vector`, `std::list`, etc...

Iterators are a means of traversing a container (i.e. vector, list, etc...), best explained as a "fancy" pointer or pointer wrapper class in C++. They allow for standard traversal and access of containers without requiring you to know the underlying implementation of the container.

Iterators are used in almost all standard library containers and their methods, and become very helpful for more complex structures down the line.

In the context of this assignment, iterators may appear redundant given your familiarity with standard accessing methods. However, teaching iterators in this structure not only explains `std::vector` methods relying on iterators, but opens you up to a greater understanding of future structures which are much more complex.

**HINT:** Do the following functions first.
- `Vector()`
- `Vector(size_t count)`
- `~Vector()`
- `size_t size() const noexcept`
- `size_t capacity() const noexcept`
- `T& operator[](size_t pos)`
- `const T& operator[](size_t pos)`
- Complete the `iterator` class

More info about the above functions can be seen below. If you complete the above functions, you should be able to complete any other function and it should pass. The above are the only functions which are "depended on." *Please note that there may be minor exceptions to this rule.*

#### You must implement the following functions for `Vector`:
----

```cpp
// Default Constructor
Vector() noexcept
```

**Description:**  Create an empty vector.

Note: There can be different defintions of "empty" or "default", but we expect an empty vector to have a capacity of 0. What does this mean we should initialize `array` to?

**Parameters**: *None*

**Returns**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_constructor*

**Functions Used By This Test:** `Vector()`, `size()`, `capacity()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/vector

----

```cpp
// Parameterized Constructor
Vector(size_t count, const T& value)
```

**Description:** Constructs the container with `count` copies of elements with value `value`.

**Parameters**:
- `count` The size of the vector to create
- `value` The element to fill the vector with

**Returns**: *None*

**Time Complexity**: *O(`count`)*

**Test For This Function:** *vector_initialization_constructor*

**Functions Used By This Test:** `Vector(count, begin)`, `operator[](pos)`, `~Vector()`, `size()`, `capacity()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/vector

----

```cpp
// Parameterized Constructor
explicit Vector(size_t count)
```

**Description:** Constructs the container with `count` *default-inserted* instances of `T`. No copies are made.

Hint: You may use [the array initialization list](https://en.cppreference.com/w/c/language/array_initialization). Alternatively, you can create a "default" instance of `T` using `T()`.

**Parameters**:
- `count` The size of the vector to create

**Returns**: *None*

**Time Complexity**: *O(`count`)* &ndash; Linear Time

**Test For This Function:** *vector_default_inserted_constructor*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `~Vector()`, `size()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/vector

----

```cpp
// Copy Constructor
Vector(const Vector& other)
```

**Description:** Constructs the container with the copy of the contents of `other`.

**Parameters**:
- `other` The vector to make a copy of. A deep copy should be made.

**Returns**: *None*

**Time Complexity**: *O(`other.size()`)* &ndash; Linear Time

**Test For This Function:** *vector_copy_constructor*

**Functions Used By This Test:** `Vector()`, `Vector(const Vector& other)`, `push_back()`, `operator[](pos)`, `size()`, `capacity()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/vector

----

```cpp
// Move Constructor
Vector(Vector&& other) noexcept
```

**Description:** Constructs the container with the contents of `other` using move semantics. After the move, `other` is guaranteed to be `empty()` (i.e. `other` should be returned to an "empty/default" state).

**Parameters**:
- `other` The vector we are moving contents from into `this` new vector. `other` should be left empty/hollow after this operation.

**Returns**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_move_constructor*

**Functions Used By This Test:** `Vector(count)`, `Vector(Vector&& other)`, `push_back()`, `operator[](pos)`, `size()`, `capacity()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/vector

----

```cpp
// Destructor
~Vector()
```

**Description:** Destructs the vector. Any memory that has been alllocated by the Vector object must be deallocated to ensure that there are no memory leaks.

**Parameters**: *None*

**Returns**: *None*

**Time Complexity**: *O(n)\**

**Test For This Function:** No specific test, but frequently required by tests.

**Functions Used By This Test:** *N/A*

**Link:** https://en.cppreference.com/w/cpp/container/vector/~vector

**\*** Depends on the element's destructor, we are assuming each element's destructor is O(1)

----

```cpp
// Copy Assignment Operator
Vector& operator=(const Vector& other)
```

**Description:** Replaces the contents with a deep copy of the contents of `other`. The target vector and `other` should be two identical yet distinct vectors after this function completes.

**Parameters**:
- `other` The vector to make a copy of. The contents of the target vector should be deleted and replaced with a copy of `other`.

**Returns**: A reference to the target `Vector`

**Time Complexity**: *O(`size() + other.size()`)*

**Test For This Function:** *vector_copy_operator*

**Functions Used By This Test:** `Vector(count)`, `operator=(const Vector& other)`, `~Vector()`, `operator[](pos)`, `size()`, `capacity()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/operator%3D

----

```cpp
// Move Assignment Operator
Vector& operator=(Vector&& other) noexcept
```

**Description:** Replaces the contents with those of `other` using move semantics (i.e. the data in other is moved from other into this container). After the move, `other` is guaranteed to be `empty()` (i.e. `other` should be returned to an "empty/default" state).  

**Parameters**:
- `other` The vector whose contents should be *moved* into the target vector. The contents of the target vector should be deleted and replaced with the contents of `other`, which should be left empty afterwards.

**Returns**: A reference to the target `Vector`

**Time Complexity**: *O(`size()`)* &ndash; Linear Time

**Test For This Function:** *vector_move_operator*

**Functions Used By This Test:** `Vector(count)`, `operator=(Vector&& other)`, `~Vector()`, `operator[](pos)`, `size()`, `capacity()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/operator%3D

----

```cpp
iterator begin() noexcept
```

**Description:** Gets an iterator to the first element in the container.

Note: If the container is empty, this should be equivalent to `end()`. **This is NOT something that you should explicitly check for in `begin()`, but rather a sanity check for you to think about.**

**Parameters**: *None*

**Returns**: An `iterator` pointing to the first element in the container.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_begin*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `iterator::operator*()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/begin

----

```cpp
iterator end() noexcept
```

**Description**: Gets an iterator to 1 past the last element in the container. For example, if we have the vector `[1, 2, 3, ?]` (size = 3, capacity = 4), the iterator returned should point to the `?`, NOT `3`.

Note: If the container is empty, this should be equivalent to `begin()`. **This is NOT something that you should explicitly check for in `end()`, but rather a sanity check for you to think about.**

**Parameters**: *None*

**Returns**: An `iterator` pointing to 1 past the last element in the container.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_end*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `end()`, `iterator::operator*()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/end

----

```cpp
[[nodiscard]] bool empty() const noexcept
```

**Description:** Checks whether the container is empty.

**Parameters**: *None*

**Returns**: True if the container is empty, false otherwise.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_empty*

**Functions Used By This Test:** `Vector()`, `Vector(count)`, `operator[](pos)`, `empty()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/empty

----

```cpp
size_t size() const noexcept
```

**Description:** Returns the number of elements in the vector.

**Parameters**: *None*

**Returns**: The size of the vector.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** No specific test, but frequently required by tests.

**Functions Used By This Test:** *N/A*

**Link:** https://en.cppreference.com/w/cpp/container/vector/size

----

```cpp
size_t capacity() const noexcept
```

**Description:** Returns the number of elements that can be held in currently allocated storage.

**Parameters**: *None*

**Returns**: The capacity of the vector (How many elements can fit before needing to resize).

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** No specific test, but frequently required by tests.

**Functions Used By This Test:** *N/A*

**Link:** https://en.cppreference.com/w/cpp/container/vector/capacity

----

```cpp
T& at(size_t pos)
```

**Description:** Access element at index `pos` **with** bounds checking. Throws `std::out_of_range` if `pos` is out of bounds.

**Parameters**:
- `pos` The index to access.

**Returns**: A reference to the element at the desired index. *Note: The difference in const vs non-const return type is not something that you need to account for when writing the `at()` functions, but rather something that will be considered by someone using the `at()` function.*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_at*

**Functions Used By This Test:** `Vector(count)`, `Vector(const Vector& other)`, `at()` *(both)*

**Link:** https://en.cppreference.com/w/cpp/container/vector/at

----

```cpp
const T& at(size_t pos) const
```

**Description:** Access element at index `pos` **with** bounds checking. Throws `std::out_of_range` if `pos` is out of bounds.

**Parameters**:
- `pos` The index to access.

**Returns**: A const reference to the element at the desired index. The returned element cannot be be used to affect the vector. *Note: The difference in const vs non-const return type is not something that you need to account for when writing the `at()` functions, but rather something that will be considered by someone using the `at()` function.*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_at*

**Functions Used By This Test:** `Vector(count)`, `Vector(const Vector& other)`, `at()` *(both)*

**Link:** https://en.cppreference.com/w/cpp/container/vector/at

----

```cpp
T& operator[](size_t pos)
```

**Description:** Access element at index `pos` **without** bounds checking.

**Parameters**:
- `pos` The index to access.

**Returns**: A reference to the element at the desired index. *Note: The difference in const vs non-const return type is not something that you need to account for when writing the access operators, but rather something that will be considered by someone using the access operators.*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_access_operator*

**Functions Used By This Test:** `Vector(count)`, `Vector(const Vector& other)`, `~Vector()`, `operator[](pos)` *(both)*, `size()`, `capacity()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/operator_at

----

```cpp
const T& operator[](size_t pos) const
```

**Description:** Access element at index `pos` **without** bounds checking.

**Parameters**:
- `pos` The index to access.

**Returns**: A const reference to the element at the desired index. The returned element cannot be be used to affect the vector. *Note: The difference in const vs non-const return type is not something that you need to account for when writing the access operators, but rather something that will be considered by someone using the access operators.*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_access_operator*

**Functions Used By This Test:** `Vector(count)`, `Vector(const Vector& other)`, `~Vector()`, `operator[](pos)` *(both)*, `size()`, `capacity()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/operator_at

----

```cpp
T& front()
```

**Description:** Access the first element.

**Parameters**: *None*

**Returns**: A reference to the first element in the vector. *Note: The difference in const vs non-const return type is not something that you need to account for when writing the `front()` functions, but rather something that will be considered by someone using the `front()` function.*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_front_back*

**Functions Used By This Test:** `Vector(count)`, `Vector(const Vector& other)`, `operator[](pos)`, `size()`, `capacity()`, `front()` *(both)*, `back()` *(both)*

**Link:** https://en.cppreference.com/w/cpp/container/vector/front

----

```cpp
const T& front() const
```

**Description:** Access the first element.

**Parameters**: *None*

**Returns**: A const reference to the first element in the vector. *Note: The difference in const vs non-const return type is not something that you need to account for when writing the `front()` functions, but rather something that will be considered by someone using the `front()` function.*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_front_back*

**Functions Used By This Test:** `Vector(count)`, `Vector(const Vector& other)`, `operator[](pos)`, `size()`, `capacity()`, `front()` *(both)*, `back()` *(both)*

**Link:** https://en.cppreference.com/w/cpp/container/vector/front

----

```cpp
T& back()
```

**Description:** Access the last element.

**Parameters**: *None*

**Returns**: A reference to the last element in the vector. *Note: The difference in const vs non-const return type is not something that you need to account for when writing the `back()` functions, but rather something that will be considered by someone using the `back()` function.*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_front_back*

**Functions Used By This Test:** `Vector(count)`, `Vector(const Vector& other)`, `operator[](pos)`, `size()`, `capacity()`, `front()` *(both)*, `back()` *(both)*

**Link:** https://en.cppreference.com/w/cpp/container/vector/back

----

```cpp
const T& back() const
```

**Description:** Access the last element.

**Parameters**: *None*

**Returns**: A const reference to the last element in the vector. *Note: The difference in const vs non-const return type is not something that you need to account for when writing the `back()` functions, but rather something that will be considered by someone using the `back()` function.*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_front_back*

**Functions Used By This Test:** `Vector(count)`, `Vector(const Vector& other)`, `operator[](pos)`, `size()`, `capacity()`, `front()` *(both)*, `back()` *(both)*

**Link:** https://en.cppreference.com/w/cpp/container/vector/back

----

```cpp
void push_back(const T& value)
```

**Description:** Adds `value` to the end of the vector using copy semantics.

**Parameters**:
- `value`: The value to insert as the new last element using copy semantics.

**Returns**: *None* 

**Time Complexity**: *O(1) amortized* &ndash; Constant Time

**Test For This Function:** *vector_push_back*

**Functions Used By This Test:** `Vector()`, `operator[](pos)`, `size()`, `capacity()`, `push_back(const T& value)`

**Link:** https://en.cppreference.com/w/cpp/container/vector/push_back

----

```cpp
void push_back(T&& value)
```

**Description:** Adds `value` to the end of the vector using move semantics.

**Parameters**:
- `value` The value to insert as the new last element using move semantics.

**Returns**: *None*

**Time Complexity**: *O(1) amortized* &ndash; Constant Time

**Test For This Function:** *vector_push_back*

**Functions Used By This Test:** `Vector()`, `operator[](pos)`, `size()`, `capacity()`, `push_back(T&& value)`

**Link:** https://en.cppreference.com/w/cpp/container/vector/push_back

----

```cpp
void pop_back()
```

**Description:** Removes the last element from the vector. Note: The capacity of the vector should never be decreased when popping or erasing elements (for this implementation).

**Parameters**: *None*

**Returns**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_pop_back*

**Functions Used By This Test:** `Vector()`, `size()`, `capacity()`, `push_back()`, `pop_back()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/pop_back

----

```cpp
iterator insert(iterator pos, const T& value)
```

**Description:** Inserts `value` at position `pos`. For example, if `pos` points to index `1` of the vector `[0, 1, 2, 3, ?]` and `value` is `5`, the result of the insert will be the vector `[0, 5, 1, 2, 3]`.

**Parameters**:
- `pos` An iterator pointing to the position the element should be inserted. If there is already an element at this position, this element and all following elements should be shifted over.
- `value` The value to insert using copy semantics.

**Returns**: An iterator pointing to the inserted element.

**Time Complexity**: *O(`end() - pos`)*

**Test For This Function:** *vector_insert*

**Functions Used By This Test:** `Vector(count)`, `size()`, `capacity()`, `operator[](pos)`, `begin()`, `insert(iterator pos, const T& value)`, `iterator::operator+(difference_type offset)`, `iterator::operator-(const iterator& rhs)`

**Link:** https://en.cppreference.com/w/cpp/container/vector/insert

----

```cpp
iterator insert(iterator pos, T&& value)
```

**Description:** Inserts `value` at position `pos`. For example, if `pos` points to index `1` of the vector `[0, 1, 2, 3, ?]` and `value` is `5`, the result of the insert will be the vector `[0, 5, 1, 2, 3]`.

**Parameters**:
- `pos` An iterator pointing to the position the element should be inserted. If there is already an element at this position, this element and all following elements should be shifted over.
- `value` The value to insert using move semantics.

**Returns**: An iterator pointing to the inserted element.

**Time Complexity**: *O(`end() - pos`)*

**Test For This Function:** *vector_insert_move*

**Functions Used By This Test:** `Vector(count)`, `size()`, `capacity()`, `operator[](pos)`, `begin()`, `insert(iterator pos, T&& value)`, `iterator::operator+(difference_type offset)`, `iterator::operator-(const iterator& rhs)`

**Link:** https://en.cppreference.com/w/cpp/container/vector/insert

----

```cpp
iterator insert(iterator pos, size_t count, const T& value)
```

**Description:** Inserts `count` copies of `value` at position `pos`. For example, if `vec` is the vector `[0, 1, 2, 3, 4, ?, ?, ?]` and `pos` points to index `2`, the call `vec.insert(pos, 3, 5)` will result in `vec` being `[0, 1, 5, 5, 5, 2, 3, 4]` (and an iterator to index `2` being returned).

**Parameters**:
- `pos` The position to start inserting elements at.
- `count` The amount of copies to insert.
- `value` The element to be repeatedly inserted.

**Returns**: An iterator pointing to the first element inserted.

**Time Complexity**: *O(`count + end() - pos`)*

**Test For This Function:** *vector_insert_multiple*

**Functions Used By This Test:** `Vector(count)`, `size()`, `capacity()`, `operator[](pos)`, `begin()`, `insert(iterator pos, size_t count, const T& value)`, `iterator::operator+(difference_type offset)`, `iterator::operator-(const iterator& rhs)`

**Link:** https://en.cppreference.com/w/cpp/container/vector/insert

----

```cpp
iterator erase(iterator pos)
```

**Description:** Erases element at position `pos`. The elements of the vector must be contiguous, so you will need to shift over any elements to the right of `pos`. Note: The capacity of the vector should never be decreased when popping or erasing elements (for this implementation).

**Parameters**:
- `pos` An iterator pointing to the element to erase.

**Returns**: An iterator pointing to the element following the one that was erased. For example, if the vector was `[0, 1, 2, 3, 4, 5]` and the element `3` was erased, the resulting vector would be `[0, 1, 2, 4, 5, ?]` and the iterator returned would point to the element `4` (index `3`).

**Time Complexity**: *O(`end() - pos`)*

**Test For This Function:** *vector_erase*

**Functions Used By This Test:** `Vector(count)`, `size()`, `capacity()`, `operator[](pos)`, `begin()`, `erase(pos)`, `iterator::operator+(difference_type offset)`, `iterator::operator-(const iterator& rhs)`

**Link:** https://en.cppreference.com/w/cpp/container/vector/erase

----

```cpp
iterator erase(iterator first, iterator last)
```

**Description:** Erases elements in the range \[`first`, `last`\), including `first` and excluding `last`. Note: The capacity of the vector should never be decreased when popping or erasing elements (for this implementation).

**Parameters**:
- `first` An iterator pointing to the first element to erase.
- `last` An iterator pointing to the element ending the range. Elements should be erased up to this point, but not including this element.

**Returns**: An iterator pointing to the element following the last erased element. For example, if the vector was `[0, 1, 2, 3, 4, 5]` with first pointing to element `0` and last pointing to element `2`, the resulting vector would be `[2, 3, 4, 5, ?, ?]` and the iterator returned would point to the element `2` (index `0`).

**Time Complexity**: *O(`end() - first`)*

**Test For This Function:** *vector_erase_multiple*

**Functions Used By This Test:** `Vector(count)`, `size()`, `capacity()`, `operator[](pos)`, `begin()`, `erase(first, last)`, `iterator::operator+(difference_type offset)`, `iterator::operator-(const iterator& rhs)`

**Link:** https://en.cppreference.com/w/cpp/container/vector/erase

----

```cpp
void clear() noexcept
```

**Description:** Clears the contents of the vector. Note: The capacity of the vector should never be decreased when popping or erasing elements (for this implementation).

**Parameters**: *None*

**Returns**: *None*

**Time Complexity**: *O(n)* &ndash; Linear Time

**Test For This Function:** *vector_clear*

**Functions Used By This Test:** `Vector(count)`, `size()`, `capacity()`, `operator[](pos)`, `clear()`

**Link:** https://en.cppreference.com/w/cpp/container/vector/clear

----

### Implement the Vector's Iterator

You must also implement an inner class `iterator` in `Vector`, which can iterate through the elements of the vector forwards and backwards. 

#### You must implement the following functions for `iterator`:

----

```cpp
iterator()
```

**Description:** Constructs a default iterator. How you define this is up you, but what value do we usually set pointers to as the "default" value? 

**Parameters**: *None*

**Returns**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** No specific test, but frequently required by tests.

**Functions Used By This Test:** *N/A*

----

----

```cpp
explicit iterator(T* ptr)
```

**Description:** Constructs an iterator pointing to the given location.

**Parameters**:
- `ptr` A pointer to the element the iterator should point to.

**Returns**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** No specific test, but frequently required by tests.

**Functions Used By This Test:** *N/A*

----

----

```cpp
[[nodiscard]] reference operator*() const noexcept
```

**Description:** Accesses the element the iterator point to.

**Parameters**: *None*

**Returns**: A reference to the element the iterator points to.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_iterator_io*

**Functions Used By This Test:** `Vector(count, value)`, `operator[](pos)`, `begin()`, `iterator::operator*()`, `iterator::operator->()`

----

```cpp
[[nodiscard]] pointer operator->() const noexcept
```

**Description:** Accesses a member or method of the element the iterator points to.

**Parameters**: *None*

**Returns**: A pointer to the element the iterator points to.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_iterator_io*

**Functions Used By This Test:** `Vector(count, value)`, `operator[](pos)`, `begin()`, `iterator::operator*()`, `iterator::operator->()`

----

```cpp
iterator& operator++() noexcept
```

**Description**: Prefix increment (++i). The iterator should be advanced forward by one element and returned.

**Parameters**: *None*

**Returns**: A reference to the advanced iterator.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_iterator_forward*

**Functions Used By This Test:** `Vector(count)`, `begin()`, `iterator::operator*()`, `iterator::operator++()`, `iterator::operator++(int)`

----

```cpp
iterator operator++(int) noexcept
```

**Description**: Postfix increment (i++). The iterator should be advanced forward by one element, but a copy of before it was advanced should be returned.

**Parameters**: *None*

**Returns**: A copy of the iterator before it was advanced.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_iterator_forward*

**Functions Used By This Test:** `Vector(count)`, `begin()`, `iterator::operator*()`, `iterator::operator++()`, `iterator::operator++(int)`

----

```cpp
iterator& operator--() noexcept
```

**Description**: Prefix decrement (--i). The iterator should be retreated backward by one element and returned.

**Parameters**: *None*

**Returns**: A reference to the retreated iterator.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_iterator_reverse*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `end()`, `iterator::operator*()`, `iterator::operator--()`, `iterator::operator--(int)`

----

```cpp
iterator operator--(int) noexcept
```

**Description**: Postfix decrement (i--). The iterator should be retreated backward by one element, but a copy of before it was retreated should be returned.

**Parameters**: *None*

**Returns**: A copy of the iterator before it was retreated.

**Time Complexity**: *O(1)* &ndash; Constant Time 

**Test For This Function:** *vector_iterator_reverse*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `end()`, `iterator::operator*()`, `iterator::operator--()`, `iterator::operator--(int)`

----

```cpp
iterator& operator+=(difference_type offset) noexcept
```

**Description**: Advances the iterator forward by an offset.

**Parameters**:
- `offset` How far to advance the iterator.

**Returns**: A reference to the iterator after it was advanced `offset` forward.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_iterator_arithmetic*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `end()`, `iterator::operator*()`, `iterator::operator++(int)`, `iterator::operator-(const iterator& rhs)`, `iterator::operator+(offset)`, `iterator::operator+(offset, iterator)` *(this function is at the very bottom of Vector.h and often overlooked)*, `iterator::operator-(difference_type offset)`, `iterator::operator[]()`, `iterator::operator+=()`, `iterator::operator-=()`

----

```cpp
[[nodiscard]] iterator operator+(difference_type offset) const noexcept
```

**Description**: Returns a copy of the iterator advanced forward by an offset.

**Parameters**:
- `offset` How far the copy should be ahead of the iterator.

**Returns**: An iterator `offset` ahead of the current iterator.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_iterator_arithmetic*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `end()`, `iterator::operator*()`, `iterator::operator++(int)`, `iterator::operator-(const iterator& rhs)`, `iterator::operator+(offset)`, `iterator::operator+(offset, iterator)` *(this function is at the very bottom of Vector.h and often overlooked)*, `iterator::operator-(difference_type offset)`, `iterator::operator[]()`, `iterator::operator+=()`, `iterator::operator-=()`

----

```cpp
iterator& operator-=(difference_type offset) noexcept
```

**Description**: Retreats the iterator backwards by an offset.

**Parameters**:
- `offset` How far to retreat the iterator.

**Returns**: A reference to the iterator after it was retreated `offset` backwards.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_iterator_arithmetic*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `end()`, `iterator::operator*()`, `iterator::operator++(int)`, `iterator::operator-(const iterator& rhs)`, `iterator::operator+(offset)`, `iterator::operator+(offset, iterator)` *(this function is at the very bottom of Vector.h and often overlooked)*, `iterator::operator-(difference_type offset)`, `iterator::operator[]()`, `iterator::operator+=()`, `iterator::operator-=()`

----

```cpp
[[nodiscard]] iterator operator-(difference_type offset) const noexcept
```

**Description**: Returns a copy of the iterator retreated backwards by an offset.

**Parameters**:
- `offset` How far the copy should be behind the iterator.

**Returns**: An iterator `offset` behind the current iterator.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_iterator_arithmetic*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `end()`, `iterator::operator*()`, `iterator::operator++(int)`, `iterator::operator-(const iterator& rhs)`, `iterator::operator+(offset)`, `iterator::operator+(offset, iterator)` *(this function is at the very bottom of Vector.h and often overlooked)*, `iterator::operator-(difference_type offset)`, `iterator::operator[]()`, `iterator::operator+=()`, `iterator::operator-=()`

----

```cpp
[[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept
```

**Description**: Finds how far apart two iterators are. Used as `iter1 - iter2`.

**Parameters**:
- `rhs` The iterator to compare with the current iterator

**Returns**: The distance between the the current iterator and `rhs`.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_iterator_arithmetic*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `end()`, `iterator::operator*()`, `iterator::operator++(int)`, `iterator::operator-(const iterator& rhs)`, `iterator::operator+(offset)`, `iterator::operator+(offset, iterator)` *(this function is at the very bottom of Vector.h and often overlooked)*, `iterator::operator-(difference_type offset)`, `iterator::operator[]()`, `iterator::operator+=()`, `iterator::operator-=()`

----

```cpp
[[nodiscard]] reference operator[](difference_type offset) const noexcept
```

**Description**: Gets a reference an element offset from the iterator.

**Parameters**:
- `offset` How far from the iterator the desired element is.

**Returns**: The element `offset` ahead of the iterator.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_iterator_arithmetic*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `end()`, `iterator::operator*()`, `iterator::operator++(int)`, `iterator::operator-(const iterator& rhs)`, `iterator::operator+(offset)`, `iterator::operator+(offset, iterator)` *(this function is at the very bottom of Vector.h and often overlooked)*, `iterator::operator-(difference_type offset)`, `iterator::operator[]()`, `iterator::operator+=()`, `iterator::operator-=()`

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

**Test For This Function:** *vector_iterator_comparison*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `iterator::operator++(int)`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator<()`, `iterator::operator>()`, `iterator::operator<=()`, `iterator::operator>=()`

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

**Test For This Function:** *vector_iterator_comparison*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `iterator::operator++(int)`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator<()`, `iterator::operator>()`, `iterator::operator<=()`, `iterator::operator>=()`

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

**Test For This Function:** *vector_iterator_comparison*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `iterator::operator++(int)`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator<()`, `iterator::operator>()`, `iterator::operator<=()`, `iterator::operator>=()`

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

**Test For This Function:** *vector_iterator_comparison*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `iterator::operator++(int)`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator<()`, `iterator::operator>()`, `iterator::operator<=()`, `iterator::operator>=()`

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

**Test For This Function:** *vector_iterator_comparison*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `iterator::operator++(int)`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator<()`, `iterator::operator>()`, `iterator::operator<=()`, `iterator::operator>=()`

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

**Test For This Function:** *vector_iterator_comparison*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `iterator::operator++(int)`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator<()`, `iterator::operator>()`, `iterator::operator<=()`, `iterator::operator>=()`

----

### One Last Function

There is a small function not a part of the `Vector` class at the bottom of `Vector.h`, which overloads adding an iterator to an offset. This allows for the addition between an iterator and an offset to be commutative

----

```cpp
[[nodiscard]] _Iterator operator+(typename _Iterator::difference_type offset, _Iterator const& iterator) noexcept
```

**Description**: Returns a copy of an iterator advanced forward by an offset.

**Parameters**:
- `offset` How far the copy should be ahead of the iterator.
- `iterator` The iterator to compare to move forward from.

**Returns**: An iterator `offset` ahead of `iterator`.

**Time Complexity**: *O(1)* &ndash; Constant Time

**Test For This Function:** *vector_iterator_arithmetic*

**Functions Used By This Test:** `Vector(count)`, `operator[](pos)`, `begin()`, `end()`, `iterator::operator*()`, `iterator::operator++(int)`, `iterator::operator-(const iterator& rhs)`, `iterator::operator+(offset)`, `iterator::operator+(offset, iterator)` *(this function is at the very bottom of Vector.h and often overlooked)*, `iterator::operator-(difference_type offset)`, `iterator::operator[]()`, `iterator::operator+=()`, `iterator::operator-=()`

----

### Further Reading
Feel free to read about `const_iterator` and `reverse_iterator` in C++. However, you need only implement `iterator` for this assignment.

It may be helpful for you to consult:
- Reference for Iterators: https://en.cppreference.com/w/cpp/iterator/iterator
- Reference for Vector Begin: https://en.cppreference.com/w/cpp/container/vector/begin
- Reference for Vector End: https://en.cppreference.com/w/cpp/container/vector/end
- Reference for List Begin: https://en.cppreference.com/w/cpp/container/list/begin
- Reference for List End: https://en.cppreference.com/w/cpp/container/list/end

----

## Run Tests

Execute the following commands from the `leyk-csce221-assignment-vector` folder to accomplish what you need:

**Build all of the tests** This is not a necessary step, as tests will be rebuilt when using the run commands below.
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
Submit the modified `Vector.h` to Gradescope. In general, submit everything except `main.cpp`.
