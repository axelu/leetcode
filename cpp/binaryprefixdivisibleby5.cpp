
// 1018. Binary Prefix Divisible by 5
// https://leetcode.com/problems/binary-prefix-divisible-by-5/


class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& A) {
        size_t n = A.size();
        vector<bool> ans(n);

        int a = A[0];
        ans[0] = a % 5 == 0 ? true : false;
        for(int i = 1; i < n; ++i) {
            a <<= 1;
            a |= A[i];
            a %= 5;
            ans[i] = a == 0 ? true : false;
        }

        return ans;
    }
};
