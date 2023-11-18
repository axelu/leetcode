
// 1755. Closest Subsequence Sum
// https://leetcode.com/problems/closest-subsequence-sum/





class Solution {
private:
    void subset_sums1(vector<int>& nums, int n, int sum, int pos, vector<int>& st) {
        if( pos == n ) {
            st.push_back(sum);
            return;
        }

        // we have a choice
        //   do not pick the current element OR
        //   pick the current element
        subset_sums1(nums, n, sum, pos + 1, st);
        subset_sums1(nums, n, sum + nums[pos], pos + 1, st);
        return;
    }

    int goal;

    // binary search
    int search(vector<int>& nums, int target) {
        int n = nums.size();
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

    int ans;

    void subset_sums2(vector<int>& nums, int n, int sum, int pos, vector<int>& st) {
        // cout << "subset_sums2 n " << n << " pos " << pos << " sum " << sum << endl;
        if( pos == n ) {

            int i = search(st, goal - sum);
            int st_sz = st.size();
            if( i == st_sz ) {
                ans = min(ans, abs(st[st_sz-1] + sum - goal));
            } else if( i == 0 ) {
                ans = min(ans, abs(st[0] + sum - goal));
            } else {
                ans = min(ans, abs(st[i] + sum - goal));
                ans = min(ans, abs(st[i-1] + sum - goal));
            }
            return;
        }

        // we have a choice
        //   do not pick the current element OR
        //   pick the current element
        subset_sums2(nums, n, sum, pos + 1, st);
        subset_sums2(nums, n, sum + nums[pos], pos + 1, st);
        return;
    }

public:
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        if( n == 1 )
            return min(abs(nums[0]-goal), abs(goal));

        this->goal = goal;

        // calculate all subset sums for the 1st half and sort them
        int n2 = n / 2;
        vector<int> st;
        subset_sums1(nums,n2,0,0,st);
        sort(st.begin(),st.end());

        ans = INT_MAX;
        subset_sums2(nums,n,0,n2,st);

        return ans;
    }
};
