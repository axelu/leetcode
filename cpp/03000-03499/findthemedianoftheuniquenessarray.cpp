
// 3134. Find the Median of the Uniqueness Array
// https://leetcode.com/problems/find-the-median-of-the-uniqueness-array/




class Solution {
private:

    long subarraysWithUpToKDistinct(vector<int>& nums, int k) {
        if( k <= 0 )
            return 0;

        long n = nums.size();
        long ret = 0;

        int cnt[100001];memset(cnt,0,sizeof cnt);
        int uniques = 0;
        int i = 0;
        for(int j = 0; j < n; ++j) {
            int numsj = nums[j];
            ++cnt[numsj];
            if( cnt[numsj] == 1 )
                ++uniques;

            while( uniques > k ) {
                int numsi = nums[i];
                --cnt[numsi];
                if( cnt[numsi] == 0 )
                    --uniques;
                ++i;
            }

            ret += (j - i + 1); // cumulative count of subarrays we can make
        }

        // cout << "subarraysWithUpToKDistinct k " << k << " ret " << ret << endl;
        return ret;
    }

    // binary search
    int search(vector<int>& nums, int s, int e, long median_index) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        long nbr_subarraysWithUpToKDistinct = subarraysWithUpToKDistinct(nums, mid);
        if( nbr_subarraysWithUpToKDistinct >= median_index ) {
            // can we do better?
            int t = search(nums, s, mid-1, median_index);
            return t != -1 ? t : mid;
        }

        return search(nums, mid+1, e, median_index);
    }

public:
    int medianOfUniquenessArray(vector<int>& nums) {
        long n = nums.size(); // 1 <= nums.size() <= 1e5; 1 <= nums[i] <= 1e5
        // cout << "n " << n << endl;

        // total number of subarrays n * (n+1)/2
        // let m be the number of unique elements in nums
        // with that we know, that the number of distinct elements in every subarray is between 1 and m inclusive
        // we are asked to look at that in an ordered way and retrieve the median
        // our median will be at position (total number of subarrays) / 2
        // because it is ordered, we can do a binary search in the range 1 to m
        //     we pick a number k between 1 and m and calculate the number of subarrays that
        //     have up to k distinct elements.
        //     if that result is equal or greater than where our median lies, than we have a candidate answer
        //         and try with a lower number of distinct elements
        //     if that result is smaller, then we need to increase

        int uniques = 0;
        int cnt[100001]; memset(cnt,0,sizeof cnt);
        for(int x: nums)
            if( ++cnt[x] == 1 )
                ++uniques;
        // cout << "uniques " << uniques << endl;

        long total_number_of_subarrays = n * (n + 1L) / 2L;
        // cout << "total_number_of_subarrays " << total_number_of_subarrays << endl;
        long median_index = (total_number_of_subarrays + 1L) / 2;
        // cout << "median_index " << median_index << endl;

        /*
        long tt1 = subarraysWithUpToKDistinct(nums, 25702);
        cout << "             " << tt1 << endl;

        return 99;
        */
        return search(nums, 1, uniques, median_index);
    }
};
