
// 2566. Maximum Difference by Remapping a Digit
// https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/


class Solution {
public:
    int minMaxDifference(int num) {

        stack<int> stck;

        int x = num;
        while( x > 0 ) {
            int rem = x % 10;
            // cout << rem << endl;
            stck.push(rem);
            x /= 10;
        }

        int mx = 0;
        int mx_replacee = -1;
        int mn = 0;
        int mn_replacee = -1;
        while( !stck.empty() ) {
            // get max => map first non-nine digit to 9
            int t = stck.top();
            mx = 10 * mx;
            if( mx_replacee == -1 ) {
                if( t != 9 )
                    mx_replacee = t;
            }
            if( t == mx_replacee )
                t = 9;
            mx += t;

            // get min => map first digit to zero
            t = stck.top();
            mn = 10 * mn;
            if( mn_replacee == -1 ) {
                mn_replacee = t;
            }
            if( t == mn_replacee )
                t = 0;
            mn += t;

            stck.pop();
        }
        // cout << "mx " << mx << endl;
        // cout << "mn " << mn << endl;

        return mx - mn;
    }
};
