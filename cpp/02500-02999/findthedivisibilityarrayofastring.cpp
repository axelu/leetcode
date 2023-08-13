
// 2575. Find the Divisibility Array of a String
// https://leetcode.com/problems/find-the-divisibility-array-of-a-string/




/* 15 / 3
 * starting with a remainder of 0
 * 1 % 3 = 1 => carry 1
 * 5 % 3 = 2 => 2 + carry 1 = 3, 3 % 3 = 0
 *
 * ans = {0,1};
 */
class Solution {
public:
    vector<int> divisibilityArray(string word, int m) {
        int n = word.size();

        vector<int> ans(n,0);

        unsigned long long carry = 0;
        for(int i = 0; i < n; ++i) {
            int t1 = (carry*10 + (word[i]-'0')) % m;
            // int t2 = (t1 + carry*10) % m;
            if( t1 == 0 )
                ans[i] = 1;
            carry = t1;
        }

        return ans;
    }
};
