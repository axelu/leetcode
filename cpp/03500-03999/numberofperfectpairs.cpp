
// 3649. Number of Perfect Pairs
// https://leetcode.com/problems/number-of-perfect-pairs/




class Solution {
    vector<int> bit;  // binary indexed tree, 0 indexed, point update, range query (sum)
    int n;

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

    // binary search lower bound
    int lower_bound(vector<int>& nums, int target) {
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;

        return s;
    }

    int gelttoet(vector<int>& nums, int target) {
        // binary search greatest element less than target or equal target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid] > target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && nums[s] > target) || s == n )
            --s;

        return s;
    }

public:
    long long perfectPairs(vector<int>& nums) {
        // perfect pair as long as
        // x/2 ... x ... 2*x

        // let us say the pos in nums is value x
        // then we need to answer:
        // how many values are there between [pos+1,n-1]
        // where x/2 <= val <= 2*x

        // range compression
        set<int> uniques;
        for(int x: nums)
            uniques.insert(x);

        n = uniques.size();
        vector<int> v(begin(uniques), end(uniques));

        bit.assign(n,0LL);

        long long ans = 0LL;

        // going right to left in nums
        long long zero_cnt = 0LL;
        int x = nums[nums.size()-1];
        if( x == 0 )
            ++zero_cnt;
        // get index of x
        // it is guaranteed that x in v
        int idx = lower_bound(v, x);
        add(idx, 1);

        for(int i = nums.size()-2; i >= 0; --i) {
            x = nums[i];

            if( x != 0 ) {

                int xp = x, xm = x;
                if( x > 0 ) {
                    xm *= -1;
                } else {
                    xp *= -1;
                }

                int lo_idx = lower_bound(v, ceil(xp / 2.0));
                int hi_idx = gelttoet(v, xp * 2);
                //cout << "xp " << x << " lo_idx " << lo_idx << " hi_idx " << hi_idx << endl;
                if( lo_idx <= hi_idx) {
                    long long cnt = sum(lo_idx, hi_idx);
                    //cout << "cnt " << cnt << endl;
                    ans += (long long)cnt;
                }

                lo_idx = lower_bound(v, xm * 2);
                hi_idx = gelttoet(v, floor(xm / 2.0));
                //cout << "xm " << x << " lo_idx " << lo_idx << " hi_idx " << hi_idx << endl;
                if( lo_idx <= hi_idx) {
                    long long cnt = sum(lo_idx, hi_idx);
                    //cout << "cnt " << cnt << endl;
                    ans += (long long)cnt;
                }

            } else { // x == 0
                ans += zero_cnt;

            }

            // get index of x
            // it is guaranteed that x in v
            if( x == 0 ) {
                ++zero_cnt;
            } else {
                int idx = lower_bound(v, x);
                add(idx, 1);
            }
        }

        return ans;
    }
};
