#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <time.h>
#include <cmath>
#include <tuple>


using namespace std;


tuple<vector<int>, vector<int>, vector<vector<int>>> SuccinctAlgorithmBitRankVector(vector<bitset<1>> bit_array){

    int length = bit_array.size(); 

    int k = floor(log2(length)/2);
    int l = k*k;

    vector<int> first(int(length/l) + 2,0);
    vector<int> second(int(length/k) + 2,0);

    for(int i = 1; i <= length;i++){

        first[ceil(double(i)/l)] += (bit_array[i] == bitset<1>(0)) ? 0 : 1;
        second[ceil(double(i)/k)] += (bit_array[i] == bitset<1>(0)) ? 0 : 1;

        if(i % k == 0){
            second[int(i/k)] += second[(i/k) - 1];
        }
        if(i % l == 0){
            first[int(i/l)] += first[(i/l) - 1];
            second[int(i/k)] = 0;
        }
    }

    vector<vector<int>> third;
       
    for(int i = 0; i < pow(2,(k-1)); i++){
        vector<int> pthird(k,0);
        for(int j = 0; j < k-1; j++){
            pthird[j+1] = pthird[j] + ((i >> (k - 2 - j)) & 1);
        }
        third.emplace_back(pthird);
    }

    return(make_tuple(first,second,third));

}



int main(){

    vector<bitset<1>> bit_array = {0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,1};

    clock_t start_c = clock();
    tuple<vector<int>, vector<int>, vector<vector<int>>> tup = SuccinctAlgorithmBitRankVector(bit_array);

    int length = bit_array.size(); 
    int k = floor(log2(length)/2);
    int l = k*k;
    
    int id = 31;

    if(id >= length){
        cerr << "Id for bit rank is outofbound for the given vector. " << endl;
        return 1;
    }
    if(id == 0){
        cerr << "Id is 1-index based." << endl;
        return 1;
    }

    int start = (id / k) * k + 1;
    int end = ((id / k) + 1) * k;

    string bit_substring = "";
    for (int i = start; i < end; i++) {
        bit_substring += bit_array[i].to_string();
    }

    

    int row_index = stoi(bit_substring, nullptr, 2);
    int value = get<2>(tup)[row_index][id % k];


    int rank = get<0>(tup)[int(id/l)] + get<1>(tup)[int(id/k)] + value;
    
    clock_t end_c = clock();
    double elapsed = double(end_c - start_c) / CLOCKS_PER_SEC;
    cout << "Elapsed time: " << elapsed << " seconds." << std::endl;


    cout << rank << endl;

    return 0;
}