#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "dirent.h"

using namespace std;

// function gettxtfiles return a vector of txt files in the directory provided in the argument
vector<string> gettxtfiles(char* dir) {
    struct dirent* entry;
    DIR* dp;
    vector<string> files;
    string temp;

    dp = opendir(dir);
    
    while((entry=readdir(dp)) !=NULL) {
	if(entry->d_type == 0x8) {
	    temp = string(entry->d_name);
	    if(temp.length()-3>0 && temp.substr(temp.length()-3, 3) == "txt") {
		files.push_back(temp);
	    }
	}
    }
    return files;
}


int main(int argc, char** argv){

// get the list of text files in the input directory
    vector<string> txtfiles = gettxtfiles(argv[1]);
    if (txtfiles.size() == 0) {
	cerr << "no txt files in the input directory." << endl;
	exit(1);
    }

// open each file in the files vector and read one line a time and parse into words.
    map<string, int> wordlist;
    string c;
    for (vector<string>::iterator it=txtfiles.begin(); it != txtfiles.end(); ++it) {
	c = "./"+string(argv[1])+"/"+*it;
	ifstream infile;
	infile.open(c.c_str());

	while(infile.good()) {
	    char line[100];
	    infile.getline(line, 100);
            if( strlen(line) == 0) {
		continue;
	    }
	    istringstream iss(line);
	    string sub;
	    while (iss >> sub) {
		for(char lastch = sub.back(); lastch ==',' || lastch == '.' || lastch == '?' || lastch == '!';lastch = sub.back())
		{ 
		    sub.pop_back();
		}
// change a word stored in sub into lowercase
		transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
// pub the word in sub in the wordlist vector: create a new entry if it is new, otherwise ++value
		if (wordlist.find(sub) == wordlist.end()) {
		    wordlist.insert(pair<string, int>(sub, 1));
		} else
		{ 
		    ++wordlist[sub];
		}
	    }
	}
	infile.close();
    }
// output wordlist into a file
    ofstream output;
    output.open(argv[2]);
    for(map<string, int>::iterator it = wordlist.begin(); it != wordlist.end(); ++it)
    {
	output << it->first << " " << it->second << endl;
    }
    output.close();
}
