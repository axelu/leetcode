
// 1425. Constrained Subsequence Sum
// https://leetcode.com/problems/constrained-subsequence-sum/



public class Cmp: IComparer<int[]> {
    public int Compare(int[] a, int[] b) {
        if( a[0] < b[0] ) {
            return 1;
        } else if( a[0] == b[0] ) {
            if( a[1] < b[1] ) // keep the closer one
                return 1;
        }
        return -1;
    }
}

public class Solution {
    public int ConstrainedSubsetSum(int[] nums, int k) {
        // from the hint:
        //     let dp[i] be the solution for the prefix of the array that ends at i,
        //     if the element at i is in the subsequence.
        //     dp[i] = nums[i] + max(0, dp[i-k], dp[i-k+1], ..., dp[i-1])

        int n = nums.Length;

        PriorityQueue<int[],int[]> pq = new(new Cmp());

        int[] dp = new int[n];
        dp[0] = nums[0];
        int[] p = {dp[0],0};
        pq.Enqueue(p,p);


        int ans = dp[0];

        for(int j = 1; j < n; ++j) {

            while( pq.Peek()[1] < j-k )
                pq.Dequeue();

            dp[j] = nums[j] + Math.Max(0,pq.Peek()[0]);
            int[] t = {dp[j],j};
            pq.Enqueue(t,t);

            ans = Math.Max(ans,dp[j]);

        }

        return ans;
    }
}
