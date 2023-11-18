
// 2763. Sum of Imbalance Numbers of All Subarrays
// https://leetcode.com/problems/sum-of-imbalance-numbers-of-all-subarrays/





class Solution {
public:
    int sumImbalanceNumbers(vector<int>& nums) {
        int n = nums.size();

        // nbr of subarrays
        // worst case n = 1000 -> 500500 subarrays
        // int a = n * (n+1)/2;

        int ans = 0;

        for(int i = 0; i < n-1; ++i) {
            set<int> st;
            int t = 0; // imbalance
            for(int j = i; j < n; ++j) {
                auto p = st.insert(nums[j]);
                if( i == j )
                    continue;
                if( p.second ) {
                    bool adjacent_to_prev = false;
                    if( p.first != st.begin() && *prev(p.first) == *p.first - 1 )
                        adjacent_to_prev = true;
                    bool adjacent_to_next = false;
                    if( next(p.first) != st.end() && *next(p.first) == *p.first + 1 )
                        adjacent_to_next = true;

                    if( adjacent_to_prev && adjacent_to_next )
                        --t;
                    else if( !adjacent_to_prev && !adjacent_to_next )
                        ++t;
                }
                ans += t;
            }
        }

        return ans;
    }
};
