
// 3012. Minimize Length of Array Using Operations
// https://leetcode.com/problems/minimize-length-of-array-using-operations/





/* example test cases
[1,4,3,1]
[5,5,5,10,5]
[2,3,4]
[5,2,2,2,9,10]
[2,7,2,4,2,9]
*/
class Solution {
public:
    int minimumArrayLength(vector<int>& nums) {
        int n = nums.size();

        // we basically could pair any element with any other and try to find the optimal pairing,
        // as long as neither element == 0
        // we do wan't to avoid any pairing and order of that pair that however results in nums[i] % nums[j] == 0
        // example: 4,2 -> 4 % 2 == 0 bad, 2 % 4 == 2 good
        // observation: if we take 'small' % 'large', the result will be 'small'
        // so we could pair the smallest element with any greater element and shorten the array all the way
        // till only the small element is left -> ans = 1
        // if we have more than one of the smallest element, we will have cnt/2 ceil left
        // but, if we find a pair, who's remainder is less than the smallest element, we can get to 1 smallest element.

        sort(nums.begin(),nums.end());
        int mn = nums[0];
        int cnt = 1;
        for(int i = 1; i < n; ++i) {
            if( nums[i] == mn )
                ++cnt;
            if( nums[i] != mn ) {
                if( cnt == 1 )
                    break;
                if( nums[i] % mn != 0 ) {
                    // the new remainder will be smaller than min,
                    // so we are back to one min value
                    cnt = 1;
                    break;
                }
            }
        }
        if( cnt == 1 )
            return 1;

        return ceil(cnt/2.0);
    }
};
