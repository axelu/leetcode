




// 1000. Minimum Cost to Merge Stones
// https://leetcode.com/problems/minimum-cost-to-merge-stones/


class Solution {
private:
    int prefixSum[31];
    int mem[30][30];

    int rec(vector<int>& stones, int k, int i, int j) {
        // cout << "rec i " << i << " j " << j << endl;

        if( j-i+1 < k ) // there is no cost if length of range is less than k
            return 0;


        if( mem[i][j] != -1)
            return mem[i][j];


        int ret = INT_MAX;

        // if our range is greater than k we need to split in k-1 increments
        for(int p = i; p < j; p += k-1) {
            ret = min(ret,rec(stones,k,i,p)+rec(stones,k,p+1,j));
        }

        // if range[i,j] is reducible to 1 pile, we need to add the range sum
        // of stones[i..j] to the cost
        if( (j-i) % (k-1) == 0 )
            ret += prefixSum[j+1]-prefixSum[i];

        return mem[i][j] = ret;
    }


public:
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();


        // at each merge we are reducing the number of piles by k-1 to arrive at 1 pile
        // n - (x * (k-1)) = 1  =>  n-1 = x * (k-1)
        // so (n-1) needs to be divisible by (k-1) for there to be a solution
        if( (n-1) % (k-1) != 0 )
            return -1;


        // prefix sum to look up sum of range [i,j] inclusive fast
        prefixSum[0] = 0;
        for(int i = 0; i < n; ++i)
            prefixSum[i+1] = prefixSum[i] + stones[i];

        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                mem[i][j] = -1;

        // recursion + memoization = dp top-down
        return rec(stones,k,0,n-1);
    }
};
