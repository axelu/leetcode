
// 1770. Maximum Score from Performing Multiplication Operations
// https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/




class Solution {
private:

    int dfs(vector<int>& nums, int n, vector<int>& multipliers, int m,
            int l, int r, int mem[]) {

        // cout << "l " << l << " r " << r << endl;

        int i = n-(r-l+1); // step
        // cout << "step " << i << endl;
        if( i == m-1 )
            return max(multipliers[i]*nums[l],multipliers[i]*nums[r]);


        int memIdx = l*m+(n-1-r);
        if( mem[memIdx] != -1000000001 )
            return mem[memIdx];


        // at each step we have a choice to take the left or right index
        int left  = multipliers[i]*nums[l] + dfs(nums,n,multipliers,m,l+1,r,mem);
        int right = multipliers[i]*nums[r] + dfs(nums,n,multipliers,m,l,r-1,mem);

        return mem[memIdx] = max(left,right);
    }

public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        // max score 10^9, min score -10^9

        int n = nums.size();
        int m = multipliers.size();

        int mem[m*m];
        for(int i = 0; i < m*m; ++i)
                mem[i] = -1000000001;

        return dfs(nums,n,multipliers,m,0,n-1,mem);
    }
};
