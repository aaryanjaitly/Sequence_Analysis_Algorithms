#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <time.h>
#include <set>
#include <map>


using namespace std;


map<char,int> Shift_Table(set<char> sigma,string pattern){

    map<char,int> shifts;
    int m = pattern.length();

    for(auto &c: sigma){

        shifts[c] = m;

    }

    for(int i = 0; i < m-1;i++){

        shifts[pattern.at(i)] = m - i - 1;

    }

    return shifts;
}




void HoorspoolPatternSearchAlgorithm(set<char> sigma,string text,string pattern){

    vector<int> match_pos;
    int i = pattern.length() - 1; 

    clock_t start = clock();
    map<char,int> shifts = Shift_Table(sigma,pattern); 

    while (i < text.length()){ 

        int j = i - pattern.length() + 1;
        string window = text.substr(j,pattern.length());

        if(window == pattern){
        match_pos.push_back(j);
        }
        i += shifts[text[i]];

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

    set<char> sigma;
    string text;
    string pattern;

    cout << "Enter Your Alphabets (Space Seprated): ";
    string sigma_Alphabets;
    getline(cin,sigma_Alphabets);

    for(auto &c: sigma_Alphabets){

        if(c != ' '){
            sigma.insert(c);
        }

    }
    
    cout << "Enter Your Text: ";
    getline(cin,text);
    cout << "Enter Your Pattern: ";
    getline(cin,pattern);

    if(text.length() < pattern.length()){

        cerr << "Error: Length of text should be greater than pattern." << endl;

    }
    else{

        cout << endl;
        HoorspoolPatternSearchAlgorithm(sigma,text,pattern);
        cout << endl;
        
    }

    return 0;
}