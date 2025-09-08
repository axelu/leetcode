
// 3674. Minimum Operations to Equalize Array
// https://leetcode.com/problems/minimum-operations-to-equalize-array/



class Solution {
public:
    int minOperations(vector<int>& nums) {
        set<int> st;
        for(int i: nums)
            st.insert(i);

        return st.size() == 1 ? 0 : 1;
    }
};
