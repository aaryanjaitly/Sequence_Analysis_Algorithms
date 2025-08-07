#include <iostream>
#include <string>
#include <unordered_map>
#include <bitset>
#include <vector>
#include <time.h>

using namespace std;


void ShiftAndPatternMatchingAlgorithm (string text, string pattern){

   vector<int> match_pos;
   unordered_map<char,bitset<32>> mask;
   bitset<32> bit = 1;
    
   clock_t start = clock();
   for(auto &c: pattern){

    mask[c] |= bit;
    bit = bit << 1;

   }
   bitset<32> accept_state = bit >> 1; 
   
   bitset<32> D = 0;
   for(int i = 0; i<text.length();i++){

    D = (((D << 1) | bitset<32>(1)) & mask[text.at(i)]);
    
    if(D == accept_state){

        match_pos.emplace_back(i - pattern.length() + 1);

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
    else if (pattern.length() > 32)
    {
        cerr << "Error: Length of pattern should be less than 64chrs to fit in register." << endl; 
    }
    else{
        cout << endl;
        ShiftAndPatternMatchingAlgorithm(text,pattern);
        cout << endl;
    }
    
    return 0;
}