
// 2178. Maximum Split of Positive Even Integers
// https://leetcode.com/problems/maximum-split-of-positive-even-integers/



class Solution {
public:
    vector<long long> maximumEvenSplit(long long finalSum) {
        vector<long long> ans;
        if( finalSum % 2 )
            return ans;

        long long even = 0;
        long long running_sum = 0;
        while( running_sum < finalSum ) {
            even = even + 2;
            running_sum = running_sum + even;
        }

        long long t = running_sum - finalSum;
        for(long long i = 2; i <= even; i = i + 2) {
            if( i != t )
                ans.push_back(i);
        }

        return ans;    }
};
