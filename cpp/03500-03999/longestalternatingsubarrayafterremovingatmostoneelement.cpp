
// 3830. Longest Alternating Subarray After Removing At Most One Element
// https://leetcode.com/problems/longest-alternating-subarray-after-removing-at-most-one-element/




class Solution {

public:
    int longestAlternating(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 1;
        if( n == 2 )
            return nums[0] != nums[1] ? 2 : 1;

        // an index has incoming and outgoing connection
        // connections have 3 possible direcitons:
        // 0 h horizontal
        // 1 u up
        // 2 d down
        // indices can be a start, an end, both or nothing
        // indices can be peaks or valeys or neither
        // index 0 and n-1 are special, no incoming respectively no outgoing

        enum direction {horizontal, up, down};

        int ans = 1;

        vector<vector<int>> intervals;
        int s = 0;
        int inc, out;
        for(int i = 1; i < n-1; ++i) {
            int pre = nums[i-1];
            int x   = nums[i];
            int nxt = nums[i+1];

            // incoming
            if( pre < x )
                inc = up;
            else if( pre > x )
                inc = down;
            else
                inc = horizontal;

            // outgoing
            if( nxt > x )
                out = up;
            else if( nxt < x )
                out = down;
            else
                out = horizontal;

            // cout << i << " inc " << inc << " out " << out << endl;

            if( out == horizontal ) {
                if( inc == up || inc == down ) {
                    // i is an end
                    int l = i - s + 1;
                    if( l > 1 ) {
                        intervals.push_back({s, i});
                        ans = max(ans, l);
                    }
                }
                s = i + 1;
            } else if (out == up ) {
                if( inc == horizontal ) {
                    s = i;
                } else if( inc == up ) {
                    // start and end
                    int l = i - s + 1;
                    if( l > 1 ) {
                        intervals.push_back({s, i});
                        ans = max(ans, l);
                    }
                    s = i;
                } else { // down
                    // no op
                }
            } else { // out == down
                if( inc == horizontal ) {
                    s = i;
                } else if( inc == up ) {
                    // no op
                } else { // inc == down
                    // start and end
                    int l = i - s + 1;
                    if( l > 1 ) {
                        intervals.push_back({s, i});
                        ans = max(ans, l);
                    }
                    s = i;
                }
            }
            // cout << i << " inc " << inc << " out " << out << " s " << s << endl;
        }
        // finish up at n-1
        if( nums[n-2] < nums[n-1] )
            inc = up;
        else if( nums[n-2] > nums[n-1] )
            inc = down;
        else
            inc = horizontal;
        if( inc == up || inc == down ) {
            // n-1 is an end
            if( s == 0 )
                return n;
            int l = (n-1) - s + 1;
            if( l > 1 ) {
                intervals.push_back({s, n-1});
                ans = max(ans, l);
            }
        }

        // intervals were ..e   == s.. could be united
        // intervals were ..e+1 == s.. could be inited if continuing in different directions
        for(int i = 1; i < intervals.size(); ++i) {
            int e = intervals[i-1][1];
            int s = intervals[i][0];
            if( e == s ) {
                int l_lft = e - intervals[i-1][0] + 1;
                int l_rgt = intervals[i][1] - s + 1;
                int l = l_lft + l_rgt - 2;
                ans = max(ans, l);

            } else if( e + 1 == s ) {
                // get incoming for s
                int pre = nums[e-1];
                int x = nums[e];
                if( pre < x )
                    inc = up;
                else if( pre > x )
                    inc = down;
                else
                    inc = horizontal; // will never happen
                // get outgoing for s
                x = nums[s];
                int nxt = nums[s+1];
                if( nxt > x )
                    out = up;
                else if( nxt < x )
                    out = down;
                else
                    out = horizontal; // will never happen

                if( inc != out ) {
                    int l_lft = e - intervals[i-1][0] + 1;
                    int l_rgt = intervals[i][1] - s + 1;
                    int l = l_lft + l_rgt - 1;
                    ans = max(ans, l);
                }
            }
        }

        return ans;
    }
};
