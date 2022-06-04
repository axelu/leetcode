
// 1802. Maximum Value at a Given Index in a Bounded Array
// https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/



class Solution {
private:
    long minfill(long k, long l) {
        long sum = 0;
        for(; l > 0 && k > 1; --l, --k) {
            sum += k;
        }
        return sum + l;
    }

    // binary search
    int search(int s, int e, int n, int index, int maxSum) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        // total = sum_left + mid + sum_right
        // we will calculate the minimum sum by filling left and right optimally
        long sum_left  = minfill(mid-1,index);
        long sum_right = minfill(mid-1,n-index-1);
        if( sum_left + mid + sum_right <= (long)maxSum ) {
            // can we do better?
            int t = search(mid+1,e,n,index,maxSum);
            return t != -1 ? t : mid;
        } else {
            return search(s,mid-1,n,index,maxSum);
        }
    }

public:
    int maxValue(int n, int index, int maxSum) {
        // determine max
        long sum = 0;
        long i = 1;
        while( sum < maxSum && i < n )
            sum += i++;

        int mx = sum >= maxSum ? i : i + (maxSum-sum)/n;

        return search(0,mx,n,index,maxSum);
    }
};
