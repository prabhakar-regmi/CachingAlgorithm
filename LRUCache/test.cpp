#include "pch.h"
#include "../src/LRUCache.h"
#include <vector>
using namespace std;

struct RandomObject
{
	vector<int> y = { 1, 2, 3 };
	double x = 0.0021;
	bool* b = nullptr;
	int z = 12;
};

TEST(TestCapacityAndSize, TestExceptionThrown)
{
	// The capacity should be more than or equal to 3
	for (int i = -10; i < 3; ++i)
	{
		EXPECT_ANY_THROW(LRUCache<vector<int>> c(i));
	}
	for (int i = 3; i < 100; ++i)
	{
		EXPECT_NO_THROW(LRUCache<RandomObject> c(i));
	}
}

TEST(TestCapacityAndSize, TestCapacity) 
{
	for (int i = 3; i < 100; i++)
	{
		LRUCache<int> cache(i);
		EXPECT_EQ(cache.Capacity(), i);
	}
}

TEST(TestCapacityAndSize, TestSize)
{
	LRUCache<int> cache(10);

	// Add 4 records
	for (int i = 1; i <= 4; ++i)
	{
		cache.Put(to_string(i), i);
	}

	// Modify the previous records
	cache.Put("4", 5);
	cache.Put("4", 4);
	
	// Get the previous rercords
	auto res = cache.Get("3");
	res = cache.Get("1");
	res = cache.Get("4");

	// Get the size of the cache - should be 4!
	EXPECT_EQ(cache.Size(), 4);

	// fill up the cache
	for (int i = 5; i <= 10; ++i)
	{
		cache.Put(to_string(i), i);
	}
	EXPECT_EQ(cache.Size(), 10);

	// overflow the cache
	for (int i = 11; i <= 15; ++i)
	{
		cache.Put(to_string(i), i);
	}

	// Size shouldn't be more than the capacity of the cache!
	EXPECT_EQ(cache.Size(), 10);
}

TEST(TestFunctionality, TestPut)
{
	int x = 100; // capacity of the cache
	LRUCache<RandomObject> cache(x);

	// Put 100 values (Random Objects)
	for (int i = 0; i < x; ++i)
	{
		RandomObject obj;
		obj.z = i*i;
		cache.Put(to_string(i), obj);
	}

	auto res = cache.Get("99");
	EXPECT_TRUE(res.second);
	EXPECT_EQ(res.first.z, 99 * 99);

	// Overflow the cache - first item will be removed
	RandomObject val;
	val.z = 100;
	cache.Put("100", val);
	EXPECT_FALSE(cache.Get("0").second);
	EXPECT_TRUE(cache.Get("100").second);
	EXPECT_EQ(cache.Get("100").first.z, 100);

	// Modify the cache for second and third item
	// It will move to the head
	EXPECT_EQ(cache.Get("1").first.z, 1);
	EXPECT_EQ(cache.Get("2").first.z, 4);

	val.z = 1;
	cache.Put("1", val);
	val.z = 2;
	cache.Put("2", val);

	// index 3 should be at the bottom
	// Let's remove by putting another cache entry
	val.z = 101;
	cache.Put("101", val);
	EXPECT_TRUE(cache.Get("1").second);
	EXPECT_EQ(cache.Get("1").first.z, 1);
	EXPECT_TRUE(cache.Get("2").second);
	EXPECT_EQ(cache.Get("2").first.z, 2);
	EXPECT_TRUE(cache.Get("101").second);
	EXPECT_EQ(cache.Get("101").first.z, val.z);

	// "3" has been evicted
	EXPECT_FALSE(cache.Get("3").second);
}

TEST(TestFunctionality, TestGet)
{
	int x = 100; // capacity of the cache
	LRUCache<string> cache(x);

	// Put 100 values (Random Objects)
	for (int i = 0; i < x; ++i)
	{
		cache.Put(to_string(i), to_string((i+2) * (i+2)));
	}

	// Effectively puts "0" in the list of least last visited
	// Will not be evicted 
	auto res = cache.Get("0");
	EXPECT_TRUE(res.second);
	EXPECT_EQ(res.first, "4");

	// overflow the cache
	cache.Put("100", to_string(102*102));

	res = cache.Get("100");
	EXPECT_TRUE(res.second);
	EXPECT_EQ(res.first, to_string(102*102));
	EXPECT_FALSE(cache.Get("1").second); // "1" has been evicted

	//  Get the values for "3" and "5"
	res = cache.Get("3");
	EXPECT_TRUE(res.second);
	EXPECT_EQ(res.first, to_string(5 * 5));
	res = cache.Get("5");
	EXPECT_TRUE(res.second);
	EXPECT_EQ(res.first, to_string(7 * 7));

	// "2","4","6","7"... should be in line for eviction
	cache.Put("101", "101");
	EXPECT_TRUE(cache.Get("101").second);
	EXPECT_FALSE(cache.Get("2").second);
	// the previous Get command didn't mistakenly add this entry
	EXPECT_FALSE(cache.Get("2").second);

	cache.Put("102", "102");
	EXPECT_TRUE(cache.Get("102").second);
	EXPECT_FALSE(cache.Get("2").second);
	EXPECT_FALSE(cache.Get("4").second);

	cache.Put("103", "103");
	EXPECT_TRUE(cache.Get("103").second);
	EXPECT_FALSE(cache.Get("2").second);
	EXPECT_FALSE(cache.Get("4").second);
	EXPECT_FALSE(cache.Get("6").second);
	EXPECT_TRUE(cache.Get("7").second);
}