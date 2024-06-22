
// 2918. Minimum Equal Sum of Two Arrays After Replacing Zeros
// https://leetcode.com/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/






class Solution {
private:
    // based on constraints given in the problem
    // 0 <= nums1[i], nums2[i] <= 1e6
    // const long long MAX_ELEMENT = 1e6;

    pair<long long, long long> get_sum_and_nbr_zeros(vector<int>& nums) {
        long long cnt_zeros = 0LL;
        long long sum = 0LL;
        for(long long x: nums)
            if( x == 0LL )
                ++cnt_zeros;
            else
                sum += x;
        return {sum,cnt_zeros};
    }

    long long sum1_fixed(long long sum1, long long sum2, long long zeros2) {
        // sum1 is fixed and
        // sum2 will go up by at least zeros2
        if( sum1 <= sum2 )
            return -1;

        // can we reach sum1?
        long long sum2_min = sum2 + zeros2;
        if( sum1 < sum2_min )
            return -1;

        return sum1;
    }

public:
    long long minSum(vector<int>& nums1, vector<int>& nums2) {
        auto p1 = get_sum_and_nbr_zeros(nums1);
        long long sum1 = p1.first;
        long long zeros1 = p1.second;

        auto p2 = get_sum_and_nbr_zeros(nums2);
        long long sum2 = p2.first;
        long long zeros2 = p2.second;

        // case 1 both sums fixed
        if( zeros1 == 0LL && zeros2 == 0LL )
            return sum1 == sum2 ? sum1 : -1LL;

        // case2 one sum of the two sumes fixed
        if( zeros1 == 0LL || zeros2 == 0LL )
            return zeros1 == 0 ? sum1_fixed(sum1,sum2,zeros2) : sum1_fixed(sum2,sum1,zeros1);

        // case3 both sums can be raised
        long long sum1_min = sum1 + zeros1;
        long long sum2_min = sum2 + zeros2;

        return max(sum1_min,sum2_min);
    }
};
