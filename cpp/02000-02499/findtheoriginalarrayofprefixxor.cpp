
// 2433. Find The Original Array of Prefix Xor
// https://leetcode.com/problems/find-the-original-array-of-prefix-xor/




/*
 * example 1: pref = {5,2,0,3,1}
 *            ans  = {5,7,2,3,2}
 * pref[0] = 5.
 * pref[1] = 5 ^ 7 = 2.
 * pref[2] = 5 ^ 7 ^ 2 = 0.
 * pref[3] = 5 ^ 7 ^ 2 ^ 3 = 3.
 * pref[4] = 5 ^ 7 ^ 2 ^ 3 ^ 2 = 1.
 */
class Solution {
public:
    vector<int> findArray(vector<int>& pref) {
        int n = pref.size(); // 1 <= pref.length <= 10^5

        vector<int> ans(n);
        ans[0] = pref[0];

        int prev = pref[0];
        for(int i = 1; i < n; ++i) {

            int t =  pref[i] ^ prev;
            ans[i] = t;

            prev = prev ^ t;
        }

        return ans;
    }
};
