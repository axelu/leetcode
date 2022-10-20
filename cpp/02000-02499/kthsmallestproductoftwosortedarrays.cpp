
// 2040. Kth Smallest Product of Two Sorted Arrays
// https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/





//         nums1    nums2
// case1  - ... -  - ... - unique
// case2  - ... -  - ... +
// case3  - ... -  + ... +
// case4  - ... +  - ... - same as 2
// case5  - ... +  - ... +
// case6  - ... +  + ... +
// case7  + ... +  - ... - same as 3
// case8  + ... +  - ... + same as 6
// case9  + ... +  + ... + unique

// Note: because it is a product, nums1 and nums2 can be swapped
//       hence the unique use cases are really:
//        - ... -  - ... -

//        + ... +  + ... +
//        - ... -  + ... +

//        - ... +  + ... +

//        - ... +  - ... +
//        - ... -  - ... +

class Solution {
private:
    // binary search
    int search1(vector<int>& nums, int s, int e, long long f, long long target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        long long res = f * nums[mid];
        if( res <= target ) {
            // can we do better?
            int t;
            if( f >= 0 )
                t = search1(nums,mid+1,e,f,target);
            else
                t = search1(nums,s,mid-1,f,target);
            return t != -1 ? t : mid;
        }
        if( f >= 0 )
            return search1(nums,s,mid-1,f,target);
        else
            return search1(nums,mid+1,e,f,target);
    }

    pair<long long,long long> solve1(vector<int>& nums1, int n, vector<int>& nums2, int m, long long target) {
        long long cnt = 0;
        long long mx = LLONG_MIN;
        for(int i = 0; i < n; ++i) {
            long long f = nums1[i];
            // binary search in nums2
            int j = search1(nums2,0,m-1,f,target);
            if( j == -1 )
                continue;

            if( f >= 0 )
                cnt += j+1;
            else
                cnt += (m-j);
            mx = max(mx, f * nums2[j]);
        }
        return {cnt,mx};
    }

    long long search0(long long s, long long e, long long k, vector<int>& nums1, int n, vector<int>& nums2, int m) {
        // cout << "search0 s " << s << " e " << e << endl;
        if( s > e )
            return LLONG_MIN;

        long long mid = s + ((e-s)/2);
        auto[cnt,p] = solve1(nums1,n,nums2,m,mid);
        // cout << "mid " << mid << " cnt " << cnt << " p " << p << endl;
        if( cnt == k ) {
            return p;
        } else if( cnt > k ) {
            // p could actually be our answer
            long long t = search0(s,p-1,k,nums1,n,nums2,m);
            return t != LLONG_MIN ? t : p;
        }

        return search0(mid+1,e,k,nums1,n,nums2,m);
    }

public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        int n = nums1.size();
        int m = nums2.size();

        // debug
        //cout << search1(nums2,0,m-1,-2,-6) << endl;
        //return 99;

        long long a = (long)nums1[0]   * nums2[0];
        long long b = (long)nums1[n-1] * nums2[m-1];
        long long c = (long)nums1[0]   * nums2[m-1];
        long long d = (long)nums2[0]   * nums1[n-1];

        long long s = min({a,b,c,d});
        long long e = max({a,b,c,d});
        return search0(s,e,k,nums1,n,nums2,m);
    }
};
