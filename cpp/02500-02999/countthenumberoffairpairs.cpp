
// 2563. Count the Number of Fair Pairs
// https://leetcode.com/problems/count-the-number-of-fair-pairs/



/*  lower <= nums[i] + nums[j] <= upper
 *  lower - nums[j] <= nums[i] aka nums[i] >= lower - nums[j]
 *                                 nums[i] <= upper - nums[j]
 *  example: lower = 3, upper = 10, nums[j] = 7
 *  nums[i] >=  3 - 7 = -4
 *  nums[i] <= 10 - 7 =  3
 *  hence -4 <= nums[i] <= 3
 *  so the question becomes: in range nums[0,j-1] inclusive,
 *      how many numbers between -4 and 3 inclusive have we seen

 */
class Solution {
private:
    vector<int> bit; // binary indexed tree, 0 indexed
    int n;

    int sum(int r) { // sum of range [0,r] inclusive
        int ret = 0;
        for(; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for(; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

    int _lower_bound(vector<int>& nums, int target) {
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
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        int nums_sz = nums.size();
        if( nums_sz == 1 )
            return 0;

        set<int> st;
        for(int x: nums)
            st.insert(x);

        n = st.size();
        vector<int> v(st.begin(),st.end()); // sorted unique elements in nums
        /*
        for(int i = 0; i < n; ++i)
            cout << i << ":" << v[i] << " ";
        cout << endl;
        */

        bit.assign(n,0);
        int idx = _lower_bound(v,nums[0]); // we know nums[0] exist in v
        add(idx,1);

        long long ans = 0;

        for(int j = 1; j < nums_sz; ++j) {
            // cout << "j " << j << endl;

            int a = lower - nums[j];
            // cout << "nums[i] has to be greater equal " << a << endl;
            int l = _lower_bound(v, a);
            if( l == n )
                continue;

            int b = upper - nums[j];
            // cout << "nums[i] has to be less equal " << b << endl;
            int r = gelttoet(v, b);
            if( r == -1 )
                continue;

            // cout << "l " << l << " r " << r << endl;
            if( l > r )
                continue;

            long long t = sum(l,r);
            // cout << "t " << t << endl;
            ans = ans + t;

            idx = _lower_bound(v,nums[j]); // we know nums[j] exist in v
            add(idx,1);
        }

        return ans;
    }
};
