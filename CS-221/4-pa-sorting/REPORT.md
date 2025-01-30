# Sorting Vectors - Oral Report

**NOTE: THE ORAL REPORT IS NO LONGER PART OF THE COURSE. THIS REMNANT IS ONLY HERE FOR EXTRA/OPTIONAL PRACTICE**

For the sorting vectors report, you will be asked three questions to test your conceptual understanding of the assignment. Some questions will expand on the concepts you learned. You will answer orally. We are expecting responses to be precise and concise. 1-3 sentences about each are sufficient. We may ask clarifying questions. Be prepared. (See the list of questions below.) Since we have many reports to complete in a single lab period, the report will be limited to two minutes.

The oral reports will be scored as "exemplary" (5 points), "mostly sufficient," "incomplete," or "insufficient" (0 points). The point value for "mostly sufficient" and "incomplete" will depend on the difficulty of the question. The points will be awarded in the programming assignment category.

Questions seven and five require you to present your code. Finally, question eight require you to prepare results from running the `main.cpp`.

## Question 1

What is the time complexity of swap when using type `std::string`? Now assume `std::move` was **not** used to implement swap. What is the time complexity on `std::string`? Explain your reasoning.

## Question 2

Consider the statement: 
```C++
using less_for_iter = std::less<typename std::iterator_traits<RandomIter>::value_type>
```
What is the purpose of `std::less` in the STL? Provided a `std::vector<char>` iterator, to which type does `typename std::iterator_traits<RandomIter>::value_type` resolve? What default behavior does `sort::less_for_iter` define for the comparator `comp`?

## Question 3

What is a comparator? What are the parameters for a comparator and the return type? How did you use the comparator to determine the relative ordering of two elements?

## Question 4

`sort::insertion(collection.begin(), collection.end());` will sort elements in ascending order.

How would you call `sort::insertion` to sort elements in descending order (greatest to least)? (Be prepared to provide implementation details, including how to call `sort::insertion`.)

## Question 5

Each algorithm you implemented gradually grows a sorted subarray. In each algorithm, there is a contiguous set of elements within the list that is guaranteed to be sorted on each iteration.

Provided your implementation, where is the sorted subarray located within the input array? Between successive iterations, how does the sorted subarray grow?

## Question 6

How many comparisons does each algorithm perform in the best case? (Provide a formula based on the length `n` of the input array.) For each algorithm, what is the configuration of the input array which produces the best-case outcome?

## Question 7

Would your sorts still work if `RandomIter` was not a random iterator, but instead a "bidirectional" iterator that can only go forward or backward one element at a time (e.g. `typename std::list<T>::iterator`)?

## Question 8

Use `main.cpp` to test the number of comparisons performed by bubble, insertion, and selection on randomly generated data. (Save your results to discuss them during the report.) Which algorithm performs the fewest comparisons? What mechanism causes this algorithm to perform many fewer comparisons when sorting randomly generated data?

## Question 9

How might you write a `CustomComparator` that, when used by any of the sorts, will rearrange all of the even numbers to the beginning of the container and the odd numbers to the end?

*Hint*: You do not have to sort the even or the odd numbers with respect to themselves; you only need to ensure that every even number precedes all odd numbers.

*Hint*: Look at the `CustomComparator` class written in [`main.cpp`](src/main.cpp).
