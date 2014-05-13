/**
 * @file dictionary.h
 */

#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_
#include <algorithm>
/**
 * Implements the dictionary ADT.
 *
 * The implementation is up to you, but you must complete all the given
 *  public functions. You will need to add some member variables and private
 *  helper functions.
 */
template <class K, class V>
class Dictionary
{
    public:
        /**
         * Constructor: creates an empty dictionary.
         */
        Dictionary();

		~Dictionary();

        /**
         * Inserts the given key, value pair into the dictionary.
         * If the key already exists, do nothing.
         *
         * @param key The key to be inserted.
         * @param value The value to be inserted.
         */
        void insert(const K & key, const V & value);

        /**
         * Removes the given key (and its associated data) from the
         *  dictionary.
         *
         * @param key The key to be removed.
         */
        void remove(const K & key);

        /**
         * Finds the value associated with a given key.
         *
         * @param key The key whose data we want to find.
         * @return The value associated with this key, or the default value
         *  (V()) if it was not found.
         */
        V find(const K & key);

        /**
         * Determines if the given key exists in the dictionary.
         *
         * @param key The key we want to find.
         * @return A boolean value indicating whether the key was found.
         */
        bool keyExists(const K & key);

        /**
         * Determines if the dictionary is empty. Should be O(1).
         *
         * @return A boolean value indicating whether the dictionary is
         *  empty.
         */
        bool isEmpty() const;

		

    private:
		class SkipNode{
			public:
				//default node constructor
				SkipNode(int h);
				//constructs node with the given data
				SkipNode(K k, V d, int h);
				//destructor
				~SkipNode();
				//getters
				K getKey();
				V getData();
				int getHeight();
				SkipNode** fwdNodes;

			private:
				int height;
				K key;
				V data;
		};
		SkipNode* head;
		SkipNode* tail;
		float probability;
		int maxHeight;
		int curHeight;
		int newLevel();
		int size;

};

#include "dictionary.cpp"
#endif
