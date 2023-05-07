
// 2150. Find All Lonely Numbers in the Array
// https://leetcode.com/problems/find-all-lonely-numbers-in-the-array/




class Solution {
public:
    vector<int> findLonely(vector<int>& nums) {

        map<int,int> mp;
        for(int x: nums)
            ++mp[x];

        vector<int> ans;

        for(auto it = mp.cbegin(); it != mp.cend(); ++it) {
            if( it->second > 1 )
                continue;

            if( it != mp.cbegin() && prev(it)->first == it->first - 1 )
                continue;

            if( next(it) != mp.end() && next(it)->first == it->first + 1 )
                continue;

            ans.push_back(it->first);
        }

        return ans;
    }
};
