
// Combination Sum II
// https://leetcode.com/problems/combination-sum-ii/




class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        if( candidates.empty() ) return {{}};

        sort(candidates.begin(), candidates.end());
        vector<int> v;
        combinationSum2(v, candidates.begin(), candidates.end(), target);

        return r;
    }
private:
    vector<vector<int>> r;

    void combinationSum2(vector<int> v, vector<int>::iterator itb,
        vector<int>::iterator ite, int target) {

        if( !v.empty() ) {
            int sum = accumulate(v.begin(), v.end(), 0);
            if( sum == target ) {
                if( find(r.begin(), r.end(), v) == r.end() )
                    r.push_back(v);
                return;
            } else if ( sum > target ) {
                return;
            }
        }

        for(auto it = itb; it != ite; ++it) {
            v.push_back(*it);
            combinationSum2(v, it + 1, ite, target);
            v.pop_back();
        }
    }
};
