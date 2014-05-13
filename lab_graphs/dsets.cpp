/*
dsets.cpp -- MP7
*/
#include "dsets.h"
#include <stdio.h>

void DisjointSets::addelements(int n)
{
    /*for (int i = 0; i < n; n++)
        uptree.push_back(-1);*/

    // changed to resize function because loop was taking forever.............why?
    uptree.resize(uptree.size() + n, -1);
}

int DisjointSets::find(int a)
{
    if (uptree[a] < 0)
        return a;
    return find(uptree[a]);
}

void DisjointSets::setunion(int a, int b)
{
    a = find(a);
    b = find(b);

    //if already in the same set, do nothing
    if (a == b)
        return;

    //if they are in different sets, then set those sets to be the same
    int newSize = uptree[a] + uptree[b];
    if (uptree[a] <= uptree[b]) // a has more elements than b
    {
        uptree[b] = a; // add b(smaller) to a_root
        uptree[a] = newSize;
    }

    else // b has more elements than a
    {
        uptree[a] = b; // add a (smaller) to b_root
        uptree[b] = newSize;
    }

}
