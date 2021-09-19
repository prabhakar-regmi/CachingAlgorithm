#include <iostream>
#include "src/LRUCache.h"
using namespace std;

int main()
{
	LRUCache<double> cache(5);
	cache.Put("first", 1);
	cache.Put("second", 2);
	cache.Put("third", 3);

	// Get the second
	auto res = cache.Get("second");
	if (res.second) {
		cout << res.first << ", Expected = 2 " << std::endl;
	}

	// Put another value at second and display the value
	cache.Put("second", -1);
	res = cache.Get("second");
	if (res.second) {
		cout << res.first << ", Expected = -1 " << std::endl;
	}

	// Put more values
	cache.Put("fourth", 4);
	cache.Put("fifth", 5);

	//Get the second
	res = cache.Get("second");
	if (res.second) {
		cout << res.first << ", Expected = -1" << std::endl;
	}
	cache.Put("second", 2);
	res = cache.Get("second");
	if (res.second) {
		cout << res.first << ", Expected = 2" << std::endl;
	}
	// The cache should be full now.
	// The potential cache to be evicted is "first"
	// Then, the potential cache to be evicted is third (second has been used twice)
	cache.Put("sixth", 6);
	res = cache.Get("first");
	if (res.second) cout << "NOT EXPECTED: First has NOT be evicted!!\n";
	else cout << "EXPECTED: First has been evicted!!\n";

	cache.Put("seventh", 7);
	res = cache.Get("second");
	if (res.second) cout << "EXPECTED: Second has NOT be evicted!!\n";
	else cout << "NOT EXPECTED: Second has been evicted!!\n";

	return 0;
}