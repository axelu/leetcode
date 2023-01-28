
// 2544. Alternating Digit Sum
// https://leetcode.com/problems/alternating-digit-sum/



class Solution {
public:
    int alternateDigitSum(int n) {

        stack<int> stck;
        while( n > 0 ) {
            stck.push(n % 10);
            n /= 10;
        }

        int ans = 0;
        int f = 1;

        while( !stck.empty() ) {
            ans += f * stck.top();
            stck.pop();
            f = f == 1 ? -1 : 1;
        }

        return ans;
    }
};
