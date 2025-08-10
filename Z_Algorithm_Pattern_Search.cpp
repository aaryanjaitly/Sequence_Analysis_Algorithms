#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <cmath>


using namespace std;


void ZAlgorithmPatternSearch(string text, string pattern){

    string z = pattern + "$"+ text;
    int m = z.length();
    vector<int> z_array(m,0);

    int l = 0;
    int r = 0;
    int k = 0;

    clock_t start = clock();
    for(int i = 1; i < m; i++){
        if(i <= r){
            k = i - l;

            z_array[i] = min((r - i + 1),z_array[k]);
        }

        while(i + z_array[i] < m && z[z_array[i]] == z[i + z_array[i]]){
            z_array[i]++;
        }
        
        if(i + z_array[i] - 1 > r){
            l = i;
            r = i + z_array[i] - 1;
        }

    }

    vector<int> match_pos;
    int n = pattern.length();

    for (int i = n + 1; i < z_array.size(); i++) {
        if (z_array[i] == n){
            match_pos.push_back(i - n - 1); 
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

    ZAlgorithmPatternSearch(text,pattern);




    return 0;
}