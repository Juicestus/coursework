List Questions
================
The following questions are some additional questions you can use to see your understanding of the list as well as other implementations of the code.

In previous semesters, this was used for a report conducted in lab - that is no longer used at this point. This REPORT.md file is not particularly for any grade, just if you would like to explore some applications or possible questions using the structure implemented.

Question 1
----------

Consider the following code snippet:

```c++
void f1() {
    List<int> ll;
    ll.push_front(20);
    ll.push_back(30);
}
```

Four nodes are created by the `List` class. (1) Briefly describe the purpose of each node and (2) identify what region of memory where it is stored (stack, heap, text, uninitialized data, or initialized data).

Question 2
----------

Consider the following code snippet, which implements the `List` destructor:

```c++
template <class T>
List<T>::~List() { 
    Node * cursor = head.next;
    while(cursor != &tail) {
        delete cursor;
        cursor = cursor->next;
    }
}
```

This code contains an error. What is the error? How would you fix it?

Question 3
----------

A student is attempting to delete a node from the doubly linked list and writes the following code:

```c++
node->next->prev = node->next;
node->prev->next = node->prev;
delete node;
```
Is this scheme correct? If so, justify why it works. If not, explain the issue with their methodology.

Question 4
----------

A student implements the following move constructor:

```c++
template <class T>
List<T>::List(List && ll) : head{}, tail{}, _size{0} {
    _size = ll._size;
    if(!ll.empty()) {
        head.next = ll.head.next;
        tail.prev = ll.tail.prev;

        ll.head.next = &ll.tail;
        ll.tail.prev = &ll.head;
    } else {
        head.next = &tail;
        tail.prev = &head;
    }
    ll._size = 0;
}
```

The code contains an error. What is the source of this error? Provide a sequence of iterator operations which demonstrate the incorrect behavior.

Question 5
----------

The `List` was implemented with head and tail sentinel nodes that bookend the list. We could have implemented it in a similar (and possibly simpler) fashion using `head` and `tail` pointers as follows:

```c++
template <class T>
class List {
    // Imagine that Node class is defined here
    Node *head, *tail;
    // ...
};
```

What benefit do the `head` and `tail` nodes provide over the above implementation?

Question 6
----------

When dealing with the `Card`s, you shuffled the `deck` using the `shuffle` function. What is the asymptotic running time of the `shuffle` function? You may assume that `rand221` runs in constant time. Justify the running time you suggest. After the deck is shuffled, assuming that it contains *n* cards, what is the time complexity to find the card that was at the **front** of the deck before it was shuffled? What is the time complexity to find the card that was at the **back** of the deck before it was shuffled? Justify these time complexities.

Question 7
----------

What is the runtime of the `pop_back` and `pop_front` functions? If we implemented a singly linked list with a single head pointer, would either of these runtimes change? If not, describe why. If so, describe which runtimes will change and what the new runtime would be.

Question 8
----------

Name at least three functions (or constructors) that call (directly or indirectly) the `insert` function variants. If you do not have three such functions in your code, name three functions that you *could* have implemented in such a manner. Describe an alternate implementation where if you used `insert` (or a derivative of `insert`, e.g. `push_back`), you do not use it and vice-versa.

Name at least two functions that call (directly or indirectly) the `erase` function (or its derivatives, i.e. `pop_back`). If you do not have two such functions in your code, name two functions that you could have implemented in such a manner. Describe an alternate implementation where if you used `erase` (or a derivative of `erase`, e.g. `pop_back`), you do not use it and vice-versa.

The goal of this question is to get you thinking about alternate implementations for the functions in your program.

Question 9
----------

In the REPORT.md for `assignment-vector` you were provided an example of iterator invalidation. That is when using `Vector`, an `Vector` iterator would point to invalid memory if an operation was performed to reallocate the underlying array. Now consider your implementation of `List`. Which of the following `List` methods *can* result in iterator invalidation? For each method that can result in iterator invalidation, describe the *conditions under which this occurs*.

- `push_back`
- `erase`
- `insert`
- `clear`
- `List& operator=( const List& other );`
- `List& operator=( List&& other ) noexcept;`
