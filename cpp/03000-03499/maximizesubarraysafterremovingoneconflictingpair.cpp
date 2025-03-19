
// 3480. Maximize Subarrays After Removing One Conflicting Pair
// https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/




class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        int conflictingPairs_sz = conflictingPairs.size();

        // pass 1 - swap pair values if needed
        for(auto& pair: conflictingPairs)
            if( pair[0] > pair[1] ) {
                int t = pair[1];
                pair[1] = pair[0];
                pair[0] = t;
            }

        // sort conflicting pairs by end index, then by begin index
        sort(conflictingPairs.begin(), conflictingPairs.end(), [](const vector<int>& a, const vector<int>& b){
            if( a[1] < b[1] ) {
                return true;
            } else if( a[1] == b[1] ) {
                if( a[0] < b[0] ) {
                    return true;
                }
            }
            return false;
        });

        // debug
        /*
        for(int i = 0; i < conflictingPairs_sz; ++i)
            cout << conflictingPairs[i][0] << "," << conflictingPairs[i][1] << " ";
        cout << endl;
        */

        long long ans = 0LL;

        // we will go from left to right through nums -> 1...n, let that be j
        // we will make valid subarrays from the lowest possible index i to j
        // at every step j we will keep track of the most restrictive i and
        // the second most restrictive i and which conflicting pair it came from
        // we then track for each conflicting pair the sum of gain if removed

        vector<long long> gains(conflictingPairs_sz, 0LL);
        int conflictingPairs_idx = 0;
        pair<int,int> maxmaxi = {0, -1}; // most restrictive aka max i
        pair<int,int> maxi    = {0, -1}; // second most restrictive i
        for(int j = 1; j <= n; ++j) {    // index in nums

            // we make valid subarrays ENDING at j
            // what is the lowest valid index our subarray can start? let that index be i

            while( conflictingPairs_idx < conflictingPairs_sz && conflictingPairs[conflictingPairs_idx][1] <= j ) {
                int i = conflictingPairs[conflictingPairs_idx][0];
                if( i >= maxmaxi.first ) {
                    maxi = maxmaxi;
                    maxmaxi = {i, conflictingPairs_idx};
                } else if( i >= maxi.first ) {
                    maxi = {i, conflictingPairs_idx};
                }
                ++conflictingPairs_idx;
            }

            // cout << "j " << j << " conflictingPairs_idx-1 " << conflictingPairs_idx-1 << endl;
            // cout << "    maxmaxi " << maxmaxi.first << " maxi " << maxi.first << endl;

            ans += (long long)(j - maxmaxi.first);

            if( maxmaxi.second >= 0 ) {
                // what  if we removed the most restrictive conflicting pair?
                // conflicting pair index = maxmaxi.second

                long long gain = maxmaxi.first - maxi.first;
                gains[maxmaxi.second] += gain;
            }
        }

        long long mxgain = 0LL;
        for(int i = 0; i < conflictingPairs_sz; ++i)
            mxgain = max(mxgain, gains[i]);

        // cout << "ans " << ans << endl;
        // cout << "mxgain " << mxgain << endl;

        return ans + mxgain;
    }
};
