#include <iostream>
#include <string>
#include <vector>
#include <time.h>


using namespace std;


void NaivePatternMatchingAlgorithm(string text, string pattern){

    vector<int> match_pos;

    clock_t start = clock();
    for(int i = 0; i < text.length() - pattern.length() + 1; i++){

        if(text.substr(i,pattern.length()) == pattern){

            match_pos.emplace_back(i);

        }

    }
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    cout << "Elapsed time: " << elapsed << " seconds." << std::endl;

    if(match_pos.size() > 0){

        cout << "Matches found at Positions: ";

        for(int &i: match_pos){

            cout << i+1 << " ";

        }
        cout << endl;

    }
    else{

        cout << "No match found." << endl;

    }
    
}

int main(){

    string text;
    string pattern;

    cout << "Enter Your Text: ";
    getline(cin,text);
    cout << "Enter Your Pattern: ";
    getline(cin,pattern);


    if(text.length() < pattern.length()){
        cerr << "Error: Length of text should be greater than pattern." << endl;
    }
    else{
        cout << endl;
        NaivePatternMatchingAlgorithm(text,pattern);
        cout << endl;
    }

    return 0;
}