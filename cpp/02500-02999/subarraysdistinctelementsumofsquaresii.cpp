
// 2916. Subarrays Distinct Element Sum of Squares II
// https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-ii/




/* for brute force implementation see
   2913. Subarrays Distinct Element Sum of Squares I
   https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-i/

   here the contraints are too big, so need to find another approach
                  0  1  2  3  4
   example array [1, 7, 2, 3, 7]
   assume we are at index 3
                           - subarray[3,3] 1 unique digit
                        ---- subarray[2,3] 2 unique digit
                     ------- subarray[1,3] 3 unique digit
                   --------- subarray[0,3] 4 unique digit
   shown differently counting from index 3 to the left
                  4  3  2  1 unique digit(s) counting from index 3; sum unique digits 10
                 16  9  4  1 squares of unique digit(s), squares sum 30
   now we proceed from index 3 to index 4
                  4  3  2  1     unique digit(s) counting from index 3 for compare
                  4  3  3  2  1  unique digit(s) counting from index 4
                        ----
   we can only increase the count till we hit the same digit to our left
   our new index always accounts for plus 1
   the question becomes: how can we calculate our sum of squares at index 4?

   if we have a given value a and add to it and square it:
   (a+1) * (a+1) = (a*a) + 1*a + 1*a + 1*1 = (a*a) + 2a + 1
   lets extend that to two values, aka our sum of squares:
   (a+1) * (a+1) + (b+1) * (b+1) =
        (a*a) + 2a + 1 + (b*b) + 2b + 1 => ((a*a) + (b*b)) + 2*(a+b) + 2
                                           ---------------      ---    -
                                            squares sum         sum    number of indicies we are increasing
    taking our example from above:
    sum uniqe digtes at index 3 = 10
    squares sum at index 3      = 30
    now going to index 4 increasing 2 indices (index 2 and index 3)  with a unique digit sum of 3 by one
    we can calculate our new square sum at index 4 as follows:
    30 + 2 * (2+1) + 2 = 38; we need to add one more as our new index will always be 1

    using a segment tree while we go from left to right we can easily get a range sum
    as well as update (add) to a range
    or we could use a binary indexed tree to do the same

 */
class Solution {
private:
    long const mod = 1000000007;
    int last_seen[100001]; // rightmost index we have seen a given value

    long t[400000]; // segment tree (sum), lazy propagation, range addition, range query
    long lazy[400000];

    void push(int v) {
        lazy[v*2] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0;
    }

    // range addition
    void update(int v, int tl, int tr, int l, int r, int addend) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            lazy[v] += addend;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), addend);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = query(v*2, tl, tm, tl, tm) + query(v*2+1, tm+1, tr, tm+1, tr);
        }
    }

    // get sum
    long query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && tr == r)
            return (t[v] + ((1 + tr - tl) * lazy[v])) % mod;
        int tm = (tl + tr) / 2;
        return (1 + r - l) * lazy[v] +
               query(v*2, tl, tm, l, min(r, tm)) +
               query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 100000; 1 <= nums[i] <= 100000
        if( n == 1 )
            return 1;

        // init segment tree, all values initially 0
        memset(t,0,sizeof t);
        memset(lazy,0,sizeof lazy);

        long ans = 1L;

        long square_sum = 1L;
        memset(last_seen,-1,sizeof last_seen);
        last_seen[nums[0]] = 0;
        update(1, 0, n-1, 0, 0, 1);
        for(int i = 1; i < n; ++i) {
            int x = nums[i];

            int l = last_seen[x] + 1;
            long sum = query(1, 0, n-1, l, i-1);
            square_sum = (square_sum + (2L * sum) + (long)(i-l) + 1L) % mod;

            ans = (ans + square_sum) % mod;

            update(1, 0, n-1, l, i, 1);
            last_seen[x] = i;
        }

        return ans;
    }
};
