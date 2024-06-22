
// 2963. Count the Number of Good Partitions
// https://leetcode.com/problems/count-the-number-of-good-partitions/





class Solution {
private:
    long mod = 1000000007;

    // exponention using bit manipulation
    long modular_pow(long base, long exponent) {

        long ret = 1;

        while(exponent > 0) {

            int last_bit = (exponent & 1);
            if( last_bit )
                ret = (ret * base) % mod;

            base = (base * base) % mod;

            exponent = exponent >> 1;
        }

        return ret;
    }

public:
    int numberOfGoodPartitions(vector<int>& nums) {
        // if we have n distinct elements in our array,
        // then the number of Good Partitions is 2^(n-1)
        // https://en.wikipedia.org/wiki/Composition_(combinatorics)
        // example n = 8 such as nums = {1,2,3,4,5,6,7,8}
        //         answer: 2^(n-1) = 2^(8-1) = 2^7 = 128
        // so we need to find the number of 'distinct' elements in our array
        // example nums = {1,3,4,2,1,5,6,2}
        //                 ---------
        //                       ---------
        // given the conditions of the problem, the number of 'distinct' elements in our array is 1
        // hence the answer is 1
        // we need to do an interval merge

        int interval_idx = 0;
        vector<pair<int,int>> ranges;
        unordered_map<int,int> um; // val, interval_idx
        int nums_sz = nums.size();
        for(int i = 0; i < nums_sz; ++i) {
            auto p = um.insert({nums[i],interval_idx});
            if( p.second ) {
                ranges.push_back({i,i});
                ++interval_idx;
            } else {
                ranges[p.first->second].second = i;
            }
        }

        int ranges_sz = ranges.size();
        if( ranges_sz == 1 )
            return 1;

        int n = 1;
        int curr_interval_end = ranges[0].second;
        for(int i = 1; i < ranges_sz; ++i) {
            if( ranges[i].first < curr_interval_end ) {
                if( ranges[i].second > curr_interval_end )
                    curr_interval_end = ranges[i].second;
            } else {
                ++n;
                curr_interval_end = ranges[i].second;
            }
        }

        return modular_pow(2,n-1);
    }
};
