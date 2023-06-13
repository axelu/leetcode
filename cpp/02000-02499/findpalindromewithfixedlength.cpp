
// 2217. Find Palindrome With Fixed Length
// https://leetcode.com/problems/find-palindrome-with-fixed-length/



/* let intLength = 7
 *
 *              0  1   2   3   2   1   0
 * contributes  9 10  10  10
 * so there are 9 * 10 * 10 * 10 palindromes
 * 1st      1000001
 * 2nd      1001001
 * 3rd      1002001
 * ...
 * 10th     1009001
 * 11th     1010101
 * ...
 * 20th     1019101
 * ...
 * 9000th   9999999
 *
 * observation
 * example query 1070, intLength = 7
 * answer        2069602
 * we can subtract 1 from the query and build our answer
 * we need to pay attention to the left most digit
 */
class Solution {
public:
    vector<long long> kthPalindrome(vector<int>& queries, int intLength) {
        int n = queries.size();

        int intLength2 = intLength/2;
        if( intLength % 2 )
            ++intLength2;
        int mx = 9 * pow(10,intLength2-1);

        vector<long long> ans(n);

        for(int i = 0; i < n; ++i) {
            if( queries[i] > mx ) {
                ans[i] = -1;
                continue;
            }

            int q = queries[i] - 1;
            string q_str = to_string(q);
            int q_str_sz = q_str.size();

            string t = "";
            for(int j = 0; j < intLength2; ++j) {
                int k = j - (intLength2 - q_str_sz); // index in q_str
                if( k >= 0 ) {
                    if( j == 0 && k == 0 ) {
                        t = (q_str[k]+1);
                    } else {
                        t = t + q_str[k];
                    }
                } else if( j == 0 ) {
                    t = "1";
                } else {
                    t = t + "0";
                }
            }
            // complete the right side of t
            int k = intLength % 2 == 0 ? t.size() - 1 : t.size() - 2;
            for(; k >= 0; --k)
                t.push_back(t[k]);

            ans[i] = stoll(t);
        }

        return ans;
    }
};
