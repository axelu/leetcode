
// 228. Summary Ranges
// https://leetcode.com/problems/summary-ranges/


class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        auto n = nums.size();
        if( n == 0 ) return {};
        if( n == 1 ) return {to_string(nums[0])};

        vector<string> r;
        string s;
        long t;
        auto it1 = begin(nums);
        auto it2 = next(it1);
        for(; it2 != end(nums); ++it2) {
            t = (long)*it2 - (long)*(it2 - 1);
            if( t == 1L ) continue;
            if( it1 == it2 - 1 ) {
                r.push_back(to_string(*it1));
            } else {
                s = to_string(*it1) + "->" + to_string(*(it2-1));
                r.push_back(s);
            }
            it1 = it2;
        }
        // finish up
        if( it1 == it2 - 1 ) {
            r.push_back(to_string(*it1));
        } else {
            s = to_string(*it1) + "->" + to_string(*(it2-1));
            r.push_back(s);
        }

        return r;
    }
};
