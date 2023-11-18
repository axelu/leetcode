
// 2834. Find the Minimum Possible Sum of a Beautiful Array
// https://leetcode.com/problems/find-the-minimum-possible-sum-of-a-beautiful-array/




class Solution {
public:
    long long minimumPossibleSum(int n, int target) {
        unordered_set<long long> us;

        long long sum = 0;
        int k = 0;
        for(long long i = 1; k < n; ++i) {

            if( i < target && us.find(i) == us.end() ) {
                sum += i;
                us.insert(target - i);
                ++k;

            } else if( i >= target ) {
                sum += i;
                ++k;
            }
        }

        return sum;
    }
};
