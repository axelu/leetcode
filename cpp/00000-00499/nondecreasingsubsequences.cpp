
// 491. Non-decreasing Subsequences
// https://leetcode.com/problems/non-decreasing-subsequences/




class Solution {
private:
    vector<vector<int>> ans;
    int * _nums;
    int n;
    set<vector<int>> s;

    void genSubsequences(int i, vector<int>& ss) {

        if( i == n ) {
            if( ss.size() > 1 && s.insert(ss).second )
                ans.push_back(ss);
            return;

        } else {
            // we have a choice

            // don't include int at current index
            genSubsequences(i+1,ss);

            // include char at current index
            if( ss.empty() || ss.back() <= _nums[i] ) {
                ss.push_back(_nums[i]);
                genSubsequences(i+1,ss);
                ss.pop_back(); // backtrack
            }
        }
        return;
    }

public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        n = nums.size();
        _nums = nums.data();

        vector<int> ss;
        genSubsequences(0,ss);

        return ans;
    }
};
