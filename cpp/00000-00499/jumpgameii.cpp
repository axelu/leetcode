
// 45. Jump Game II
// https://leetcode.com/problems/jump-game-ii/

class Solution {
private:
    int rec(vector<int>& nums, int n, int pos, int mem[]) {
        if( pos >= n ) 
            return 1e9; // some large number
        
        if( pos == n-1 )
            return 0;
        
        if( mem[pos] != -1) 
            return mem[pos];
        
        int ret = 1e9;
        for(int i = 1; i <= nums[pos]; ++i)
            ret = min(ret, 1 + rec(nums,n,pos+i,mem));
        
        return mem[pos] = ret;
    }

public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int mem[n];memset(mem,-1,sizeof mem);
     
        return rec(nums,n,0,mem);
    }    
};
