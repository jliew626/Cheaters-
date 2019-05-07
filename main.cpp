
// main.cpp
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
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>

#include "hashTab.h"


using namespace std;


/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }

    closedir(dp);
    return 0;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void swapStr(string *xp, string *yp)
{
    string temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int main(int argc, char *argv[]){

    int index;
    int words = 0;
    int count = 0;
    int chunkSize = atoi(argv[2]);
    int cPlag = atoi(argv[3]);

    string word;
    string wordCpy;
    string wordQueue;
    hashTab hashObj;

    string dir = string(argv[1]);
    vector<string> files = vector<string>();

    getdir(dir,files);

    files.erase(files.begin());
    files.erase(files.begin());


    for (unsigned int i = 0;i < files.size();i++) {
        //cout << i << files[i] << endl; SHOW FILE NAME
        queue <string> chunk;
        ifstream inFile;
        int queueSize = 0;
        string toChar = (string(argv[1]) + "/" + files[i]);
        inFile.open(toChar.c_str());
        while(inFile >> word) {
            // turn words into alphanumeric characters only
            for (int j = 0; j < word.length(); j++) {
                if (isalnum(word[j])) {
                    if (islower((int)word[j])) {
                        wordCpy += (word[j] - 32); //make upperrcase
                    } else {
                        wordCpy += word[j];
                    }
                }
            }
            wordQueue += wordCpy;
            queueSize++;
            chunk.push(wordCpy); // push
            if (queueSize == chunkSize) {
                hashObj.addDoc(wordQueue, files[i]);
                //cout << "Document " << files[i] << " has key: " << wordQueue << endl;
                chunk.pop(); //pop first one in queue
                wordQueue = "";
                for(int k = 0; k < 5; k++) {
                    //chunk.push(chunk.front);
                    wordQueue += chunk.front();
                    wordCpy = chunk.front();
                    chunk.pop();
                    chunk.push(wordCpy);
                }
                queueSize--;
            }
            wordCpy = "";
            words++;
        }
        wordQueue = "";
        queueSize = 0;
        words = 0;
        inFile.close();
    }

    cout << endl << "Plagrism Result " << endl;
    cout << "--------------------------------------------------" << endl;

    // kind of a debug tool for hashtable
    /*for(int a = 0; a < 250000; a++){
        cout << "Index " << a << " has " << hashObj.numDoc(a) << " documents." << endl;
    }*/

    // 2D Array
    int sCheck = (int)files.size();
    int arr[sCheck][sCheck];
    /*arr[0][0] = 0;
    cout << "Making Array" << endl;
    for(int i = 0; i < sCheck; i++){
        for(int j = 0; j < sCheck; j++){
            arr[i][j] = 0;
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }*/


    /*cout << "Making Array" << endl;
    for(int i = 0; i < sCheck; i++){
        for(int j = 0; j < sCheck; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }*/
    int nCount = 0;
    vector<int> numPlag(0);
    vector<string> docPlag(0);

    for(int i = 0; i < sCheck; i++) {
        for (int j = 0; j < sCheck; j++) {
            if(i != j){
                if(i > j){
                    arr[i][j] = hashObj.compDoc(files[i], files[j]);
                    if(arr[i][j] > cPlag){
                        cout << "We found " << arr[i][j] << " chunks of similaries between " << files[i] << " and " << files[j] << "." << endl;
                        numPlag.push_back(arr[i][j]);
                        docPlag.push_back(files[i]);
                        docPlag.push_back(files[j]);
                        nCount++;
                    }
                }
            }
        }
    }

    //Sorting Array
    int i, j, max;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < nCount; i++)
    {
        max = i;
        for (j = i+1; j < nCount; j++) {
            if (numPlag[j] > numPlag[max]){
                max = j;
            }
        }
        swap(&numPlag[max], &numPlag[i]);
        swapStr(&docPlag[max*2], &docPlag[i*2]);
        swapStr(&docPlag[max*2 + 1], &docPlag[i*2 + 1]);
    }

    cout << endl << "Sorted Results: " << endl;
    cout << "--------------------------------------------------" << endl;
    for(int i = 0; i < nCount; i++){
        //print values
        cout << numPlag[i] << ": " << docPlag[i*2] << " & " << docPlag[i*2+ 1] << endl;
    }

    /*cout << "Making Array" << endl;
    for(int i = 0; i < sCheck; i++){
        for(int j = 0; j < sCheck; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }*/
    return 0;
}