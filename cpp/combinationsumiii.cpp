
// day 12 September 2020 challenge
// Combination Sum III
// https://leetcode.com/problems/combination-sum-iii/




class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        // k = number of numbers 1 - 9 that add up to n
        if( k < 1 || k > 9 || n > 45 ) return {};

        vector<int> v;
        combinationSum3(v, k, n);

        return r;
    }
private:
    vector<vector<int>> r;

    void combinationSum3(vector<int> v, int k, int n) {
        if( v.size() == k ) {
            int sum = accumulate(v.begin(), v.end(), 0);
            if( sum == n ) r.push_back(v);
            return;
        }

        int s = ( v.empty() ) ? 0 : v.back();
        for(int i = s + 1; i <= 9; ++i) {
            int sum = accumulate(v.begin(), v.end(), 0);
            if( sum + i > n ) break;
            v.push_back(i);
            combinationSum3(v, k, n);
            v.pop_back();
        }
    }
};
