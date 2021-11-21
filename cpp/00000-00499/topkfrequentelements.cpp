
// 347. Top K Frequent Elements
// https://leetcode.com/problems/top-k-frequent-elements/


class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> um; // key,frequency
        size_t n = nums.size();
        pair<unordered_map<int,int>::iterator,bool> p;
        for(int i = 0; i < n; ++i) {
            p = um.insert({nums[i],1});
            if( !p.second ) ++p.first->second;
        }
        auto cmp = [](const int& a, const int& b){return a > b;};
        multimap<int,int,decltype(cmp)> mm(cmp); // frequency,key sorted non-increasing frequency
        for(auto it = begin(um); it != end(um); ++it)
            mm.insert({it->second,it->first});

        vector<int> ans(k);
        auto it = begin(mm);
        for(int i = 0; i < k; ++i) {
            ans[i] = it->second;
            ++it;
        }

        return ans;
    }
};
