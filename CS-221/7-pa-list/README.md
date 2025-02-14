# Linked Lists
In this assignment, you will program a Doubly Linked List class called `List` which parodies the [`std::list`](https://en.cppreference.com/w/cpp/container/list) class inherent to the Standard Template Library (STL) in C++.

Topics:

- Allocation (`new`) and Deallocation (`delete`)
- Stack and Heap Memory
- Bidirectional Iterators
  - Simplification of Random Access Iterators

The difficulty of the assignment is very close to that of the `Vector` assignment. You do not need to write as many functions, but there is much more nuanced work with the inner class `List::Node`.

A linked list consists of a sequence of data members in memory. Rather than maintaining adjacent elements in one contiguous memory block, a link list is a sequence of memory blocks each containing a data member and the memory location of the next memory block in the sequence. These memory blocks are often referred to as “nodes.” In C/C++, nodes are structs or classes containing a pointer (memory address) of the next node as well as a data member. Doubly linked lists also contain a pointer to the previous node in the list to permit bidirectional iteration.

## Suggested Implementation using Sentinel Nodes

There are several strategies for implementing linked lists. While any strategy conforming to the `std::list` API will be accepted, we recommend implementing the doubly-linked list using "sentinel nodes."  (The function descriptions under "Doubly Linked List Implementation" also assume the use of sentinel nodes.) In the starter code, the `List::Node` struct represents a single node in the list. Each node contains three members: `next` is a pointer to the next node in the sequence, `prev` is a pointer to the previous node in the sequence, and `data` is the data member stored in the current node. The data nodes will contain all three fields. The only exception to this is the sentinel nodes. Sentinel nodes are extra “dummy” nodes which are added before the first data node and after the last data node. While these denote the start and end of the collection, they do not themselves contain any data. (The data member can be left uninitialized.) A good analogy of this is bookends, in which the bookends are on both ends of a book collection, but are not books in the collection. When the list is first initialized, the `head`’s `next` pointer should point to the `tail` and the `tail`’s previous pointer should point to the `head`. The `head` and `tail` are allocated along with the List collection since they are always present. As items are added, they will be added between the head and tail to maintain a fully linked list.

## Table of Contents
[Getting Started](#getting-started)

[Assignment](#assignment)

- [Doubly Linked List Implementation](#doubly-linked-list-implementation)

- [Implement the List's Iterator](#implement-the-lists-iterator)

- [Implementing a Queue (Application of Doubly Linked List)](#implementing-a-queue-application-of-doubly-linked-list)

[Incremental Testing](#incremental-testing)

[Run Tests](#run-tests)

[Turn In](#turn-in)

## Getting started
Download this code by running the following command in the directory of your choice:
```sh
git clone git@github.com:tamu-edu-students/leyk-csce221-assignment-list.git && cd leyk-csce221-assignment-list
```
Open the code in your editor of choice. For instance, if you use VS Code:
```sh
code .
```
*Note:* On OSX you may need to enable the `code` command in VS Code with <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and typing "shell command." You can select the option to install the command, and then the above command will work.
## Assignment
### Doubly Linked List Implementation
Implement the following [constructors](https://en.cppreference.com/w/cpp/container/list/list), [destructors](https://en.cppreference.com/w/cpp/container/list/%7Elist), and assignment operators [`operator=`](https://en.cppreference.com/w/cpp/container/list/operator%3D) which include the Rule of 5:

----
`List()` - **Default constructor**

**Description:** Constructs an empty linked list. In an empty linked list, `head` and `tail` should point to each other.

**Complexity: O(1)**

**Test For This Function:** *constructor_default*

**Functions Used By This Test:** `List()`, `size()`, `cbegin()`, `cend()`, `iterator::operator==()`

**Link:** https://en.cppreference.com/w/cpp/container/list/list

----
`List( size_type count, const T& value )`

**Description:** Constructs a linked list with `count` copies of elements with value `value`.

**Complexity: O(`count`)**

**Test For This Function:** *constructor_insert_copies*

**Functions Used By This Test:** `List(count, value)`, `~List()`, `size()`, `cbegin()`, `cend()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator++(int)`, `iterator::operator--()`

**Link:** https://en.cppreference.com/w/cpp/container/list/list

----
`explicit List( size_type count )`

**Description:** Constructs a linked list with `count` default-inserted instances of `T` (`T()`). No copies are made.

**Complexity: O(`count`)**

**Test For This Function:** *constructor_default_inserted*

**Functions Used By This Test:** `List(count)`, `~List()`, `size()`, `cbegin()`, `cend()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator++(int)`, `iterator::operator--()`

**Link:** https://en.cppreference.com/w/cpp/container/list/list

----
`List( const List& other )` - **Copy constructor** 

**Description:** Constructs a linked list with a **copy** of the contents of `other`.

**Complexity: O(`other.size()`)**

**Test For This Function:** *constructor_copy*

**Functions Used By This Test:** `List(count)`, `List(const List&)`, `~List()`, `size()`, `cbegin()`, `cend()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator++(int)`, `iterator::operator--()`

**Link:** https://en.cppreference.com/w/cpp/container/list/list

----
`List( List&& other )` - **Move constructor**

**Description:** Constructs a linked list with the contents of `other` using move semantics (i.e. the data in `other` is moved from `other` into this container). No new nodes should be made. `other` should be left in an empty state after. To call the move constructor, you can use `List<type> list1 = std::move(list2);`.

**Complexity: O(1)**

**Test For This Function:** *constructor_move*

**Functions Used By This Test:** `List(count)`, `List(List&&)`, `size()`, `cbegin()`, `cend()`, `begin()`, `end()`, `iterator::operator!=()`, `iterator::operator==()`, `iterator::operator*()`, `iterator::operator++(int)`, `iterator::operator++()`, `iterator::operator--()`

**Link:** https://en.cppreference.com/w/cpp/container/list/list

----
`~List()` - **Destructor**

**Description:** The destructors of the elements are called and the used storage is deallocated. Note, that if the elements are pointers, the pointed-to objects are not destroyed.

**Complexity: O(`size()`)**

**Test For This Function:** No Direct Test, But Frequently Utilized

**Link:** https://en.cppreference.com/w/cpp/container/list/%7Elist

----
`List& operator=( const List& other )` - **Copy assignment operator** 

**Description:** Replaces the linked list with a copy of the contents of `other`.

**Complexity: O(max(`size()`, `other.size()`))**

**Test For This Function:** *operator_copy* and *operator_copy_consistency*

**Functions Used By This Test:** `List(count)`, `operator=(const List&)`, `~List()`, `size()`, `begin()`, `end()`, `cbegin()`, `cend()`, `iterator::operator!=()`, `iterator::operator==()`, `iterator::operator*()`, `iterator::operator++(int)`, `iterator::operator--()`, `insert(pos, const T&)`, `erase(pos)`

**Link:** https://en.cppreference.com/w/cpp/container/list/operator%3D

----
`List& operator=( List&& other ) noexcept` - **Move assignment operator** 

**Description:** Replaces the linked list with the contents of `other` using move semantics (i.e. the data in `other` is moved from `other` into this container). No new nodes should be made. `other` should be left in an empty state after. To call the move assignment operator, you can use `list1 = std::move(list2);`.

**Complexity: O(`size()`)**

**Test For This Function:** *operator_move* and *operator_move_consistency*

**Functions Used By This Test:** `List(count)`, `operator=(List&&)`, `~List()`, `size()`, `begin()`, `end()`, `cbegin()`, `cend()`, `iterator::operator!=()`, `iterator::operator==()`, `iterator::operator*()`, `iterator::operator++(int)`, `iterator::operator--()`, `insert(pos, const T&)`, `erase(pos)`

**Link:** https://en.cppreference.com/w/cpp/container/list/operator%3D

----

#### Implement the following functions for `List`:

----
`reference front()` and `const_reference front() const`

**Description:** Accesses the first element of the linked list.

**Complexity: O(1)**

**Test For This Function:** *terminals*

**Functions Used By This Test:** `List()`, `List(count)`, `~List()`, `begin()`, `end()`, `cbegin()`, `cend()`, `iterator::operator==()`, `iterator::operator*()`, `iterator::operator--()`, `front()` (both), `back()` (both)

**Link:** https://en.cppreference.com/w/cpp/container/list/front

----
`reference back()` and `const_reference back() const`

**Description:** Accesses the last element of the linked list.

**Complexity: O(1)**

**Test For This Function:** *terminals*

**Functions Used By This Test:** `List()`, `List(count)`, `~List()`, `begin()`, `end()`, `cbegin()`, `cend()`, `iterator::operator==()`, `iterator::operator*()`, `iterator::operator--()`, `front()` (both), `back()` (both)

**Link:** https://en.cppreference.com/w/cpp/container/list/back

----
`iterator begin()` and `const_iterator begin() const noexcept`

**Description:** Returns an iterator (or const iterator) to the first element of the linked list.

Note: If the container is empty, this should be equivalent to `end()`. **This is NOT something that you should explicitly check for in `begin()`, but rather a sanity check for you to think about.**

**Complexity: O(1)**

**Test For This Function:** *terminals*

**Functions Used By This Test:** `List()`, `List(count)`, `~List()`, `begin()`, `end()`, `cbegin()`, `cend()`, `iterator::operator==()`, `iterator::operator*()`, `iterator::operator--()`, `front()` (both), `back()` (both)

**Link:** https://en.cppreference.com/w/cpp/container/list/begin

----
`iterator end()` and `const_iterator end() const noexcept`

**Description:** Returns an iterator (or const iterator) to the end of the list (`tail`).

**Complexity: O(1)**

**Test For This Function:** *terminals*

**Functions Used By This Test:** `List()`, `List(count)`, `~List()`, `begin()`, `end()`, `cbegin()`, `cend()`, `iterator::operator==()`, `iterator::operator*()`, `iterator::operator--()`, `front()` (both), `back()` (both)

**Link:** https://en.cppreference.com/w/cpp/container/list/end

----
`const_iterator cbegin() const noexcept`

**Description:** Returns a const iterator to the first element of the linked list.

Note: If the container is empty, this should be equivalent to `cend()`. **This is NOT something that you should explicitly check for in `cbegin()`, but rather a sanity check for you to think about.**

**Complexity: O(1)**

**Test For This Function:** *terminals*

**Functions Used By This Test:** `List()`, `List(count)`, `~List()`, `begin()`, `end()`, `cbegin()`, `cend()`, `iterator::operator==()`, `iterator::operator*()`, `iterator::operator--()`, `front()` (both), `back()` (both)

**Link:** https://en.cppreference.com/w/cpp/container/list/begin

----
`const_iterator cend() const noexcept`

**Description:** Returns a const iterator to the end of the list (`tail`).

**Complexity: O(1)**

**Test For This Function:** *terminals*

**Functions Used By This Test:** `List()`, `List(count)`, `~List()`, `begin()`, `end()`, `cbegin()`, `cend()`, `iterator::operator==()`, `iterator::operator*()`, `iterator::operator--()`, `front()` (both), `back()` (both)

**Link:** https://en.cppreference.com/w/cpp/container/list/end

----
`bool empty() const noexcept`

**Description:** Checks whether the container is empty.

**Complexity: O(1)**

**Test For This Function:** *clear_and_empty*

**Functions Used By This Test:** `List(count, value)`, `begin()`, `end()`, `size()`, `empty()`, `iterator::operator==()`, `iterator::operator*()`, `iterator::operator--()`, `iterator::operator++(int)`, `clear()`, `push_back copy`, `push_front copy`

**Link:** https://en.cppreference.com/w/cpp/container/list/empty

----
`size_t size() const noexcept`

**Description:** Returns the number of elements.

**Complexity: O(1)**

**Test For This Function:** No Direct Test, But Frequently Utilized

**Link:** https://en.cppreference.com/w/cpp/container/list/size

----
`void clear() noexcept`

**Description:** Clears the contents of the linked list. The list should be left in an empty state afterwards.

**Complexity: O(`size()`)**

**Test For This Function:** *clear_and_empty*

**Functions Used By This Test:** `List(count, value)`, `begin()`, `end()`, `size()`, `empty()`, `iterator::operator==()`, `iterator::operator*()`, `iterator::operator--()`, `iterator::operator++(int)`, `clear()`, `push_back copy`, `push_front copy`

**Link:** https://en.cppreference.com/w/cpp/container/list/clear

----
`iterator insert(const_iterator pos, const T& value)` and `iterator insert(const_iterator pos, T&& value)`

**Description:** Inserts `value` before `pos` .

**Complexity: O(1)**

**Test For This Function:** *insert*

**Functions Used By This Test:** `List()`, `cbegin()`, `cend()`, `size()`, `iterator::operator==()`, `iterator::operator*()`, `iterator::operator--()`, `iterator::operator--(int)`, `iterator::operator++()`, `iterator::operator++(int)`, `insert copy`, `insert move`

**Link:** https://en.cppreference.com/w/cpp/container/list/insert

----
`iterator erase(const_iterator pos)`

**Description:** Removes the element at `pos` and returns an iterator that points to the element following the erased item.

**Complexity: O(1)**

**Test For This Function:** *erase*

**Functions Used By This Test:** `List(count)`, `begin()`, `end()`, `size()`, `iterator::operator==()`, `iterator::operator*()`, `iterator::operator--()`, `iterator::operator--(int)`, `iterator::operator++()`, `iterator::operator++(int)`, `erase(pos)`

**Link:** https://en.cppreference.com/w/cpp/container/list/erase

----
`void push_back(const T& value)` and `void push_back(T&& value)`

**Description:** Adds `value` to the end of the list.

**Complexity: O(1)**

**Test For This Function:** *push_back*

**Functions Used By This Test:** `List()`, `~List()`, `cbegin()`, `cend()`, `size()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator--()`, `iterator::operator++(int)`, `push_back copy`, `push_back move`

**Link:** https://en.cppreference.com/w/cpp/container/list/push_back

----
`void pop_back()`

**Description:** Removes the last element of the list.

**Complexity: O(1)**

**Test For This Function:** *pop_back*

**Functions Used By This Test:** `List(count)`, `begin()`, `end()`, `size()`, `iterator::operator*()`, `iterator::operator--()`, `iterator::operator++(int)`, `pop_back()`

**Link:** https://en.cppreference.com/w/cpp/container/list/pop_back

----
`void push_front(const T& value)` and `void push_front(T&& value)`

**Description:** Inserts `value` at the beginning of the list.

**Complexity: O(1)**

**Test For This Function:** *push_front*

**Functions Used By This Test:** `List()`, `~List()`, `cbegin()`, `cend()`, `size()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator--()`, `iterator::operator++(int)`, `push_front copy`, `push_front move`

**Link:** https://en.cppreference.com/w/cpp/container/list/push_front

----
`void pop_front()`

**Description:** Removes the first element of the list.

**Complexity: O(1)**

**Test For This Function:** *pop_front*

**Functions Used By This Test:** `List(count)`, `begin()`, `end()`, `size()`, `iterator::operator*()`, `iterator::operator--()`, `iterator::operator++(int)`, `pop_front()`

**Link:** https://en.cppreference.com/w/cpp/container/list/pop_front

----

### Implement the List's Iterator

Implement `List::basic_iterator` which will create `iterator` and `const_iterator` for you. Write the following functions, which are **different from those of the Random Access Iterator from `Vector`.** If you reuse that code, it will not work at all because the list iterator is a **Bidirectional Iterator**.

#### Implement the following functions for `basic_iterator`:

----
`basic_iterator() noexcept` - Default Constructor

**Description:** Create a default `basic_iterator`.

**Complexity: O(1)**

**Test For This Function:** *iterator*

**Functions Used By This Test:** `List(count)`, `begin()`, `cbegin()`, `cend()`, `iterator::basic_iterator()`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator->()`, `iterator::operator--()`, `iterator::operator--(int)`, `iterator::operator++()`, `iterator::operator++(int)`

----
`reference operator*() const`

**Description:** Dereference the pointer, returning a reference to the value in the managed node. **Do not return a reference to the `Node`, but instead return a reference to its managed data.**

**Complexity: O(1)**

**Test For This Function:** *iterator*

**Functions Used By This Test:** `List(count)`, `begin()`, `cbegin()`, `cend()`, `iterator::basic_iterator()`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator->()`, `iterator::operator--()`, `iterator::operator--(int)`, `iterator::operator++()`, `iterator::operator++(int)`

----
`pointer operator->() const`

**Description:** Return a pointer to the data managed by `Node`. **Do not return a pointer to the `Node`, but instead return a pointer to its managed data.**

**Complexity: O(1)**

**Test For This Function:** *iterator*

**Functions Used By This Test:** `List(count)`, `begin()`, `cbegin()`, `cend()`, `iterator::basic_iterator()`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator->()`, `iterator::operator--()`, `iterator::operator--(int)`, `iterator::operator++()`, `iterator::operator++(int)`

----
`basic_iterator& operator++()`

**Description:** **Prefix Increment.** Advance the iterator so that it points to the next node in the list. Return a reference to this iterator.

**Complexity: O(1)** 

**Test For This Function:** *iterator*

**Functions Used By This Test:** `List(count)`, `begin()`, `cbegin()`, `cend()`, `iterator::basic_iterator()`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator->()`, `iterator::operator--()`, `iterator::operator--(int)`, `iterator::operator++()`, `iterator::operator++(int)`

----
`basic_iterator operator++(int)`

**Decription:** **Postfix Increment.** Advance the iterator so that it points to the next node in the list. Return a copy of the iterator from before it was advanced.

**Complexity: O(1)**

**Test For This Function:** *iterator*

**Functions Used By This Test:** `List(count)`, `begin()`, `cbegin()`, `cend()`, `iterator::basic_iterator()`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator->()`, `iterator::operator--()`, `iterator::operator--(int)`, `iterator::operator++()`, `iterator::operator++(int)`

----
`basic_iterator& operator--()`

**Description:** **Prefix Decrement.** Retreat the iterator so that it points to the previous node in the list. Return a reference to this iterator.

**Complexity: O(1)**

**Test For This Function:** *iterator*

**Functions Used By This Test:** `List(count)`, `begin()`, `cbegin()`, `cend()`, `iterator::basic_iterator()`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator->()`, `iterator::operator--()`, `iterator::operator--(int)`, `iterator::operator++()`, `iterator::operator++(int)`

----
`basic_iterator operator--(int)`

**Description:** **Postfix Decrement.** Retreat the iterator so that it points to the previous node in the list. Return a copy of the iterator from before it was retreated.

**Complexity: O(1)**

**Test For This Function:** *iterator*

**Functions Used By This Test:** `List(count)`, `begin()`, `cbegin()`, `cend()`, `iterator::basic_iterator()`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator->()`, `iterator::operator--()`, `iterator::operator--(int)`, `iterator::operator++()`, `iterator::operator++(int)`

----
`bool operator==(const basic_iterator& other) const noexcept`

**Description:** Compare two iterators and determine if they are equivalent.

**Complexity: O(1)**

**Test For This Function:** *iterator*

**Functions Used By This Test:** `List(count)`, `begin()`, `cbegin()`, `cend()`, `iterator::basic_iterator()`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator->()`, `iterator::operator--()`, `iterator::operator--(int)`, `iterator::operator++()`, `iterator::operator++(int)`

----
`bool operator!=(const basic_iterator& other) const noexcept`

**Description:** Compare two iterators and determine if they are not equivalent.

**Complexity: O(1)**

**Test For This Function:** *iterator*

**Functions Used By This Test:** `List(count)`, `begin()`, `cbegin()`, `cend()`, `iterator::basic_iterator()`, `iterator::operator==()`, `iterator::operator!=()`, `iterator::operator*()`, `iterator::operator->()`, `iterator::operator--()`, `iterator::operator--(int)`, `iterator::operator++()`, `iterator::operator++(int)`

----

A possible implementation (followed by GCC) is to make:
```cpp
auto begin_it = begin(), end_it = end();
--begin_it; ++end_it;
begin_it == end(); // this is true
end_it == begin(); // this is true
```
Thus, the end loops back to the beginning and the beginning back to the end. **You do not have to do this, but it is an approach that you can follow to prevent Segfaults from going off the end of the list.** This form of `List` is very similar to a Circular Linked List.

#### Further Reading
- [Geeks For Geeks Doubly Linked List](https://www.geeksforgeeks.org/doubly-linked-list/)
- [Tutorials Point Double Linked List](https://www.tutorialspoint.com/data_structures_algorithms/doubly_linked_list_algorithm.htm)
- [Wikipedia Doubly Linked List](https://en.wikipedia.org/wiki/Doubly_linked_list)

### Implementing a Queue (Application of Doubly Linked List)

One of the big applications for a linked list is designing other ADTs such as a queue or a stack. For this assignment, you are tasked with implementing a queue using the List class you defined. Keep in mind, that queues are FIFO (First in first out) structures, so you should design it accordingly. The implementation is mostly up to you, as long as the queue is functional.

We provide for you a `class Queue` in [`Queue.h`](./src/Queue.h) and ask that you implement the following functions for the queue:

----
`reference front()`

**Description:** Returns a reference to the current value at the **front** of the queue. This should be the oldest value in the queue. May use the underlying function of the container `c`.

**Complexity: O(1)**

**Test For This Function:** *queue_front_push_and_pop*

**Functions Used By This Test:** `List()`, `Queue::push copy`, `Queue::pop()`, `Queue::front()`, `Queue::size()`

----
`const_reference front()`

**Description:** Returns a const reference to the current value at the **front** of the queue. This should be the oldest value in the queue. May use the underlying function of the container `c`.

**Complexity: O(1)**

**Test For This Function:** *queue_front_push_and_pop*

**Functions Used By This Test:** `List()`, `Queue::push copy`, `Queue::pop()`, `Queue::front()`, `Queue::size()`

----
`reference back()`

**Description:** Returns a reference to the current value at the **back** of the queue. This should be the most recently added value in the queue. May use the underlying function of the container `c`.

**Complexity: O(1)**

**Test For This Function:** *queue_back_and_push*

**Functions Used By This Test:** `List()`, `Queue::push copy`, `Queue::back()`, `Queue::size()`

----
`const_reference back()`

**Description:** Returns a const reference to the current value at the **back** of the queue. This should be the most recently added value in the queue. May use the underlying function of the container `c`.

**Complexity: O(1)**

**Test For This Function:** *queue_back_and_push*

**Functions Used By This Test:** `List()`, `Queue::push copy`, `Queue::back()`, `Queue::size()`

----
`bool empty()`

**Description:** Returns true if the queue is empty, otherwise returns false. Can use the underlying function of the container `c`.

**Complexity: O(1)**

**Test For This Function:** *queue_push_pop_and_empty*

**Functions Used By This Test:** `List()`, `Queue::push copy`, `Queue::pop()`, `Queue::size()`, `Queue::empty()`

----
`size_type size()`

**Description:** Returns the number of elements currently in the queue. Can use the underlying function of the container `c`.

**Complexity: O(1)**

**Test For This Function:** No Direct Test, But Frequently Utilized

----
`void push(const value_type& value)`

**Description:** Adds a copy of `value` to the end of the queue. This should be the last of the current elements to be removed.

**Complexity: O(1)**

**Test For This Function:** *queue_back_and_push*, *queue_push_pop_and_empty*, and *queue_front_push_and_pop*

**Functions Used By These Tests:** See Specifications Above For Each Test

----
`void push(value_type&& value)`

**Description:** Adds `value` to the end of the queue using move semantics. This should be the last of the current elements to be removed.

**Complexity: O(1)**

**Test For This Function:** *queue_push_move*

**Functions Used By This Test:** `List()`, `Queue::push move`, `Queue::back()`, `Queue::size()`

----
`void pop()`

**Description:** Removes the first element of the queue. This should be the current oldest element in the queue.

**Complexity: O(1)**

**Test For This Function:** *queue_push_pop_and_empty* and *queue_front_push_and_pop*

**Functions Used By These Tests:** See Specifications Above For Each Test

----
`inline bool operator==(const Queue<T, Container>& lhs, const Queue<T, Container>& rhs)`

**Description:** Determines if 2 queues are equivalent. If the 2 queues have different sizes, they are not equal. Must compare the individual elements of the underlying container (i.e. all elements in each queue must be equal in order for 2 queues to be equal).

Hint: Because this operator is marked as a `friend` of the `Queue` class, the underlying container (i.e. the underlying `List`) of `lhs` and `rhs` can be accessed by `lhs.c` and `rhs.c`, respectively.

**Complexity: O(n)**

**Test For This Function:** *queue_equality_operator*

**Functions Used By This Test:** `List()`, `Queue::push copy`, `Queue::size()`, `operator==(const Queue&, const Queue&)`

----

## Incremental Testing
 
Unlike `Vector`, elements are not organized contiguously in `List`. This means we can't directly access elements. Instead, elements
must be accessed through the `iterator`. This impacts testing since the correctness of the `iterator` can't be tested independently of
the list itself. There are many possible ways to approach the assignment. Although, there are also many implicit dependencies in the test cases. To minimize test dependencies, we recommend you follow the ordering below. These methods listed in the below steps are explicitly required by the test cases. You may wish to write additional helper methods or implement methods in an alternative order to avoid repetition.
 
### 1. Implement the following methods first:
```cpp
explicit List( size_type count );
~List();
size_t size();
cbegin();
cend();
basic_iterator operator++(int);
basic_iterator& operator--();
reference operator*() const;
bool operator!=(const basic_iterator& other) const noexcept;
```
 
This is the minimal set of methods we need for rigorous testing. With a correct implementation of these methods, you will be able to pass the `constructor_default_inserted` test. 
 
### 2. Flesh out the `iterator`:
 
```cpp
pointer operator->() const;
bool operator==(const basic_iterator& other) const noexcept;
basic_iterator operator--(int);
basic_iterator& operator++();
begin();
end();
```
 
After implementing these methods, you will be able to pass the `iterator` test.
 
### 3. Finish the `List`:
 
At this point, the necessary foundation should exist for you to approach the remaining tests. The functions are listed with their corresponding test cases above. Most will require you to implement a single method on top of this foundation. Notable exceptions include:
 
- The `push` family of methods requires that you implement the default constructor
- `clear` and `empty` are aggregated into a single test
- `front` and `back` are tested in `terminals`
- `operator_copy_consistency` requires `insert`, `erase`, and the copy operator. This serves as a stress test to assert the copy operator leaves the objects in a valid state. The copy operator is also tested independently of `insert` and `erase` in `operator_copy`.
- `operator_move_consistency` requires `insert`, `erase`, and the move operator. Same rationale.
 
### 4. Finish the `Queue.h` functions
 
`List` is utilized in `Queue.h` and assumed to be in working condition. You should utilize the functions implemented in `List.h` to implement the queue ADT. It is recommended to do the equality operator last.

## Run Tests
**First consult this guide: [`tests/README.md`](./tests/README.md)**

To run the tests, you need to rename [`main.cpp`](./src/main.cpp) or you need to rename the `int main` function within that file.

Execute the following commands from the `assignment-list` folder to accomplish what you need:

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

The first command builds the tests, the next enters the folder where the tests were built. The third invokes `gdb` (**use `lldb` if on Mac OSX**) which is used to debug the program by examining Segmentation Faults and running code line-by-line. Finally, the last command takes you back to the top-level directory.

## Turn In
Submit the following files **and no other files** to Gradescope:
- [ ] [`Queue.h`](src/Queue.h)
- [ ] [`List.h`](src/List.h)
