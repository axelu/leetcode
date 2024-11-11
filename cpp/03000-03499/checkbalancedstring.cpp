
// 3340. Check Balanced String
// https://leetcode.com/problems/check-balanced-string/



class Solution {
public:
    bool isBalanced(string num) {
        int n = num.size();

        int sum_even = 0;
        int sum_odd = 0;
        for(int i = 0; i < n; ++i)
            if( i % 2 )
                sum_odd += (num[i] - '0');
            else
                sum_even += (num[i] - '0');

        return sum_even == sum_odd;
    }
};
