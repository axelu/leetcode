
// 2418. Sort the People
// https://leetcode.com/problems/sort-the-people/

class Solution {
public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        int n = names.size(); // names.size() == heights.size()
        map<int,string> m;

        for(int i = 0; i < n; ++i)
            m.insert({heights[i],names[i]});

        vector<string> ans(n);
        int idx = 0;
        for(auto it = m.rbegin(); it != m.rend(); ++it)
            ans[idx++] = it->second;

        return ans;
    }
};
