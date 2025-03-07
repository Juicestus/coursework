Binary Search Tree Oral Report
===============================

The following questions are some additional questions you can use to see your understanding of the programming assignment as well as other implementations of the code.

In previous semesters, this was used for a report conducted in lab - that is no longer used at this point. This REPORT.md file is not particularly for any grade, but could be of some help on your canvas programming assignment demo.

Question 1
----------

What traversals are performed by `clear`, `printTree`, and `clone`? What is the time complexity of each method? Justify your answer with a recurrence.

Question 2
----------

 
Binary search trees provide many useful algorithms and operations. These include search, insertion, removal, traversals, and min/max. Although, many of these same algorithms and operations can be carried out using a combination of sorting and binary search on a contiguous memory structure.
 
You are considering whether to use a binary search tree or a sorted dynamic array. E.g. comparing a binary search tree with `n` integers and a tree with `n` integers.

```
Array: 1, 7, 9, 10, 12

BST:
       9
      / \
     7   12
    /    /
   1    10
```
 
Compare the two approaches and the algorithmic complexity of search, insertion, removal, min/max, and space-complexity. Provide a concrete example where trees are superior to binary search and sorting. Also, an example where binary search and sorting is superior to search trees.

Question 3:
-----------

Consider the following insert methods:

```C++
void insert(K const & key, T const & value) {
	Node** cur = head;

	while(cur) {
		if(key is less than the key(cur))
			change cur to the left pointer of cur;
		else if (key is greater than key(cur))
			change cur to the right pointer of cur;
		else
			handle;
	}

	cur = new Node(/* args */);
}
```

```C++
void insert_helper(K const & key, T const & value, Node *& n) {
	if(!n) {
		n = new Node(/* args */);
	}


	if(key is less than the key(n))
		insert_helper(key, value, left(n));
	else if (key is greater than key(n))
		insert_helper(key, value, right(n));
	else
		handle;
}
```


The first method implements a traversal using an iterative method. The second method implements a traversal using a recursive method.  As you may remember from CSCE 121, each time a function is called, some accounting information is saved on the stack. This includes the return address, local variables, function arguments, and some previous state. Assuming each function call takes O(1) memory due to the stack frame, what is the memory complexity of each insert method?

Question 4:
-----------

Consider a binary search tree where for any given node, 20% of its children reside in the left half subtree and 80% of its children reside in the right half subtree. In this highly unbalanced tree, what is the average runtime of the insert function? Justify your answer.

Question 5:
-----------

You are writing a program which determines the reading complexity of text. To accomplish this, a human creates a complexity score for each word. The complexity values and words are stored in a binary search tree as (word, score) key-value pairs. The program iterates through all words in the text and sums the complexity values. 

### 5.1

Assuming there are `n` words in the text and `k` words in the dictionary (which are all inserted into the tree), what is the average time complexity of this algorithm assuming the search tree is perfectly balanced? Now, assume the programmer reads the words from a file sorted in alphabetical order by the word. These are inserted into the tree in alphabetical order. What is the runtime of the algorithm?

### 5.2

Considering the suboptimal runtime of inserting the (word, score) pairs in ascending order, design an algorithm to insert the pairs in an alternative order to build the most efficient tree. You can assume the pairs have been read in alphabetical order and appended to the end of a vector. Describe the significant details of your algorithm. Is there any significance to the order in which elements are inserted?

Question 6:
-----------

The STL `ordered_map` container utilized a binary search tree to store key value pairs. Like all STL containers, they support an iterator which allows you to traverse through the tree in-order. This can be implemented by maintaining a pointer to the parent in each node. Instead, consider implementing an iterator using a stack to store pointers to the parent nodes. (The nodes themselves do not have parent pointers.) Describe how an increment operation should be performed.

Question 7:
-----------

Many algorithms in machine learning and robotics rely on spatial locality to make decisions. Examples include hierarchical clustering, region growing, cluster extraction, and normal estimation among others. Take one of the best examples - k-nearest neighbors. This requires you to find `k` nearest points `x_1`, `x_2`, `x_3`, …, `x_k` to a target point `x_t`. In other words, find the k nearest points in space to the target point. 

Consider a simpler version of the algorithm - the 1-nearest neighbor. How would you use a tree to efficiently find the nearest neighbor to a given point lying on a 1D number line? What is the complexity of this algorithm? (Hint: use a tree and remember your traversals.)

```
X: 0 7 14 18 23 28 35 39
nearest_neighbor(18) = 18
nearest_neighbor(19) = 18
nearest_neighbor(37) = 35
```
