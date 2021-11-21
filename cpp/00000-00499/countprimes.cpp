#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <cmath>

using namespace std;

// 204. Count Primes
// https://leetcode.com/problems/count-primes/

class Solution {
public:
    int countPrimes(int n) {
        if( n <= 2 ) return 0;

        vector<bool> v(n-2);
        fill(v.begin(), v.end(), true);

        n = n - 1; // adjusting for 0 index and 
                   // to count only primes less than n

        int c = 0;
        // int r = sqrt(n);
        auto itb = v.begin();
        auto ite = v.end();
        auto itoe = itb + sqrt(n) - 2;
        // for(int i = 2; i <= r; ++i) {
        for(auto it = itb; it <= itoe; ++it) {
            cout << "i = " << it - v.begin() + 2 << endl;
            if( *it ) {

                // int i2 = i * i;
                int i = (it - itb + 2);
                int i2 = i * i;
                // for(int j = i2; j <= n; j += i) {
                for(auto iti = itb + i2 - 2; iti <= ite - 1; iti = iti + i) {

                    // cout << "j " << j << endl;
                    cout << "j " << iti - v.begin() + 2 << endl;
                    if( *iti ) {
                        ++c;
                        *iti = false;
                    }
                }
            }
        }

        return n - 1 - c;
        // return count(v.begin(),v.end(),true);
    }
};

int main() {
    Solution s;

    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsed_seconds;
   
    vector<int> is = {5};
    // vector<int> is = {10};
    // vector<int> is = {30};
    // vector<int> is = {10,30,1000};
    // vector<int> is = {10,30,1000,10000,2147483647};
    // vector<int> is = {10,30,1000,10000};
    // 4, 10, 168, 1229, 105097565

    for(int i : is) {

        cout << i << endl;
        start = chrono::system_clock::now();
        // assert(s.countPrimes(1000) == 168);
        cout << s.countPrimes(i) << endl;
        end = chrono::system_clock::now();
        elapsed_seconds = end - start;
        cout << elapsed_seconds.count() << endl;
    }




    return 0;
}
