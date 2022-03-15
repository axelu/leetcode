
// 2086. Minimum Number of Buckets Required to Collect Rainwater from Houses
// https://leetcode.com/problems/minimum-number-of-buckets-required-to-collect-rainwater-from-houses/



class Solution {
public:
    int minimumBuckets(string street) {
        int n = street.size();

        if( n == 1 )
            return street[0] == '.' ? 0 : -1;

        int ans = 0;
        int lb = -1; // index of last bucket placed
        for(int i = 1; i < n; ++i) {
            if( i == 1 ) {
                if( street[0] == 'H' && street[1] == 'H' ) {
                    return -1;
                } else if( street[0] == 'H' ) {
                    lb = 1;
                    ++ans;
                } else if( street[1] == 'H' ) {
                    if( n >= 3 ) {
                        if( street[2] == 'H' ) {
                            lb = 0;
                        } else {
                            lb = 2;
                        }
                    }
                    ++ans;
                }
            } else if( i == n-1 ) {
                // the bucket can only go at i-1
                if( street[i] == 'H' && street[i-1] == 'H' ) {
                    return -1;
                } else if( street[i] == 'H' && lb != i-1 )
                    ++ans;
            } else if( street[i] == 'H' ) {
                // we have to place a bucket
                // either at i-1 or i+1
                // we prefer to place the bucket at i+1 (greedy)
                // unless we already placed a bucket at i-1
                if( street[i-1] == 'H' && street[i+1] == 'H' ) {
                    return -1;
                } else if( street[i-1] == '.' && lb == i-1 ) {
                    // do nothing
                } else if( street[i+1] == '.' ) {
                    lb = i+1;
                    ++ans;
                } else {
                    lb == i-1;
                    ++ans;
                }
            }
        }

        return ans;
    }
};
