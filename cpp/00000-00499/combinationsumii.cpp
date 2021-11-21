
// 40. Combination Sum II
// https://leetcode.com/problems/combination-sum-ii/

class Solution {
private:
    
    void genSubsequences(map<int,int>& mp, 
                         map<int,int>::iterator it, 
                         vector<int>& subseq, 
                         int sum, 
                         int target,
                         vector<vector<int>>& ans) {
        
        if( it == mp.end() ) {
            if( sum == target )
                ans.push_back(subseq);
        
        } else {
            // we have a choice
            // don't include int at current index
            genSubsequences(mp,next(it),subseq,sum,target,ans);

            
            // include int at current index
            int sum_new = sum;
            int i = 0;
            for(; i < it->second; ++i) {
                sum_new += it->first;
                if( sum_new > target )
                    break;
                subseq.push_back(it->first);
                genSubsequences(mp,next(it),subseq,sum_new,target,ans);
            }
            // backtrack
            for(; i > 0; --i)
                subseq.pop_back();
        }
        return;
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        int n = candidates.size();
        
        if( n == 1 ) {
            if( candidates[0] != target )
                return ans;
            else {
                ans.push_back(candidates);
                return ans;
            }
        }
        
        int sum = 0;
        map<int,int> mp; // candidate,count to group duplicantes
        for(int i = 0; i < n; ++i) {
            if( candidates[i] > target )
                continue;
            sum += candidates[i];
            ++mp[candidates[i]];
        }

        if( sum < target )
            return ans;
        
        vector<int> subseq;
        
        if( sum == target ) {
            for(auto it = mp.begin(); it != mp.end(); ++it)
                for(int i = 0; i < it->second; ++i)
                    subseq.push_back(it->first);
            ans.push_back(subseq);  
            return ans;
        }
        
        
        
        genSubsequences(mp,mp.begin(),subseq,0,target,ans);
        return ans;
    }
};
