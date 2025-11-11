
// 3678. Smallest Absent Positive Greater Than Average
// https://leetcode.com/problems/smallest-absent-positive-greater-than-average/


class Solution {
public:
    int smallestAbsent(vector<int>& nums) {
        int n = nums.size();

        int sum = 0;
        set<int> st;
        for(int i = 0; i < n; ++i) {
            sum += nums[i];
            st.insert(nums[i]);
        }

        double avg = sum / (n * 1.0);
        int t = floor(avg);
        if( avg < 0.0 ) // problem asks for smallest absent positive
            t = 0;

        auto ub = st.upper_bound(t);
        if( ub == st.end() || *ub > t+1 )
            return t+1;

        int ans = t+2;
        for(auto it = next(ub); it != st.end(); ++it) {
            if( *it > ans )
                break;
            ++ans;
        }

        return ans;
    }
};
