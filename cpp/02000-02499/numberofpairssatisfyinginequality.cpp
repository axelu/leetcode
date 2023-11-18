
// 2426. Number of Pairs Satisfying Inequality
// https://leetcode.com/problems/number-of-pairs-satisfying-inequality/





class Solution {
private:
    int bit[40002]; // binary indexed tree bit, 0 indexed
    int n = 40001;

    // point query
    int get(int r) { // sum of range [0,r] inclusive
        int ret = 0;
        for(; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    // range update [idx,n] inclusive
    void add(int idx, int delta) {
        for(; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int diff) {
        int N = nums1.size(); // nums1.size() == nums2.size()

        long long ans = 0LL;

        // equation
        // nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff for 0 <= i < j <= n - 1
        // lets rewrite the equation
        // nums1[i] - nums2[i] <= nums1[j] - nums2[j] + diff

        // worst case
        // i
        // nums1[i] = -10000, nums2[i] =  10000 -> nums1[i] - nums2[i] = -20000
        // nums1[i] =  10000, nums2[i] = -10000 -> nums1[i] - nums2[i] =  20000
        // j
        // nums1[j] = -10000, nums2[j] =  10000, diff = -10000 -> nums1[j] - nums2[j] + diff = -30000
        // nums1[j] =  10000, nums2[j] = -10000, diff =  10000 -> nums1[j] - nums2[j] + diff =  30000

        memset(bit,0,sizeof bit);
        int offset = 20000;
        add(nums1[0]-nums2[0]+offset,1);

        for(int j = 1; j < N; ++j) {
            int t = nums1[j] - nums2[j] + diff + offset;
            if( t > 40000 ) {
                ans += j;
            } else if( t >= 0 ) {
                ans += get(t);
            }

            add(nums1[j]-nums2[j]+offset,1);
        }

        return ans;
    }
};
