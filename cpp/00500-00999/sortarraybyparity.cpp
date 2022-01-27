#include <iostream>
#include <vector>
#include <algorithm>

// day 21 August 2020 challenge
// 905. Sort Array by Parity
// https://leetcode.com/problems/sort-array-by-parity

using namespace std;

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        // generates heap-buffer overflow runtime error respectively segmentation fault
        // sort(A.begin(),A.end(),[](int a, int b){return a % 2 == 0;});

        sort(A.begin(),A.end(),[](int a, int b){return a % 2 == 0 && b % 2 != 0;});
        return A;
    }
};

void print(vector<int>& v) {
    for(auto i : v) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    Solution s;

    vector<int> v;

    v = {3,1,2,4};
    vector<int> r = s.sortArrayByParity(v);
    print(r);

    v = {3363,4833,290,3381,4227,1711,1253,2984,2212,874,2358,2049,2846,2543,1557,1786,4189,1254,2803,62,3708,1679,228,1404,1200,4766,1761,1439,1796,4735,3169,3106,3578,1940,2072,3254,7,961,1672,1197,3187,1893,4377,2841,2072,2011,3509,2091,3311,233};
    r = s.sortArrayByParity(v);
    print(r);


    

    return 0;
}
