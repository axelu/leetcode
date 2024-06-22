
// 3187. Peaks in Array
// https://leetcode.com/problems/peaks-in-array/





class Solution {
private:
    vector<int> bit;  // binary indexed tree
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

    bool is_peak(vector<int>& nums, int i) {
        if( i == 0 || i == n-1 )
            return false;
        return nums[i-1] < nums[i] && nums[i] > nums[i+1];
    }

public:
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        n = nums.size(); // 3 <= nums.length <= 1e5

        bit.assign(n, 0);

        for(int i = 1; i < n-1; ++i)
            if( nums[i-1] < nums[i] && nums[i] > nums[i+1] )
                add(i, 1);

        int q_sz = queries.size();
        vector<int> ans;
        for(int i = 0; i < q_sz; ++i) {
            if( queries[i][0] == 1 ) {
                int l = queries[i][1];
                int r = queries[i][2];
                int t = r - l >= 2 ? sum(l+1, r-1) : 0;
                ans.push_back(t);

            } else {
                int j = queries[i][1]; // j -> index into nums
                int val = queries[i][2];

                // we need to assess the impact to j-1, j and j+1
                if( nums[j] == val )    // val unchanged
                    continue;

                bool is_j_peak = is_peak(nums, j);

                if( is_j_peak && val > nums[j] ) {
                    // nums[j] is currently a peak and the new value is even bigger
                    // so it will remain a peak
                    nums[j] = val;
                    continue;
                }

                if( j == 0 ) {
                    // before
                    bool is_r_peak = is_peak(nums, j+1);

                    // update nums
                    nums[j] = val;

                    // after
                    bool is_r_peak_new = is_peak(nums, j+1);
                    if( is_r_peak_new != is_r_peak) {
                        if( is_r_peak_new )
                            add(j+1, 1);
                        else
                            add(j+1, -1);
                    }

                } else if( j == n-1 ) {
                     // before
                    bool is_l_peak = is_peak(nums, j-1);

                    // update nums
                    nums[j] = val;

                    // after
                    bool is_l_peak_new = is_peak(nums, j-1);
                    if( is_l_peak_new != is_l_peak) {
                        if( is_l_peak_new )
                            add(j-1, 1);
                        else
                            add(j-1, -1);
                    }

                } else {
                    // before
                    //   is_j_peak = is_peak(nums, j);
                    bool is_l_peak = is_peak(nums, j-1);
                    bool is_r_peak = is_peak(nums, j+1);

                    // update nums
                    nums[j] = val;

                    // after
                    bool is_j_peak_new = is_peak(nums, j);
                    if( is_j_peak_new != is_j_peak) {
                        if( is_j_peak_new )
                            add(j, 1);
                        else
                            add(j, -1);
                    }

                    bool is_l_peak_new = is_peak(nums, j-1);
                    if( is_l_peak_new != is_l_peak) {
                        if( is_l_peak_new )
                            add(j-1, 1);
                        else
                            add(j-1, -1);
                    }

                    bool is_r_peak_new = is_peak(nums, j+1);
                    if( is_r_peak_new != is_r_peak) {
                        if( is_r_peak_new )
                            add(j+1, 1);
                        else
                            add(j+1, -1);
                    }
                }
            }
        }

        return ans;
    }
};
