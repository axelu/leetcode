
// day 3 October 2020 challenge
// 532. K-diff Pairs in an Array
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/559/week-1-october-1st-october-7th/3482/
// https://leetcode.com/problems/k-diff-pairs-in-an-array/




#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <iterator>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <map>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
private:
    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> tend;
    chrono::duration<double> elapsed_seconds;
public:
    int findPairs(vector<int>& nums, int k) {
        auto n = nums.size();
        if( n == 1 ) return 0;

        auto itb = begin(nums);
        auto ite = end(nums);

        int r = 0;

        if( k == 0 ) {
            // count unique duplicates using map
            /*
            unordered_map<int,int> m;
            for(auto it = itb; it != ite; ++it) {
                auto p = m.insert({*it,1});
                if( !p.second ) {
                    ++p.first->second;
                    if( p.first->second == 2 ) ++r;
                }
            }
            */

            int max = *max_element(itb,ite);
            int min = *min_element(itb,ite);
            int range = max - min + 1;

            vector<int> count(range);
            for (int i = 0; i < n; i++) {
                count[nums[i] - min]++;
                if( count[nums[i] - min] == 2 ) ++r;
            }

        } else {

            start = chrono::system_clock::now();
            // sort(itb, ite); // slow on large numer of elements

            // counting sort
            int max = *max_element(itb,ite);
            int min = *min_element(itb,ite);
            int range = max - min + 1;

            vector<int> count(range);
            vector<int> output(n);
            for (int i = 0; i < n; i++)
                count[nums[i] - min]++;

            for (int i = 1; i < range; i++)
                count[i] += count[i - 1];

            for (int i = n - 1; i >= 0; i--) {
                output[count[nums[i] - min] - 1] = nums[i];
                count[nums[i] - min]--;
            }

            tend = chrono::system_clock::now();
            elapsed_seconds = tend - start;
            cout << "sort elapsed_seconds " << elapsed_seconds.count() << endl;

            itb = begin(output);
            ite = end(output);

            // 'remove' duplicates, unique 'removes' adjancent duplicates, hence sort before
            start = chrono::system_clock::now();
            ite = unique(itb,ite);

            tend = chrono::system_clock::now();
            elapsed_seconds = tend - start;
            cout << "unique elapsed_seconds " << elapsed_seconds.count() << endl;

            start = chrono::system_clock::now();
            // sliding window
            auto iti = itb;
            for(auto ito = itb + 1; ito != ite; ++ito) {
                int d = *ito - *iti;
                if( d < k ) {
                    continue;
                } else if ( d == k ) {
                    ++r;
                    continue;
                }
                while( d > k ) {
                    ++iti;
                    if( iti == ito ) break;
                    d = *ito - *iti;
                    if( d == k ) ++r;
                }
            }
            tend = chrono::system_clock::now();
            elapsed_seconds = tend - start;
            cout << "count elapsed_seconds " << elapsed_seconds.count() << endl;

        }

        return r;
    }
};
/*
int main() {

    // chrono::time_point<chrono::system_clock> start;
    // chrono::time_point<chrono::system_clock> end;
    // chrono::duration<double> elapsed_seconds;

    // start = chrono::system_clock::now();
    // do something
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    Solution s;
    vector<int> nums;
    int k;
    int r;

    nums = {3,1,4,1,5};
    cout << "{3,1,4,1,5}" << endl;
    k = 2;
    r = s.findPairs(nums,k);
    cout << "result " << r << endl;
    assert(r == 2);

    nums = {1,2,3,4,5};
    cout << "{1,2,3,4,5}" << endl;
    k = 1;
    r = s.findPairs(nums,k);
    cout << "result " << r << endl;
    assert(r == 4);

    nums = {1,3,1,5,4};
    cout << "{1,3,1,5,4}" << endl;
    k = 0;
    r = s.findPairs(nums,k);
    cout << "result " << r << endl;
    assert(r == 1);

    nums = {1,2,4,4,3,3,0,9,2,3};
    cout << "{1,2,4,4,3,3,0,9,2,3}" << endl;
    k = 3;
    r = s.findPairs(nums,k);
    cout << "result " << r << endl;
    assert(r == 2);

    nums = {-1,-2,-3};
    cout << "{-1,-2,-3}" << endl;
    k = 1;
    r = s.findPairs(nums,k);
    cout << "result " << r << endl;
    assert(r == 2);

    nums = {3,4,4,6,8,8,4,8};
    cout << "{3,4,4,6,8,8,4,8}" << endl;
    k = 0;
    r = s.findPairs(nums,k);
    cout << "result " << r << endl;
    assert(r == 2);


    // generate vector with 10e7 elements betweem -10e7 and 10e7, dupliactes are ok
    nums = {};
    srand(time(nullptr)); // use current time as seed for random generator
    for(int i = 0; i < 10000000; ++i) {

        int rdm = rand() % 20000001 - 10000000; // random in the range -10e7 and 10e7
        nums.push_back(rdm);
    }

    cout << "random 10e7 ints, k = 0" << endl;
    r = s.findPairs(nums,0);
    cout << "result " << r << endl;

    // generate random k in the range 0 and 10e7
    k = rand() % 10000001;
    cout << "random 10e7 ints, random k" << endl;
    cout << "k " << k << endl;
    r = s.findPairs(nums,k);
    cout << "result " << r << endl;
    // assert(r == 2);

    return 0;
}*/
