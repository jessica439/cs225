/**
 * @file unit_tests.cpp
 * Unit tests for the dictionary class.
 *
 * @author Sean Massung
 * @date Fall 2012
 */

#include <vector>
#include <map>
#include <utility>
#include <ctime>
#include <cstdlib>
#include <string>
#include "dictionary.h"
#include "proxy.h"

using std::vector;
using std::pair;
using std::make_pair;
using std::string;
using std::map;

UNIT_TEST(insert_find_1, 0, 14, 1000)
{
    Dictionary<string, char> dict;

    dict.insert("a", 'a');
    dict.insert("b", 'b');
    dict.insert("c", 'c');
    dict.insert("d", 'd');
    dict.insert("e", 'e');

    ASSERT(dict.find("a") == 'a');
    ASSERT(dict.find("b") == 'b');
    ASSERT(dict.find("c") == 'c');
    ASSERT(dict.find("d") == 'd');
    ASSERT(dict.find("e") == 'e');
}

UNIT_TEST(insert_find_2, 0, 14, 2000)
{
    Dictionary<int, int> dict;
    map<int, int> soln;

    srand(1234);
    for(int i = 0; i < 10000; ++i)
    {
        // if duplicate key, ignore!!
        int key = rand() % 1000;
        int value = rand() % 1000;
        dict.insert(key, value);
        soln.insert(make_pair(key, value));
    }

    for(map<int, int>::iterator it = soln.begin(); it != soln.end(); ++it)
        ASSERT(dict.find(it->first) == it->second);
}

UNIT_TEST(empty_remove, 0, 5, 1000)
{
    Dictionary<size_t, size_t> dict;
    dict.remove(47);
}

UNIT_TEST(insert_remove_1, 0, 20, 1000)
{
    Dictionary<string, string> dict;
    
    dict.insert("abcdef", "");
    dict.insert("ghijkl", "first");
    dict.insert("mnopqr", "");
    
    dict.remove("ghijkl");
    dict.insert("ghijkl", "second");

    ASSERT(dict.find("ghijkl") == "second");
}

UNIT_TEST(insert_remove_2, 0, 21, 2000)
{
    Dictionary<int, int> dict;
    map<int, int> soln;

    // insert a bunch of keys
    srand(4747);
    for(int i = 0; i < 10000; ++i)
    {
        // if duplicate key, ignore!!
        int key = rand() % 1000;
        int value = rand() % 1000;
        dict.insert(key, value);
        soln.insert(make_pair(key, value));
    }

    // randomly remove half

    vector<int> toRemove;
    for(map<int, int>::iterator it = soln.begin(); it != soln.end(); ++it)
    {
        if(rand() % 2)
            toRemove.push_back(it->first);
    }

    for(vector<int>::iterator rem = toRemove.begin(); rem != toRemove.end(); ++rem)
    {
        soln.erase(soln.find(*rem));
        dict.remove(*rem);
    }

    // make sure the removed half is gone
    for(vector<int>::iterator rem = toRemove.begin(); rem != toRemove.end(); ++rem)
        ASSERT(!dict.keyExists(*rem));

    // make sure the other half is still there
    for(map<int, int>::iterator it = soln.begin(); it != soln.end(); ++it)
        ASSERT(dict.find(it->first) == it->second);
}

UNIT_TEST(is_empty_1, 0, 5, 1000)
{
    Dictionary<int, int> dict;
    dict.insert(1, 2);
    ASSERT(dict.find(1) == 2);
    dict.remove(1);
    ASSERT(dict.isEmpty());
}

UNIT_TEST(is_empty_2, 0, 5, 1000)
{
    Dictionary<int, int> dict;
    map<int, int> soln;

    srand(4321);
    for(int i = 0; i < 1000; ++i)
    {
        // if duplicate key, ignore!!
        int key = rand() % 100;
        int value = rand() % 100;
        dict.insert(key, value);
        soln.insert(make_pair(key, value));
    }

    for(map<int, int>::iterator it = soln.begin(); it != soln.end(); ++it)
        dict.remove(it->first);

    ASSERT(dict.isEmpty());
}

VALGRIND_TEST(valgrind_1, 0, 8, 3000)
{
    Dictionary<int, int>* dict = new Dictionary<int, int>;

    srand(225);
    dict->insert(1, 1);
    for(int i = 0; i < 2000; ++i)
        dict->insert(rand() % 100, rand() % 100);

    ASSERT(dict->find(1) == 1);
    delete dict;
}

VALGRIND_TEST(valgrind_2, 0, 8, 3000)
{
    Dictionary<string, int>* d1 = new Dictionary<string, int>;
    d1->insert("a", 1);
    d1->insert("b", 2);
    d1->insert("c", 3);
    
    Dictionary<string, int>* d2 = new Dictionary<string, int>(*d1);
    delete d1;

    ASSERT(d2->find("a") == 1);
    ASSERT(d2->find("b") == 2);
    ASSERT(d2->find("c") == 3);
    delete d2;
}
