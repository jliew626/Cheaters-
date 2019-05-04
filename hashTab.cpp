//
// Created by Jeffrey Liew on 2019-05-02.
//

#include <cstdlib>
#include <string>
#include <iostream>
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
    int index = hashInd(key);
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

int hashTab::hashInd(string key){
    unsigned int hash = 0;
    int index;
    int len = (int)key.length();

    for(int i = 0; i < len; i++){
        hash = hash*54059 ^ (76963*(int)key[i]);
    }

    index = hash % tableSize;

    return index;

}

int hashTab::compDoc(string n1, string n2){
    bool flag1 = false;
    bool flag2 = false;
    int count = 0;
    for(int i = 0; i < tableSize; i++){
        doc *ptr = HashTable[i];
        while(ptr->next != NULL){
            if(ptr->name == n1){
                flag1 = true;
            }
            if(ptr->name == n2){
                flag2 = true;
            }
            ptr = ptr->next;
        }
        if(flag1 && flag2){
            count++;
            flag1 = false;
            flag2 = false;
        }
    }
    return count;
}
