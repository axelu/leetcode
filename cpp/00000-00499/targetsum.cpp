
// 494. Target Sum
// https://leetcode.com/problems/target-sum/



class Solution {
private:
    int dfs(vector<int>& nums, int m, int n, int offset, int i, int res, int target, int mem[]) {
        if( i == m )
            return res == target;

        int memIdx = i*n+(res+offset);
        if( mem[memIdx] != -1 )
            return mem[memIdx];

        // at each pos we have a choice to add a + or - operation
        int add = dfs(nums,m,n,offset,i+1,res+nums[i],target,mem);
        int sub = dfs(nums,m,n,offset,i+1,res-nums[i],target,mem);

        return mem[memIdx] = add+sub;
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int m = nums.size();
        int n = m*2*1000+1;
        int offset = m*1000;

        int mem[m*n];memset(mem,-1,sizeof mem);
        return dfs(nums,m,n,offset,0,0,target,mem);
    }
};
