
// 3040. Maximum Number of Operations With the Same Score II
// https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-ii/



class Solution {
private:
    int n;

    int * mem;

    int rec(vector<int>& nums, int i, int j, const int res) {
        int l = j - i + 1;
        if( l < 2 )
            return 0;

        int idx = i * n + j;
        if( mem[idx] != -1 )
            return mem[idx];

        // we have a choice
        //    delete the first two elements of nums OR
        //    delete the last two elements of nums OR
        //    delete the first and the last element
        int a = 0;
        if( nums[i] + nums[i+1] == res ) {
            a = 1 + rec(nums, i+2, j, res);
        }
        int b = 0;
        if( nums[j-1] + nums[j] == res ) {
            b = 1 + rec(nums, i, j-2, res);
        }
        int c = 0;
        if( nums[i] + nums[j] == res ) {
            c = 1 + rec(nums, i+1, j-1, res);
        }

        return mem[idx] = max({a,b,c});
    }

public:
    int maxOperations(vector<int>& nums) {
        n = nums.size();
        if( n < 2 )
            return 0;
        if( n <= 3 )
            return 1;

        // we can start either with
        //    delete the first two elements of nums OR
        //    delete the last two elements of nums OR
        //    delete the first and the last element

        int _mem[n*n]; memset(_mem,-1,sizeof _mem); mem = _mem;

        int res = nums[0] + nums[1];
        int a = 1 + rec(nums, 2, n-1, res);

        res = nums[n-2] + nums[n-1];
        memset(_mem,-1,sizeof _mem);
        int b = 1 + rec(nums, 0, n-3, res);

        res = nums[0] + nums[n-1];
        memset(_mem,-1,sizeof _mem);
        int c = 1 + rec(nums, 1, n-2, res);

        return max({a,b,c});
    }
};
