
// 3202. Find the Maximum Length of Valid Subsequence II
// https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/





class Solution {
private:
    int upper_bound(vector<int> rems[], int n, int rem, int target) {
        // int n = rems[rem].size();

        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= rems[rem][mid] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && rems[rem][s] <= target )
            ++s;

        return s;
    }

    int mem[1000][1000];

    int rec(vector<int>& nums, int pos, vector<int> rems[], int k, int rem) {
        // cout << "rec pos " << pos << " rem " << rem << endl;
        // rem is the remainder we are aiming for

        if( mem[pos][rem] != -1 )
            return mem[pos][rem];

        int cur = nums[pos] % k;
        // where do we continue?
        int rem_new = rem - cur;
        if( rem_new < 0 )
            rem_new += k;
        int rem_new_sz = rems[rem_new].size();
        if( rem_new_sz == 0 )
            return mem[pos][rem] = 1;
        int i = upper_bound(rems, rem_new_sz, rem_new, pos);
        if( i == rem_new_sz )
            return mem[pos][rem] = 1;
        int pos_new = rems[rem_new][i];

        return mem[pos][rem] = 1 + rec(nums, pos_new, rems, k, rem);
    }

public:
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size();

        // we can have remainders 0 to k-1
        vector<int> rems[k]; // nums[i] % k, {indicies}
        for(int i = 0; i < n; ++i) {
            int rem = nums[i] % k;
            rems[rem].push_back(i);
        }

        memset(mem,-1,sizeof mem);

        int ans = 2;
        ans = max(ans, (int)rems[0].size());
        for(int rem = 0; rem < k; ++rem) {

            for(int i = 0; i < n-1; ++i) {
                int l = n - i;
                if( l <= ans )
                    break;
                ans = max(ans, rec(nums, i, rems, k, rem));
            }
        }

        return ans;
    }
};
