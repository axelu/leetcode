
// 3073. Maximum Increasing Triplet Value
// https://leetcode.com/problems/maximum-increasing-triplet-value/





class Solution {
private:
    vector<int> bit; // binary indexed tree bit, 0 indexed
    int n;
    const int INF = 1000000000;

    // range query get minimum in range [0,r] inclusive
    int getmin(int r) {
        int ret = INF;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = min(ret, bit[r]);
        return ret;
    }

    void update(int idx, int val) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] = min(bit[idx], val);
    }

public:
    int maximumTripletValue(vector<int>& nums) {
        int nums_sz = nums.size(); // 3 <= nums.length <= 1e5; 1 <= nums[i] <= 1e9
        // it is guaranteed that least one triplet meets the given condition
        if( nums_sz == 3 )
            return nums[0] - nums[1] + nums[2];

        set<int> st; // unique vals in nums
        for(int x: nums)
            st.insert(x);

        n = st.size();
        bit.assign(n, INF);

        unordered_map<int,int> um;
        int idx = 0;
        for(int x: st)
            um[x] = idx++;

        int ans = -INF;

        st.clear();
        for(int i = 0; i < nums_sz; ++i) {
            int r = um[nums[i]];

            // give me the smallest difference between two elements in front of me
            // where the larger element is smaller than me and came after the smaller element
            if( r > 0 ) {
                int min_diff = getmin(r-1);
                ans = max(ans, nums[i] - min_diff);
            }

            // give me the largest value smaller than me seen so far
            auto lb = st.lower_bound(nums[i]);
            if( lb != st.begin() ) {
                int a = *prev(lb);
                int diff = nums[i] - a;

                update(r, diff);
            }

            st.insert(nums[i]);
        }

        return ans;
    }
};
