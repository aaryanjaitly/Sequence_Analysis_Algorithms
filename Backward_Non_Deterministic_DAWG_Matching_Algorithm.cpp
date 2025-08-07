#include <iostream>
#include <string>
#include <unordered_map>
#include <bitset>
#include <vector>
#include <time.h>

using namespace std;

void BackwardNonDeterministicDAWGMatchingAlgorithm(string text, string pattern){

    reverse(pattern.begin(),pattern.end());

    vector<int> match_pos;
    unordered_map<char,bitset<32>> mask;
    bitset<32> bit = 1;
    
    clock_t start = clock();
    for(auto &c: pattern){
        mask[c] |= bit;
        bit = bit << 1;
    }
    bitset<32> accept_state = bit >> 1; 


    int n = text.length();
    int m = pattern.length();
    int pos = m;

    while(pos <= n){

        int j = 1;
        int last_suffix = 0;
        bitset<32> D = (1 << m) - 1;

        while(D != 0){

            if (pos - j < 0){
                break;
            }

            D &= mask[text[pos - j]];
            if((D & accept_state) != bitset<32>(0)){

                if(j == m){

                    match_pos.emplace_back(pos - m);
                    break;

                }
                else{

                    last_suffix = j;

                }
                
            }
            j += 1;
            D = D << 1;

        }
        pos += m - last_suffix;

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
        BackwardNonDeterministicDAWGMatchingAlgorithm(text,pattern);
        cout << endl;
    }

    return 0;
}