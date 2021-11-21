
// 1793. Maximum Score of a Good Subarray
// https://leetcode.com/problems/maximum-score-of-a-good-subarray/





class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        if( n == 1 )
            return nums[0];


        int ans = nums[k];


        // edge cases k == 0, k == n-1
        int t = nums[k];
        if( k == n-1) {
            for(int i = n-2; i >= 0; --i) {
                if( nums[i] < t ) {
                    ans = max(ans,(n-1-i)*t);
                    t = nums[i];
                }
            }
            ans = max(ans,n*t);
            return ans;
        }
        if( k == 0) {
            for(int i = 1; i < n; ++i) {
                if( nums[i] < t ) {
                    ans = max(ans,i*t);
                    t = nums[i];
                }
            }
            ans = max(ans,n*t);
            return ans;
        }


        int i = k-1; // left index
        while( i >= 0 && nums[i] >= nums[k] )
            --i;
        int j = k+1; // right index
        while( j < n && nums[j] >= nums[k] )
            ++j;

        if( i < 0 && j == n )
            return nums[k]*n;

        int tl = i >= 0 ? nums[i] : nums[k];
        int tr = j < n ? nums[j] : nums[k];
        ans = max(ans,(j-i-1)*nums[k]);

        while( true ) {
            // cout << "in  i  " << i << " j  " << j << " tl " << tl << " tr " << tr << endl;
            // expand to the left and right of k

            if( tl == tr ) {
                // left
                while( i >= 0 && nums[i] >= tl )
                    --i;

                // right
                while( j < n && nums[j] >= tr )
                    ++j;

                ans = max(ans,(j-i-1)*tl);
                tl = i >= 0 ? nums[i] : 0;
                tr = j < n ? nums[j] : 0;
            } else {
                if( tr > tl ) {
                    while( j < n && nums[j] >= tr )
                        ++j;
                    ans = max(ans,(j-i-1)*tr);
                    tr = j < n ? nums[j] : 0;
                } else {
                    // tr < tl
                    while( i >= 0 && nums[i] >= tl )
                        --i;
                    ans = max(ans,(j-1-i)*tl);
                    tl = i >= 0 ? nums[i] : 0;
                }
            }

            // cout << "out i  " << i << " j  " << j << " tl " << tl << " tr " << tr << endl;
            // cout << "ans " << ans << endl;


            if( i < 0 && j == n )
                break;
        }



        return ans;
    }
};
