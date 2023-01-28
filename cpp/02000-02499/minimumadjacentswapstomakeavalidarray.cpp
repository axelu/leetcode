
// 2340. Minimum Adjacent Swaps to Make a Valid Array
// https://leetcode.com/problems/minimum-adjacent-swaps-to-make-a-valid-array/




class Solution {
public:
    int minimumSwaps(vector<int>& nums) {
        // determine position of max element, if multiple return rightmost
        // determine position of min element, if multiple return leftmost

        int n = nums.size();

        int mn = 100001, mn_pos;
        int mx = 0, mx_pos;

        for(int i = 0; i < n; ++i) {
            if( nums[i] < mn ) {
                mn = nums[i];
                mn_pos = i;
            }
            if( nums[i] >= mx ) {
                mx = nums[i];
                mx_pos = i;
            }
        }

        //cout << "mn " << mn << " mn_pos " << mn_pos << endl;
        //cout << "mx " << mx << " mx_pos " << mx_pos << endl;

        int ans = mn_pos + n - mx_pos - 1;
        if( mn_pos > mx_pos )
            --ans;

        return ans;
    }
};
