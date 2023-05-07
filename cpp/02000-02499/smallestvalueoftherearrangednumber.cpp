
// 2165. Smallest Value of the Rearranged Number
// https://leetcode.com/problems/smallest-value-of-the-rearranged-number/ 



class Solution {
public:
    long long smallestNumber(long long num) {
        // -10^15 <= num <= 10^15
        if( num == 0 )
            return num;

        bool is_negative = false;
        if( num < 0 ) {
            is_negative = true;
            num *= -1;
        }

        int cnt[10];memset(cnt,0,sizeof cnt);

        while( num > 0 ) {
            ++cnt[num % 10];
            num /= 10;
        }

        string str_ans = "";
        if( !is_negative ) {
            // place 1 of the smallest positive integer 1st
            for(int i = 1; i < 10; ++i) {
                if( cnt[i] > 0 ) {
                    str_ans.push_back(i+'0');
                    --cnt[i];
                    break;
                }
            }

            // place 0s next
            for(int t = cnt[0]; t > 0; --t)
                str_ans.push_back('0');

            // place all integers starting from smallest
            for(int i = 1; i < 10; ++i) {
                for(int t = cnt[i]; t > 0; --t)
                    str_ans.push_back(i+'0');
            }

        } else {
            // places all digits from largest to smallest
            for(int i = 9; i >= 0; --i) {
                for(int t = cnt[i]; t > 0; --t)
                    str_ans.push_back(i+'0');
            }
        }

        long long ans = stoll(str_ans);
        if( is_negative )
            ans *= -1;

        return ans;
    }
};
