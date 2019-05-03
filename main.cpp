
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

int main()
{

    int index;
    int words = 0;
    int count = 0;

    string word;
    string wordCpy;
    hashTab hashObj;

    index = hashObj.hashInd("Jesus");

    cout << "The index size is " << index << endl << endl;


    string dir = string("/Users/jeffreyliew/CLionProjects/plagiarismCatcher/sm_doc_set");
    vector<string> files = vector<string>();

    getdir(dir,files);

    for (unsigned int i = 2;i < files.size();i++) {
        cout << i << files[i] << endl;
        queue <string> chunk;
        ifstream inFile;
        char c;
        int space = 0;
        inFile.open("/Users/jeffreyliew/CLionProjects/plagiarismCatcher/sm_doc_set/" + files[i]);
        while(inFile >> word){
            for(int j = 0; j < word.length(); j++){
                if(isalnum(word[j])){
                    if(isupper((int)word[j])){
                        word[j] += 32;
                    }
                    wordCpy += word[j];
                }
            }
            chunk.push(wordCpy);
            cout << chunk.back() << endl;

            if(chunk.size() == 6){
                cout << "Success" << endl;
                //call hash comparison


                //pop first one in queue
                chunk.pop();
            }
            wordCpy = "";
            words++;
        }



        inFile.close();

    }
    return 0;
}