
// 2802. Find The K-th Lucky Number
// https://leetcode.com/problems/find-the-k-th-lucky-number/





/* 1 <= k <= 10^9
 * so enumeration is not an option
 * 1th: "4"
 * 1000000000th: "77477744774747744747444444447"
 */
class Solution {
public:
    string kthLuckyNumber(int k) {
        // 1 <= k <= 10^9

        string ans = "";

        int four = 1;
        int seven = 1;
        stack<array<int,3>> prev_range; // previous range begin, previous range end
        prev_range.push({1,2,1});

        while( true ) {
            if( k == 1 ) {
                ans.push_back('4');
                break;
            }
            if( k == 2 ) {
                ans.push_back('7');
                break;
            }

            int begin_of_range = prev_range.top()[1] + 1;
            // cout << "begin_of_range " << begin_of_range << endl;

            int four = 2 * prev_range.top()[2];
            int begin_of_range_4 = prev_range.top()[1] + 1;
            int end_of_range_4   = prev_range.top()[1] + four;
            // cout << "end_of_range_4 " << end_of_range_4 << endl;
            if( end_of_range_4 >= k ) {
                ans.push_back('4');
                k = prev_range.top()[0] + (k - begin_of_range_4);
                prev_range.pop();
                continue;
            }

            seven = 2 * prev_range.top()[2];
            int begin_of_range_7 = end_of_range_4 + 1;
            int end_of_range_7 = end_of_range_4 + seven;
            // cout << "end_of_range_7 " << end_of_range_7 << endl;
            if( end_of_range_7 >= k ) {
                ans.push_back('7');
                k = prev_range.top()[0] + (k - begin_of_range_7);
                prev_range.pop();
                continue;
            }

            int end_of_range = prev_range.top()[1] + four + seven;
            // cout << "end_of_range   " << end_of_range << endl;

            prev_range.push({begin_of_range, end_of_range, 2 * prev_range.top()[2]});
        }

        return ans;
    }
};
