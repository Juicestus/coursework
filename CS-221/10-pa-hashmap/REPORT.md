# Unordered Map & Priority Queue Questions

The following questions are some additional questions you can use to see your understanding of the unordered map you constructed as well as other implementations of the code.

In previous semesters, this was used for a report conducted in lab - that is no longer used at this point. This REPORT.md file is not particularly for any grade, but could be of some help on your canvas programming assignment demo(s).

For this set of questions, there are also some priority queue questions included that you can explore if you would like. Again, these questions are not required, but are included for your benefit.

Unordered Map Questions:
========================

Question 1
----------

You have an Unordered Map with `b` buckets. Explain your implementation of the `find()` function and how its runtime changes when the only elements present in your Unordered Map have hash values that are multiples of `b/c`, where `c` is some factor of `b`. Let there be `n` elements in your Unordered Map. 

For example, let's say that our unordered map contains 10 buckets. What will each bucket look like if every element inserted has a hash value that is a multiple of 10? What if each hash value is a multiple of 5? A multiple of 2? Use these examples to formulate a general answer for the runtime of `find()` in terms of `n` and `c`.

How could we change the `_hash` data member to improve the performance of the `find()` function given the same elements as input? Alternatively, how could we change `_bucket_count` to see a similar improvement? _Hint: Think about how `_bucket()` is implemented and how you initialized `_bucket_count` in your "default" constructor._

Question 2
----------

Where are the `_size`, `_buckets[]`, `_head`, and `HashNodes` of our unordered map implementation stored (stack or heap)? Explain the Copy and Move Operators and how each of these instance fields are copied/moved in these operators. 

Question 3
----------

In your implementation, your iterator classes had these instance fields:
```C++
class basic_iterator {
    ...
    UnorderedMap* _map;
    HashNode* _node;
    ...
}
class local_iterator {
    ...
    HashNode* _node;
    ...
}
```
Why do these two different iterators require different instance fields? Make sure to discuss the `operator++` in your answer.

Question 4
----------

In our implementation, we stored an individual list in each bucket. But we can utilize other data structures in each bucket. What would be the runtime of the `find()` function given there is a linked list at every bucket (our implementation)? Let the number of elements in a the unordered map be `n` and the number buckets be `b`. Additionally, assume that our hash function evenly distributes the `n` elements among the `b` buckets.

What is the runtime of the `find()` function given there is a binary search tree at every bucket (assuming the binary search tree is balanced)?

What is the runtime of the `find()` function given there is another unordered map at every bucket of the overall unordered map. Assume that the bucket count of the second unordered map is large enough that every element is in its own bucket. Is this implementation faster than a single, larger unordered map?

Priority Queue Questions:
=========================

Question 5
----------
Explain the Process of `Upheap` and `Downheap` with respect to the `push()` and `pop()` functions. How do these functions help preserve the structure/properties of the maximum binary heap? 

If you have 1000 elements (numbered 0...999) that you want to insert into a max heap, what permutation of these elements will insert into the heap in the shortest amount of time? What permutations will insert in the most amount of time? Explain your reasoning. 

Question 6
----------
In your priority queue implementation, you used a maximum binary heap as your internal data structure. Why is this internal data structure preferable to a sorted linked list (sorted in reverse, with max element at the head)? In your answers, discuss how the time complexities of `push()`, `pop()`, and `top()` would change, if at all. Let the number of elements in the heap be `n`.

Question 7
----------
Programming assignment 2 was on sorting vectors. How can we sort a vector from lowest to highest using a minimum priority queue? Describe the implementation and the runtime. Let the number of elements in the vector be `n`. Compare its runtime and the number of comparisons to another comparison based algorithm. 

Question 8
----------
Discuss the algorithm you used for `push()` and `pop()` operations. Describe an alternate implementation (For example, if you implemented it recursively, explain how you it could be written iteratively. If you did it iterativey, explain how you could have written in recursively). Analyze any differences in the time and space complexity that may exist between the two implementations (iterative and recursive).