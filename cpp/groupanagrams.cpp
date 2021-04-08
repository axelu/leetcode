
// 47. Group Anagrams
// https://leetcode.com/problems/group-anagrams/



class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        size_t n = strs.size();
        vector<vector<string>> ans;
        if( n == 1 ) {
            ans.push_back({strs[0]});
            return ans;
        }

        map<array<int,26>,vector<string>> m;
        for(int i = 0; i < n; ++i) {
            array<int,26> chs{0};
            for(int j = 0; j < strs[i].size(); ++j)
                ++chs[strs[i][j]-'a'];
            auto p = m.insert({chs,{strs[i]}});
            if( !p.second )
                p.first->second.push_back(strs[i]);
        }

        for(auto it = begin(m); it != end(m); ++it)
            ans.push_back(it->second);

        return ans;
    }
};
