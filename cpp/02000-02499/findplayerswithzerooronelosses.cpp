
// 2225. Find Players With Zero or One Losses
// https://leetcode.com/problems/find-players-with-zero-or-one-losses/




class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        // matches[i] = [winneri, loseri]

        unordered_map<int,pair<int,int>> um;  // player,{wins,losses}

        for(auto& m: matches) {
            auto p = um.insert({m[0],{1,0}});
            if( !p.second )
                ++p.first->second.first;
            p = um.insert({m[1],{0,1}});
            if( !p.second )
                ++p.first->second.second;
        }

        vector<vector<int>> ans(2);
        for(const auto& n : um)
            if( n.second.second == 0 )
                ans[0].push_back(n.first);
            else if( n.second.second == 1 )
                ans[1].push_back(n.first);
        sort(ans[0].begin(),ans[0].end());
        sort(ans[1].begin(),ans[1].end());
        return ans;
    }
};
