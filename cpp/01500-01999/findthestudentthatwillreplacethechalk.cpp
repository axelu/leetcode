
// 1894. Find the Student that Will Replace the Chalk
// https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/


class Solution {
private:
    // binary search
    int search(long prefixSum[], int s, int e, long k) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);

        // pieces of chalk needed for student mid to finish
        long p = prefixSum[mid+1];

        if( p == k ) {
            // the next student will run out
            return mid+1;

        } else if( p > k ) {
            // we know the student at mid will run out,
            // but we may also have run out before
            // can we do better?
            int t = search(prefixSum,s,mid-1,k);
            return t == -1 ? mid : t;

        } else { // p < k
            return search(prefixSum,mid+1,e,k);
        }
    }

public:
    int chalkReplacer(vector<int>& chalk, int k) {
        int n = chalk.size();

        long prefixSum[n+1];
        prefixSum[0] = 0L;
        for(int i = 0; i < n; ++i)
            prefixSum[i+1] = prefixSum[i] + (long)chalk[i];

        long rem = (long)k % prefixSum[n];
        if( rem == 0L )
            return 0;

        return search(prefixSum,0,n-1,rem);
    }
};
