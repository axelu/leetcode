
// 373. Find K Pairs with Smallest Sums
// https://leetcode.com/problems/find-k-pairs-with-smallest-sums/



public class Cmp: IComparer<int> {
    public int Compare(int a, int b) {
        if( a == b )
            return 0;
        else if( a > b)
            return -1;
        else
            return 1;
    }
}

public class Solution {
    public IList<IList<int>> KSmallestPairs(int[] nums1, int[] nums2, int k) {
        int n1 = Math.Min(nums1.Length,k);
        int n2 = Math.Min(nums2.Length,k);

        var pq = new PriorityQueue<Tuple<int,int,int>,int>(new Cmp());
        // var pq = new PriorityQueue<Tuple<int,int,int>,int>(Comparer<int>.Create((a,b) => b - a));

        for(int i = 0; i < n1; ++i) {
            for(int j = 0; j < n2; ++j) {
                int sum = nums1[i] + nums2[j];

                if( pq.Count < k ) {
                    pq.Enqueue(new Tuple<int,int,int>(nums1[i],nums2[j],sum),sum);
                } else if( sum < pq.Peek().Item3 ) {
                    pq.Dequeue();
                    pq.Enqueue(new Tuple<int,int,int>(nums1[i],nums2[j],sum),sum);
                } else {
                    break;
                }
            }
        }

        IList<IList<int>> ans = new List<IList<int>>();
        while( pq.Count > 0 ) {
            var p = new List<int>(2);
            p.Add(pq.Peek().Item1);
            p.Add(pq.Peek().Item2);
            ans.Add(p);
            pq.Dequeue();
        }

        return ans;
    }
}
