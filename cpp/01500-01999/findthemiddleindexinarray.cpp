




// 1991. Find the Middle Index in Array
// https://leetcode.com/problems/find-the-middle-index-in-array/


class Solution {
public:
    int findMiddleIndex(vector<int>& nums) {
        int n = nums.size();

        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 0; i < n; ++i)
            prefixSum[i+1] = prefixSum[i] + nums[i];

        /*
        for(int i = 0; i <= n; ++i)
            cout << prefixSum[i] << " ";
        cout << endl;
        */

        int leftSum,rightSum;
        for(int i = 0; i < n; ++i) {
            // sum left of i, with i being the middleIndex
            leftSum = prefixSum[i];
             // sum right of i, with i being the middleIndex
            rightSum = prefixSum[n]-prefixSum[i+1];
            if( leftSum == rightSum )
                return i;
        }


        return -1;
    }
};
