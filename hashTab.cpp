// hashTab.cpp
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
//
// Created by Jeffrey Liew on 2019-05-02.
//

#include <cstdlib>
#include <string>
#include <iostream>
#include <math.h>
#include "hashTab.h"

using namespace std;

hashTab::hashTab(){
    for(int i = 0; i < tableSize; i++){
        HashTable[i] = new doc;
        HashTable[i]->name = "";
        HashTable[i]->chunk = "";
        HashTable[i]->next = NULL;
    }
}

void hashTab::addDoc(string key, string name) {
    long long int index = hashInd(key);
    string check = HashTable[index]->name;
    if(HashTable[index]->name == ""){
        HashTable[index]->name = name;
        HashTable[index]->chunk = key;
    }
    else{
        if(HashTable[index]->name == name){
            return;
        }
        doc *ptr = HashTable[index];
        doc *n = new doc;
        n->name = name;
        n->chunk = key;
        n->next = NULL;
        while(ptr->next != NULL){
            if(ptr->next->name == name){
                return;
            }
            ptr = ptr->next;
        }
        ptr->next = n;
    }
}

int hashTab::numDoc(int index){
    int count = 0;
    if(HashTable[index]->name == ""){
        return count;
    } else{
        count++;
        doc *ptr = HashTable[index];
        while(ptr->next != NULL){
            count++;
            ptr = ptr->next;
        }
        return count;
    }
}

long long int hashTab::hashInd(string key){
    unsigned long long hash = 0;
    unsigned long long index;
    long int len = (int)key.length();

    for(int i = 0; i < len; i++){
        //hash += hash*54059 ^ (76963*(int)key[i]);
        //hash += (54059*key[i]) ^ (unsigned long long)(233*i);
        hash += (int)key[i] * (unsigned long long)(pow(23,i));
    }

    hash = hash % tableSize;

    return hash;

}

int hashTab::compDoc(string n1, string n2){
    bool flag1 = false;
    bool flag2 = false;
    int count = 0;
    for(int i = 0; i < tableSize; i++){
        doc *ptr = HashTable[i];
        while(ptr->next != NULL && !(flag1 && flag2)){
            if(ptr->name == n1){
                flag1 = true;
                if(ptr->next->name == n2){
                    flag2 = true;
                }
            }
            else if(ptr->name == n2){
                flag2 = true;
                if(ptr->next->name == n1){
                    flag1 = true;
                }
            }
            ptr = ptr->next;
        }
        if(flag1 && flag2){
            count++;
            flag1 = false;
            flag2 = false;
        }
        //reset flags
        flag1 = false;
        flag2 = false;
    }
    return count;
}