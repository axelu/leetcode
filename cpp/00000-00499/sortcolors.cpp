
// 75. Sort Colors
// https://leetcode.com/problems/sort-colors/





class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return;

        int i;


        // 2 pass solution
        /*
        int cnt[3];memset(cnt,0,sizeof cnt);
        // pass 1
        for(i = 0; i < n; ++i)
            ++cnt[nums[i]];

        // pass 2
        // 0s
        for(i = 0; i < cnt[0]; ++i)
            nums[i] = 0;
        // 1s
        for(; i < cnt[0]+cnt[1]; ++i)
            nums[i] = 1;
        // 2s
        for(; i < cnt[0]+cnt[1]+cnt[2]; ++i)
            nums[i] = 2;
        */

        // 1 pass solution

        // 0s
        for(i = 0; i < n; ++i)
            if( nums[i] != 0 ) // go to first element != 0
                break;

        int j = i+1;
        for(; i < n; ++i) {

            while( j < n && nums[j] != 0 )
                ++j;
            if( j == n )
                break;

            nums[j] = nums[i];
            nums[i] = 0;
            ++j;
        }

        // 1s
        for(; i < n; ++i)
            if( nums[i] != 0 && nums[i] != 1 ) // go to first element != 1
                break;

        j = i+1;
        for(; i < n; ++i) {

            while( j < n && nums[j] != 1 )
                ++j;
            if( j == n )
                break;

            nums[j] = 2;
            nums[i] = 1;
            ++j;
        }


    }
};
