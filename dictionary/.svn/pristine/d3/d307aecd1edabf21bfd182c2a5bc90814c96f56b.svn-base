#include <iostream>
#include <string>
#include "dictionary.h"
using namespace std;

int main(int argc, char* argv[])
{
    Dictionary<string, int> dict;
    cout << "Empty? " << dict.isEmpty() << endl;

    dict.insert("hello", 42);
    cout << "Empty? " << dict.isEmpty() << endl;
    cout << "keyExists(\"hello\"): " << dict.keyExists("hello") << endl;
    cout << "find(\"hello\"): " << dict.find("hello") << endl;

    dict.remove("hello");
    cout << "Empty? " << dict.isEmpty() << endl;

    return 0;
}
