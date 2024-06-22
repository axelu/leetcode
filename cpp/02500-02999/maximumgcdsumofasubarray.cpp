
// 2941. Maximum GCD-Sum of a Subarray
// https://leetcode.com/problems/maximum-gcd-sum-of-a-subarray/




// resources
// https://www.geeksforgeeks.org/sparse-table/
// https://cp-algorithms.com/data_structures/sparse-table.html
// https://iq.opengenus.org/range-gcd-query-using-sparse-table/
// solution based on hints in the problem

class Solution {
private:
    // sparse table for GCD lookup [i,j] where i is starting index and 2^j is length inclusive
    int st[100000][17];
    long long prefixSum[100001];

    void buildSparseTable(vector<int>& nums, int n) {
        for(int i = 0; i < n; ++i)
            st[i][0] = nums[i];

        for(int j = 1; (1 << j) <= n; ++j) {
            // compute gcd for all intervals with size 2^j
            for(int i = 0; (i + (1 << j) - 1) < n; ++i) {
                int a = st[i][j - 1];
                int b = st[i + (1 << (j - 1))][j - 1];
                st[i][j] = gcd(a,b);
            }
        }

        return;
    }

    // range query GCD lookup using sparse table
    int query(int L, int R) {
        int j = (int)log2(R - L + 1);
        int a = st[L][j];
        int b = st[R - (1 << j) + 1][j];
        int g = gcd(a,b);
        // cout << "query L " << L << " R " << R << " result " << g << endl;
        return g;
    }

    void buildPrefixSum(vector<int>& nums, int n) {
        prefixSum[0] = 0LL;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + (long long)nums[i-1];
        return;
    }

    // binary search
    int search(int s, int e, int L, int target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        int _gcd = query(L,mid); // will never be greater than target
        if( _gcd == target) {
            // can we do better?
            int t = search(mid+1,e,L,target);
            return t != -1 ? t : mid;
        }

        return search(s,mid-1,L,target);
    }


public:
    long long maxGcdSum(vector<int>& nums, int k) {
        int n = nums.size();
        buildSparseTable(nums,n);
        buildPrefixSum(nums,n);

        long long ans = 0LL; // gcd sum
        long long s,g;

        for(int L = 0; L < n; ++L) {

            int target = nums[L];
            int R = search(L,n-1,L,target);
            // cout << "L " << L << " R " << R << endl;

            if( R-L+1 >= k) {
                s = prefixSum[R+1] - prefixSum[L];
                g = query(L,R);
                ans = max(ans, s * g);
            }

            while( ++R < n ) {
                target = query(L,R);
                R = search(R,n-1,L,target);

                if( R-L+1 >= k) {
                    s = prefixSum[R+1] - prefixSum[L];
                    g = query(L,R);
                    ans = max(ans, s * g);
                }
            }
        }

        return ans;
    }
};
