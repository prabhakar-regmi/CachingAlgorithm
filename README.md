# CachingAlgorithm

Least Last Used Cache Implemented using C++.

## Implementation

This is implemented as a library class. Class ``LRUCache`` wraps around a hash-map (in C++, this is done using the STL `unordered map`). This hash-map ensures a `O(n)` lookup for the hash-key. The hash-key is set as a `string`. The data value is templated - so that we can use this class for generic cases.

The least last used algorithm is implemented by using a doubly linked list. The hash key that was called last is always put at the top of the list. A doubly linked list is used to ensure that we can cleanly remove an element from the list and place it at the top (or remove the last element if required!)

The class ``LRUCache`` is included in the unit-tests in the ``LRUCache.sln`` unit-test solution on Visual Studio. The test file has various test cases that tests each and every ``public`` functions used in the class ``LRUCache``. 

## How To Run

The class ``LRUCache`` is implemented in a header (`.h`) file. The class is tested using the #Google Test For C++# in Microsoft Visual Studio. In MS Visual Studio, I have created a unit test solution. This solution can compile fine if the "Test Adaptor for Google Test" extension is added to Visual Studio, under `Extensions` -> `Manage Extensions` menu.

The ``LRUCache.sln`` file (that is the unit test project) can then be just compiled and run with Visual Studio.

## Developer Info

This is developed by Prabhakar Regmi
