
// 2938. Separate Black and White Balls
// https://leetcode.com/problems/separate-black-and-white-balls/



class Solution {
public:
    long long minimumSteps(string s) {
        int n = s.size(); // 1 black ball, 0 white ball

        long long ans = 0LL;
        long long zeros = 0LL;

        // every one needs to be swapped with every 0 to its right
        for(int i = n-1; i >= 0; --i)
            if( s[i] == '0' )
                ++zeros;
            else
                ans += zeros;

        return ans;
    }
};
