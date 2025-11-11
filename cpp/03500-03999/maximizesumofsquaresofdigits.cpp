
// 3723. Maximize Sum of Squares of Digits
// https://leetcode.com/problems/maximize-sum-of-squares-of-digits/


class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        // 1 <= num <= 2 * 1e5
        // 1 <= sum <= 2 * 1e6

        // quick check
        // we could put a 9 in every position of our integer
        // max_sum = num * 9
        // if max_sum < sum then we have no solution
        // worst case 9 * 2 * 1e5 = 1,800,000
        // theoretical worst case score 9^2 * 2 * 1e5 = 81 * 2 * 1e5 = 16,200,000
        int max_sum = num * 9;
        if( max_sum < sum )
            return "";

        if( max_sum == sum )
            return string(num, '9');

        if( sum < 10 ) {
            string res1(1, sum+'0');
            string res2(num-1, '0');
            return res1 + res2;
        }

        // we greedily fill with 9's
        int nines = sum / 9;
        // positions [0..nines-1] are 9's
        int rem = sum % 9;
        // position nines is rem
        // positions [nines+1..num-1] are 0's

        string ret(nines,'9');
        ret.push_back(rem+'0');
        int zeros = num - (nines + 1);
        if( zeros > 0 ) {
            ret += string(zeros, '0');
        }

        return ret;;
    }
};
