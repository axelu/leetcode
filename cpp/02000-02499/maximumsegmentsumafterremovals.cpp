
// 2382. Maximum Segment Sum After Removals
// https://leetcode.com/problems/maximum-segment-sum-after-removals/



class Solution {
public:
    vector<long long> maximumSegmentSum(vector<int>& nums, vector<int>& removeQueries) {
        int n = nums.size(); // nums.size() == removeQueries.size()

        vector<long long> ans(n,0LL);

        map<int,pair<int,long long>> mp; // start of segment, {end of segment, segment sum}

        // interval merge
        mp.insert({removeQueries[n-1],{removeQueries[n-1],nums[removeQueries[n-1]]}});
        long long mx = nums[removeQueries[n-1]];

        for(int i = n-2; i >= 0; --i) {
            ans[i] = mx;

            auto ub = mp.upper_bound(removeQueries[i]);

            // if we found an upper bound then either
            //    if( removeQueries[i] + 1 == ub->first ) we are extending that interval
            //    if that interval is not the 1st interval, we need to check the prev interval also
            //        if( removeQueries[i] - 1 == prev(ub)->second.first ) we are extending the prev interval
            //        aka interval merge
            // if we didn't find an interval, then check the last interval and see if we are extending it

            long long seg_sum;
            if( ub != mp.end() ) {
                bool extend_next = removeQueries[i] + 1 == ub->first;
                bool extend_prev = ub != mp.begin() && removeQueries[i] - 1 == prev(ub)->second.first ? true : false;
                if( extend_next && extend_prev ) {
                    seg_sum = prev(ub)->second.second + ub->second.second + nums[removeQueries[i]];
                    prev(ub)->second.first = ub->second.first;
                    prev(ub)->second.second = seg_sum;
                    mp.erase(ub);

                } else if( extend_next ) {
                    seg_sum = ub->second.second + nums[removeQueries[i]];
                    mp.insert({removeQueries[i],{ub->second.first,seg_sum}});
                    mp.erase(ub);

                } else if( extend_prev ) {
                    seg_sum = prev(ub)->second.second + nums[removeQueries[i]];
                    prev(ub)->second.first = removeQueries[i];
                    prev(ub)->second.second = seg_sum;

                } else {
                    seg_sum = nums[removeQueries[i]];
                    mp.insert({removeQueries[i],{removeQueries[i],seg_sum}});
                }

            } else {
                auto last = mp.rbegin();
                if( removeQueries[i] - 1 == last->second.first ) {
                    seg_sum = last->second.second + nums[removeQueries[i]];
                    last->second.first = removeQueries[i];
                    last->second.second = seg_sum;
                } else {
                    seg_sum = nums[removeQueries[i]];
                    mp.insert({removeQueries[i],{removeQueries[i],seg_sum}});
                }
            }
            mx = max(mx, seg_sum);
        }

        return ans;
    }
};
