
// 2177. Find Three Consecutive Integers That Sum to a Given Number
// https://leetcode.com/problems/find-three-consecutive-integers-that-sum-to-a-given-number/


class Solution {
public:
    vector<long long> sumOfThree(long long num) {
        // num = x-1 + x + x+1 => num = 3x => num/3 = x

        if( num % 3LL == 0 ) {
            long long x = num / 3LL;
            vector<long long> ans = {x-1,x,x+1};
            return ans;
        } else {
            return {};
        }

    }
};
