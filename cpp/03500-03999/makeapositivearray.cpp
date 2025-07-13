
// 3511. Make a Positive Array
// https://leetcode.com/problems/make-a-positive-array/





class Solution {

public:
    int makeArrayPositive(vector<int>& nums) {
        int n = nums.size(); cout << "n " << n << endl;

        int ans = 0;

        // we are asked to return min number of operations needed
        // if we set an element nums[i] then any subarray that
        // nums[i] is a part off will be a good subarray, because
        // we can set it to 1e18

        int i = -1; // last index on left we set to 1e18
        for(int j = 2; j < n; ++j) {
            // every nums[j] <= 0 has the potential to cause us
            // having a subarray of len >= 3 where sum <= 0
            // we also know that we have set nums[i] to 1e18, so we
            // do not need to look beyond i to the left

            long long sum = 0LL;
            int lft = j;
            while ( true ) {
                if( lft == i )
                    break;
                sum += nums[lft];
                if( j - lft + 1 >= 3 ) {
                    if( sum <= 0 )
                        break;
                }
                --lft;
            }
            if( lft > i && j-lft+1 >= 3 ) {
                // the subarray [lft,j] has a sum <= 0
                // we would set nums[j] = 1e18
                ++ans;
                i = j;
                j += 2; // loop will advance j
            }
        }



        return ans;
    }
};
