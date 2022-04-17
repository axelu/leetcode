
// 1712. Ways to Split Array Into Three Subarrays
// https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/



class Solution {
private:
    // binary search
    int search1(long prefixSum[], int s, int e, int i, long target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        long sum = prefixSum[mid+1] - prefixSum[i];

        if( sum >= target ) {
            // can we do better?
            int t = search1(prefixSum,s,mid-1,i,target);
            return t != -1 ? t : mid;
        } else {
            return search1(prefixSum,mid+1,e,i,target);
        }
    }

    // binary search
    int search2(long prefixSum[], int s, int e, int jl, int n) {
        //cout << "search2 s " << s << " e " << e << " jl " << jl << " n " << n << endl;
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        //cout << "  mid " << mid << endl;
        long sum_left  = prefixSum[mid+1] - prefixSum[jl]; // really sum_mid
        long sum_right = prefixSum[n] - prefixSum[mid+1];
        //cout << "  sum_left " << sum_left << " sum_right " << sum_right << endl;

        if( sum_left <= sum_right ) {
            // can we do better?
            int t = search2(prefixSum,mid+1,e,jl,n);
            return t != -1 ? t : mid;
        } else {
            return search2(prefixSum,s,mid-1,jl,n);
        }
    }

public:
    int waysToSplit(vector<int>& nums) {
        int n = nums.size();
        // cout << n << endl;

        long ans = 0L;

        long prefixSum[n+1];
        prefixSum[0] = 0L;
        for(int i = 0; i < n; ++i)
            prefixSum[i+1] = prefixSum[i] + (long)nums[i];

        long sum_left = 0L; // 0  ... i
        //long sum_mid;       // i+1... j
        //long sum_right;     // j+1... n-1

        // subarray left nums[0,i-1] inclusive
        for(int i = 0; i <= n-3; ++i) {
            sum_left += nums[i];

            // find the smallest index jl with i < jl <= n-2
            // where sum of elements between i and jl inclusive >= sum_left
            // sum_mid = prefixSum[jl+1] - prefixSum[i]
            long jl = search1(prefixSum,i+1,n-2,i+1,sum_left);
            if( jl == -1L )
                continue;

            // find the largest index jr with jl <= jr <= n-2
            // where sum[jl,jr] inclusive <= sum[jr+1,n]
            long jr = search2(prefixSum,jl,n-2,i+1,n);
            if( jr == -1L )
                continue;

            //cout << "i " << i << " jl " << jl << " jr " << jr << endl;
            ans = (ans + (jr-jl+1)) % 1000000007L;
        }

        return ans;
    }
};
