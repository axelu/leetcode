
// 3020. Find the Maximum Number of Elements in Subset
// https://leetcode.com/problems/find-the-maximum-number-of-elements-in-subset/





class Solution {
private:

    int rec(map<int,int>& cnt, long x, unordered_set<int>& seen) {

        auto f = cnt.find(x);
        if( f == cnt.end() || f->second < 2 )
            return 0;

        seen.insert(x);

        int ret = 2;

        /*
        long i = 2;
        for(; i*i <= x; ++i)
            if( i*i == x )
                ret += rec(cnt, i, seen);
        */

        long i = sqrt(x);
        if( i * i == x )
            ret += rec(cnt, i, seen);

        return ret;
    }



public:
    int maximumLength(vector<int>& nums) {
        int n = nums.size();
        if( n == 2 )
            return 1;

        // special consideration must be given to elements of value 1
        // e.g. {1,1,1,1,1} -> ans = 5

        map<int,int> cnt; // value, count
        for(int i: nums)
            ++cnt[i];

        int ans = 1;

        unordered_set<int> seen;
        for(auto it = cnt.rbegin(); it != cnt.rend(); ++it) {
            if( it->first == 1 ) {
                int ones = it->second % 2 ? it->second : it->second - 1;
                ans = max(ans, ones);
                break;
            }

            long x = it->first;
            if( seen.find(x) != seen.end() )
                continue;

            // lets assume the current element is our peak
            /*
            long i = 2;
            for(; i*i <= x; ++i)
                if( i*i == x ) {
                    ans = max(ans, 1 + rec(cnt, i, seen));
                    break;
                }
            */
            long i = sqrt(x);
            if( i * i == x )
                ans = max(ans, 1 + rec(cnt, i, seen));
        }

        return ans;
    }
};
