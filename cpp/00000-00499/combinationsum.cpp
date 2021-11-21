
// 39. Combination Sum
// https://leetcode.com/problems/combination-sum/

#include <iostream>
#include <cassert>

#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        r.clear();
        sort(candidates.begin(), candidates.end());

        auto l1 = lower_bound(candidates.begin(), candidates.end(), target);
        if( l1 != candidates.end() ) {
            if( *l1 == target ) r.push_back({target});
            if( distance(candidates.begin(), l1) == 0 ) return r;
        }

        for(auto it = candidates.begin(); it != l1; ++it) {
            if( *it * 2 > target ) break;
            vector<int> v;
            v.push_back(*it);
            combinationSum(v, it, l1, target);
        }
        return r;
    }
private:
    vector<vector<int>> r;

    void combinationSum(vector<int> v, vector<int>::iterator itb,
        vector<int>::iterator ite, int target) {
/*
        cout << "v ";
        for(int i : v) cout << i << " ";
        cout << endl;

        cout << "c ";
        for(auto it = itb; it != ite; ++it) {
            cout << *it << " ";
        }
        cout << endl;
*/
        int sum = accumulate(v.begin(), v.end(), 0);
        if( sum == target ) {
            if( find(r.begin(), r.end(), v) == r.end() )
                r.push_back(v);
            return;
        } else if ( sum > target ) {
            return;
        }

        for(auto it = itb; it != ite; ++it) {
            v.push_back(*it);
            combinationSum(v, it, ite, target);
            v.pop_back();
        }
    }
};


int main() {

    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elapsed_seconds;

    Solution s;
    vector<vector<int>> r;
    vector<int> candidates;

    r = {{7},{2,2,3}};
    candidates = {2,3,6,7};
    assert(s.combinationSum(candidates,7) == r);

    r = {{2,2,2,2},{2,3,3},{3,5}};
    candidates = {2,3,5};
    assert(s.combinationSum(candidates,8) == r);

    r = {{1,1,1,1},{1,1,2},{2,2}};
    candidates = {1,2};
    assert(s.combinationSum(candidates,4) == r);

    r = {{2,2,3},{2,5}};
    candidates = {2,3,5};
    assert(s.combinationSum(candidates,7) == r);

    candidates = {4,8,11,10,9,3,12,7,6};

    start = chrono::system_clock::now();

    r = s.combinationSum(candidates,25);

    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << elapsed_seconds.count() << endl;

    int i = 0;
    for(auto v : r) {
        cout << "result vector " << i << endl;
        for (int k : v)
            cout << k << " ";
        cout << endl;
        ++i;
    }


// case 168/168 runs into endless loop

    candidates = {92,71,89,74,102,91,70,119,86,116,114,106,80,81,115,99,117,93,76,77,111,110,75,104,95,112,94,73};

    start = chrono::system_clock::now();

    r = s.combinationSum(candidates,310);

    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << elapsed_seconds.count() << endl;



    return 0;
}
