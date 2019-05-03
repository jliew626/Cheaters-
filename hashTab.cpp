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
        HashTable[i]->next = NULL;
    }
}

void hashTab::addDoc(string name) {
    int index = hashInd(name);
    if(HashTable[index]->name == ""){
        HashTable[index]->name = name;
    }
    else{
        doc *ptr = HashTable[index];
        doc *n = new doc;
        n->name = name;
        n->next = NULL;
        while(ptr->next != NULL){
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
    }
}


int hashTab::hashInd(string key){

    int hash = 0;
    int index;
    int len = key.length();

    for(int i = 0; i < len; i++){
        cout << "Index " << i << " is " << (int)key[i] << endl;
        hash += (int)key[i];
    }

    index = hash % tableSize;

    return index;

}
