
// 1207. Unique Number of Occurrences
// https://leetcode.com/problems/unique-number-of-occurrences/


class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        int cnt[2001];
        for(int i = 0; i < 2001; ++i) cnt[i] = 0;

        for(auto it = begin(arr); it != end(arr); ++it)
            ++cnt[*it+1000];

        unordered_set<int> us;
        for(int i = 0; i < 2001; ++i)
            if( cnt[i] != 0 && !us.insert(cnt[i]).second ) return false;
        return true;
    }
};
