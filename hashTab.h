//
// Created by Jeffrey Liew on 2019-05-02.
//

#ifndef PLAGIARISMCATCHER_HASH_H
#define PLAGIARISMCATCHER_HASH_H

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

class hashTab{

private:
    static const int tableSize = 1000;
    static const int chunkSize = 6;

    struct doc{
        string name;
        doc *next;
    };

    doc *HashTable[tableSize];

public:
    hashTab();
    int hashInd(string key);
    void addDoc(string name);
    int numDoc(int index);
};




#endif //PLAGIARISMCATCHER_HASH_H


