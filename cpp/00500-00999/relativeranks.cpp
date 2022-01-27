
// 506. Relative Ranks
// https://leetcode.com/problems/relative-ranks/



class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();
        map<int,int> m; // score,index
        for(int i = 0; i < n; ++i)
            m.insert({score[i],i});

        vector<string> ans(n);
        int i = 1;
        for(auto it = m.rbegin(); it != m.rend(); ++it) {
            if( i == 1 )
                ans[it->second] = "Gold Medal";
            else if( i == 2 )
                ans[it->second] = "Silver Medal";
            else if( i == 3 )
                ans[it->second] = "Bronze Medal";
            else
                ans[it->second] = to_string(i);
            ++i;
        }
        return ans;
    }
};
