
// 1885. Count Pairs in Two Arrays
// https://leetcode.com/problems/count-pairs-in-two-arrays/



// https://leetcode.com/problems/create-sorted-array-through-instructions/
// https://www.topcoder.com/thrive/articles/Binary%20Indexed%20Trees

class Solution {
private:
    long tree[200001]; // Binary Indexed Tree (BIT) Fenwick Tree
    int mx = 200000;

    void update(int idx, long val) {
        while(idx <= mx) {
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }

    long q(int ind) { // query range [1, ind]
        long sum = 0;
        while(ind > 0) {
            sum += tree[ind];
            ind -= (ind & -ind);
        }
        return sum;
    }

public:
    long long countPairs(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(); // n == nums1.length == nums2.length

        // nums1[i] + nums1[j] > nums2[i] + nums2[j] transforms into
        // nums1[i] - nums2[i] > nums2[j] - nums1[j]
        // where i < j

        // 1 <= nums1[i], nums2[i] <= 10^5
        // with that our worst cases for difference are:
        // 1 - 10^5 = -99999 and 10^5 - 1 = 99999
        // we can use a Binary Indexed Tree (BIT) Fenwick Tree to
        // store the frequency of a given difference
        // we need an offset to have positive index

        memset(tree,0,sizeof tree);
        long offset = 100000;

        long ans = 0;

        long a,b;
        for(int i = n-2, j = n-1; i >= 0; --i,--j) {
            a = nums1[i] - nums2[i];
            b = nums2[j] - nums1[j];

            // insert b into our BIT
            // aka increase the frequency of b by 1
            update(b+offset,1L);

            // get cumulative frequency of differences smaller than a
            long t = q(a+offset-1);

            ans += t;
        }

        return ans;
    }
};

