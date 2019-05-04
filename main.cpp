
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

int main(){

    int index;
    int words = 0;
    int count = 0;
    int chunkSize = 0;
    int cPlag = 0;
    cout << "Identify a chunk size: ";
    cin >> chunkSize;
    cout << endl << "Give an appropriate plagrism count: ";
    cin >> cPlag;

    string word;
    string wordCpy;
    string wordQueue;
    hashTab hashObj;

    string dir = string("/Users/jeffreyliew/CLionProjects/plagiarismCatcher/sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir,files);

    files.erase(files.begin());
    files.erase(files.begin());


    for (unsigned int i = 0;i < files.size();i++) {
        //cout << i << files[i] << endl; SHOW FILE NAME
        queue <string> chunk;
        ifstream inFile;
        char c;
        int space = 0;
        inFile.open("/Users/jeffreyliew/CLionProjects/plagiarismCatcher/sm_doc_set/" + files[i]);
        while(inFile >> word) {
            // turn words into alphanumeric characters only
            for (int j = 0; j < word.length(); j++) {
                if (isalnum(word[j])) {
                    if (isupper((int) word[j])) {
                        word[j] += 32; //make lowercase
                    }
                    wordCpy += word[j];
                }
            }
            wordQueue += wordCpy;
            chunk.push(wordCpy); // push
            //int cInd[1000]; // checks if there are any matching indexes
            //int kInd;
            //int k = 0;
            //bool restart = false;
            if (chunk.size() == chunkSize) {
                //Checking for Collison
                /*while(cInd[index] == 1){
                    if(k == 1000){
                        cInd[index] = 0;
                    }
                    if(index + k > 999){
                        k = index;
                        index = 0;
                        restart = true;
                    }
                    else if(restart){
                        k++;
                    }
                }*/
                hashObj.addDoc(wordQueue, files[i]);
                //pop first one in queue
                chunk.pop();
                wordQueue = "";
                for(int k = 0; k < 5; k++) {
                    chunk.push(chunk.front());
                    wordQueue += chunk.front();
                    chunk.pop();

                }
            }
            wordCpy = "";
            words++;
        }
        words = 0;
        inFile.close();
    }

    /*
    for(int a = 0; a < 50000; a++){
        cout << "Index " << a << " has " << hashObj.numDoc(a) << " documents." << endl;
    }*/

    // 2D Array
    int sCheck = (int)files.size();
    int arr[sCheck][sCheck];
    arr[0][0] = 0;
    for(int i = 0; i < sCheck; i++){
        for(int j = 1; j < sCheck; j++){
            arr[i][j] = 0;
        }
        cout << endl;
    }

    /*
    int arr[sCheck+1][sCheck+1];
    arr[0][0] = 0;
    for(int i = 1; i < sCheck; i++){
        arr[i][0] = i;
        arr[0][i] = i;
        for(int j = 1; j < sCheck; j++){
            arr[i][j] = 0;
        }
        cout << endl;
    }*/

    /*
    cout << "Making Array" << endl;
    for(int i = 0; i < sCheck; i++){
        for(int j = 0; j < sCheck; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }*/

    for(int i = 0; i < sCheck; i++) {
        for (int j = 0; j < sCheck; j++) {
            if(i != j){
                if(i > j){
                    arr[i][j] = hashObj.compDoc(files[i], files[j]);
                    if(arr[i][j] > cPlag){
                        cout << "We found " << arr[i][j] << " chunks of similaries between " << files[i] << " and " << files[j] << "." << endl;
                    }
                }

            }
        }
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

