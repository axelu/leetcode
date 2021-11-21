
// 164. Maximum Gap
// https://leetcode.com/problems/maximum-gap/
// day 30 May 2021 challenge
// https://leetcode.com/explore/featured/card/may-leetcoding-challenge-2021/602/week-5-may-29th-may-31st/3761/



class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 ) return 0;
        if( n == 2 ) return abs(nums[0]-nums[1]);

        // pigeonhole principle

        int i;
        int mn = nums[0];
        int mx = nums[0];

        // get min and max
        for(i = 1; i < n; ++i) {
            mn = min(mn,nums[i]);
            mx = max(mx,nums[i]);
        }

        // divide into n-1 buckets of equal size
        double bkSz = (double)(mx-mn)/(n-1);
        // cout << bkSz << endl;
        // keep track of min and max in each bucket
        int mnBk[n-1];
        int mxBk[n-1];
        for(i = 0; i < n-1; ++i) {
            mnBk[i] = 1000000001;
            mxBk[i] = -1;
        }

        // put all values into the buckets except our mn and mx
        int bkIdx;
        for(i = 0; i < n; ++i) {
            // skip mn and mx
            if( nums[i] == mn || nums[i] == mx )
                continue;
            // which bucket?
            bkIdx = (int)floor((nums[i]-mn)/bkSz);

            mnBk[bkIdx] = min(mnBk[bkIdx],nums[i]);
            mxBk[bkIdx] = max(mxBk[bkIdx],nums[i]);
        }

        /*
        for(i = 0; i < n-1; ++i) {
            cout << i << " " << mnBk[i] << " " << mxBk[i] << endl;
        }
        */

        // get the largest gap
        // largest gap is max of mnBk[i]-mxBk[j]
        // where j > i are indexes between consequitive non-empty buckets
        // an empty bucket is mnBk[i] = 1000000001 and mxBk[i] = -1
        int ans = 0;
        int lastMx = mn; // init lastMx to mn, this is where our 1st bucket starts
        for(i = 0; i < n-1; ++i) {
            // skip empty bucket
            if( mxBk[i] == -1 ) continue;

		    ans = max(ans,mnBk[i]-lastMx);
		    lastMx = mxBk[i];
        }
        ans = max(ans,mx-lastMx); // end as mx is the max of our last bucket
        return ans;
    }
};
