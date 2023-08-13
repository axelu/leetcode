
// 2811. Check if it is Possible to Split Array
// https://leetcode.com/problems/check-if-it-is-possible-to-split-array/





class Solution {
private:
    vector<int> prefixSum;
    int mem[101][101];

    bool rec(int s, int e, int m) {
        // cout << "rec s " << s << " e " << e << endl;
        if( e == s )
            return true;

        if( mem[s][e] != -1 )
            return mem[s][e];

        for(int i = s; i < e; ++i) {
            if( i-s > 0 && prefixSum[i+1] - prefixSum[s] < m )
                continue;
            if( e - (i+1) > 0 && prefixSum[e+1] - prefixSum[i+1] < m )
                continue;
            if( rec(s,i,m) && rec(i+1,e,m) )
                return mem[s][e] = true;
        }

        return mem[s][e] = false;
    }

public:
    bool canSplitArray(vector<int>& nums, int m) {
        int n = nums.size();
        if( n == 1 )
            return true;

        prefixSum.assign(n+1,0);
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        memset(mem,-1,sizeof mem);

        return rec(0,n-1,m);
    }
};
