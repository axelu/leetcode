
// Count Smaller after self
// https://leetcode.com/problems/count-of-smaller-numbers-after-self/
// passed when originally submitted
// but when it became part of June 2021 challenged, it got TLE
// see countsmallerafterself2.cpp for solution that passed



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
#include <cmath>
#include <bitset>
#include <cstring>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    vector<int> countSmaller1(vector<int>& nums) {
        auto n = nums.size();
        if( n == 0 ) return {};
        if( n == 1 ) return {0};

        int ht[20001]; memset(ht,0,sizeof ht);

        vector<int> r(n,0);
        int c = nums[n-1];
        int idx = c + 10000;
        ++ht[idx];
        int count;
        int mn = 10001;
        for(int i = n - 2; i >= 0; --i) {
            int c = nums[i];
            mn = min(mn,c);
            int idx = c + 10000;
            ++ht[idx];
            count = 0;
            if(mn < c) {
            for(int j = 0; j < idx; ++j) {
                count += ht[j];
            }
            }
            r[i] = count;
        }

        return r;
    }

    int insert(const int& c, int b, int e, vector<int>& desc) {
        // cout << "binary search " << c << " " << b << " " << e << endl;
        // crossing and equal begin and end
        if( b == e || b > e || e < b ) {
            auto it = begin(desc);
            if( c > desc[b] ) {
                it += b;
            } else if( c < desc[b] ) {
                it += b + 1;
            } else {
                // c == desc[b]
                it += b + 1;
                while( it != end(desc) && *it == c ) ++it;
            }
            it = desc.insert(it,c);
            return desc.size() - distance(begin(desc),it) - 1;
        }

        int s = b + ((e - b)/2);
        // cout << "s " << s << endl;

        int r;
        if( c > desc[s] ) {
            r = insert(c, b, s-1, desc);
        } else if( c < desc[s] ) {
            r = insert(c, s+1, e, desc);
        } else {
            // desc[s] == s
            auto it = begin(desc) + s + 1;
            while( it != end(desc) && *it == c ) ++it;
            it = desc.insert(it,c);
            r = desc.size() - distance(begin(desc),it) - 1;
        }
        return r;
    }

    int insert(int c, vector<int>& desc) {
        // cout << c << endl;
        // for(auto i : desc) cout << i << " ";
        // cout << endl;
        int r;
        if( c > desc.front() ) {
            desc.insert(begin(desc),c);
            r = desc.size() - 1;
        } else if( c <= desc.back() ) {
            desc.push_back(c);
            r = 0;
        } else if( c == desc.front() ) {
            auto it = begin(desc) + 1;
            while( it != end(desc) && *it == c ) ++it;
            it = desc.insert(it,c);
            r = desc.size() - distance(begin(desc),it) - 1;
        } else {
            // binary search
            r = insert(c,0,desc.size()-1,desc);
        }
        // cout << "after insert " << c << " " << r << endl;
        // for(auto i : desc) cout << i << " ";
        // cout << endl;

        return r;
    }


    vector<int> countSmaller(vector<int>& nums) {
        auto n = nums.size();
        if( n == 0 ) return {};
        if( n == 1 ) return {0};

        vector<int> desc;
        desc.reserve(n);
        desc.push_back(nums[n-1]);
        // for(auto i : desc) cout << i << " ";
        // cout << endl;

        vector<int> r(n,0);
        for(int i = n - 2; i >= 0; --i)
            r[i] = insert(nums[i],desc);

        return r;
    }
};

int main() {

    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end;
    chrono::duration<double> elapsed_seconds;

    // start = chrono::system_clock::now();
    // do something
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    Solution s;
    vector<int> nums;
    vector<int> r;
    vector<int> expected;

    // 0 <= nums.length <= 10^5
    // -10^4 <= nums[i] <= 10^4

    // Example 1
    nums = {5,2,6,1};
    r = s.countSmaller(nums);
    for(auto i : r) cout << i << " ";
    cout << endl;
    expected = {2,1,1,0};
    assert(expected == r);

    // case 15/16 initially wrong answer
    nums = {26,78,27,100,33,67,90,23,66,5,38,7,35,23,52,22,83,51,98,69,81,32,78,28,94,13,2,97,3,76,99,51,9,21,84,66,65,36,100,41};
    r = s.countSmaller(nums);
    for(auto i : r) cout << i << " ";
    cout << endl;
    expected = {10,27,10,35,12,22,28,8,19,2,12,2,9,6,12,5,17,9,19,12,14,6,12,5,12,3,0,10,0,7,8,4,0,0,4,3,2,0,1,0};
    assert(expected == r);

    srand(time(nullptr));
    int rdm;
    for(int i = 0; i < 10e5; ++i) {
        rdm = (rand() % 20001) - 10000;
        nums.push_back(rdm);
    }

    start = chrono::system_clock::now();
    r = s.countSmaller(nums);
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    return 0;
}
