
// 2576. Find the Maximum Number of Marked Indices
// https://leetcode.com/problems/find-the-maximum-number-of-marked-indices/




class Solution {
public:
    int maxNumOfMarkedIndices(vector<int>& nums) {
        int n = nums.size(); cout << n << endl;
        if( n == 1 )
            return 0;

        int ans = 0;

        // two pointer approach
        sort(nums.begin(),nums.end());
        vector<bool> seen(n,false);
        int j = n-1;
        int i = n/2-1;
        while( i >= 0 ) {

            while( j > 0 && seen[j] )
                --j;
            if( j == 0 )
                break;

            if( i >= j )
                i = j-1;
            while( i >= 0 && seen[i] )
                --i;
            if( i == -1 )
                break;

            while( i >= 0 && 2 * nums[i] > nums[j] )
                --i;
            if( i == -1 )
                break;

            ans += 2;
            seen[i] = true;
            --i;
            seen[j] = true;
            --j;
        }

        return ans;
    }
};
