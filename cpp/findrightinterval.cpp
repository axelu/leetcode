
// day 27 August 2020 challenge
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/552/week-4-august-22nd-august-28th/3438/


class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        if( intervals.empty() ) return {};
        size_t is = intervals.size();
        if( is == 1 ) return {-1};

        // create map: key are begin points, value is index in intervals
        map<int,int> m;
        for(auto i = 0; i < is; ++i)
            m.insert({intervals[i].front(),i});

        vector<int> r;
        r.reserve(is);
        int mb = m.rbegin()->first;
        // iterate through intervals and find equal or next key in map
        // only search if endpoint <= max begin point, else -1
        for(auto vi : intervals) {
            if( vi.back() > mb ) {
                r.push_back(-1);
            } else {
                // it must be there
                r.push_back(m.lower_bound(vi.back())->second);
            }
        }
        return r;
    }
};
