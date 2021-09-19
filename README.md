# CachingAlgorithm

Least Last Used Cache Implemented using C++.

## Implementation

This is implemented as a library class. Class ``LRUCache`` wraps around a hash-map (in C++, this is done using the STL `unordered map`). This hash-map ensures a `O(n)` lookup for the hash-key. The hash-key is set as a `string`. The data value is templated - so that we can use this class for generic cases.

The least last used algorithm is implemented by using a doubly linked list. The hash key that was called last is always put at the top of the list. A dubly linked list is used to ensure that we can cleanly remove an element from the list and place it at the top (or remove the last element if required!)


## Developer Info

This is developed by Prabhakar Regmi
