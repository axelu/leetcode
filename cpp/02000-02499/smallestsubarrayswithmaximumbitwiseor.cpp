
// 2411. Smallest Subarrays With Maximum Bitwise OR
// https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/





class Solution {
private:
    int w;
    int orw[32];

    void add(int x) {
        for(int i = 0; i < 32; ++i)
            if( x & (1 << i) ) {
                ++orw[i];
                w |= 1 << i;
            }
    }

    void shrink(int x) {
        for(int i = 0; i < 32; ++i)
            if( x & (1<<i) ) {
                --orw[i];
                if( orw[i] == 0 )
                    w &= ~(1 << i);
            }
    }

public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();

        int b[n];
        b[n-1] = nums[n-1];
        for(int i = n-2; i >= 0; --i)
            b[i] = nums[i] | b[i+1];

        vector<int> ans(n);

        w = 0;
        memset(orw,0,sizeof orw);
        add(nums[0]);

        for(int i = 0, j = 0; i < n; ++i) {
            if( j < i )
                add(nums[++j]);

            //cout << "i " << i << endl;
            if( w < b[i] ) {
                // we need to grow the current window
                while( j+1 < n && w < b[i] ) {
                    add(nums[++j]);
                    //cout << "  j " << j << endl;
                    //cout << "  w " << w << endl;
                }
            }

            ans[i] = j-i+1;

            // shrink the current window
            shrink(nums[i]);
        }

        return ans;
    }
};
