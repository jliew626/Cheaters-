// hashTab.h
/*Student information for project:
 *
 * Replace <NAME> with your name.
 *
 * On my honor, <Adin Lee>, this programming project is my own work
 * and I have not provided this code to any other student.
 *
 * Name: Adin Lee & Jeffrey Liew
 * email address: adinlee@utexas.edu & jliew626@utexas.edu
 * UTEID: ael2575 & jyl662
 * Section 5 digit ID: 15975
*/

#ifndef HASHTAB_H
#define HASHTAB_H

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

class hashTab{

private:
    static const int tableSize = 50000;
    static const int chunkSize = 6;

    struct doc{
        string name;
        string chunk;
        doc *next;
    };

    doc *HashTable[tableSize];

public:
    hashTab();
    int hashInd(string key);
    void addDoc(string key, string name);
    int numDoc(int index);
    int compDoc(string n1, string n2);

};

#endif //HASHTAB_H
