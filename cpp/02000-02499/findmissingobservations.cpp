
// 2028. Find Missing Observations
// https://leetcode.com/problems/find-missing-observations





class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int m = rolls.size();

        // (sum(rolls)+x) / (m+n) = mean
        // x = (mean * (m+n))-sum(rolls)
        // once we have x we need to be able to fill x = sum(x0+x1...+xn-1) [1,6]

        int sum = accumulate(rolls.begin(),rolls.end(),0);
        int x = (mean * (m+n)) - sum;
        // cout << "x " << x << endl;

        if( x < n || x > 6*n )
            return {};

        if( n == 1 )
            return {x};

        vector<int> ans(n,1);

        int rem = x - n;
        int i = 0;
        while( rem > 0 ) {
            if( rem >= 5 ) {
                ans[i] = 6;
                rem -= 5;
            } else {
                ans[i] = 1+rem;
                break;
            }
            ++i;
        }

        return ans;
    }
};
