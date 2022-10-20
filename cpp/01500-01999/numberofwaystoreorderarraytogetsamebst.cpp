
// 1569. Number of Ways to Reorder Array to Get Same BST
// https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/



class Solution {
private:
    long mod = 1000000007;

    long t[1001][1001];

    long dfs(vector<int>& nums) {
        int n = nums.size();
        if( n <= 2 )
            return 1L;

        // nums[0] is always the root
        // divide nums into element smaller aka left child/subtree and
        // larger aka right child/subtree
        vector<int> smaller;
        vector<int> larger;
        int root = nums[0];
        for(int i = 1; i < n; ++i) {
            int k = nums[i];
            if( k < root )
                smaller.push_back(k);
            else
                larger.push_back(k);
        }

        // divide
        int x  = smaller.size();
        long l = dfs(smaller);
        int y  = larger.size();
        long r = dfs(larger);
        // conquer aka merge
        // answer is the number of possibilities of the left node x
        //               number of possibilities of the right node x
        // the number of times we can interleave those possibilities
        // which is formaly:
        //    let x be the the number of elements in the left subtree
        //    let y be the number of elements in the right subtree
        //    how many ways can we order x elements in x+y positions
        //    [or vice versa]

        int elements = x != 0 ? x : y;
        int positions = x + y;

        return (((l * r) % mod) * t[elements][positions]) % mod;
    }


public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();

        // t[elements][slots] whereas elements <= slots
        // DP bottom up
        for(int i = 1; i <= n; ++i)
            for(int j = i; j <= n; ++j)
                if( i == 1 )
                    t[i][j] = j;
                else if( i == j )
                    t[i][j] = 1;
                else
                    t[i][j] = (t[i][j-1] + t[i-1][j-1]) % mod;

        return dfs(nums)-1; // because 1 permutation was given to us
    }
};
