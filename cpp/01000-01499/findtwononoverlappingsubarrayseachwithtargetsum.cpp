
// 1477. Find Two Non-overlapping Sub-arrays Each With Target Sum
// https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/






class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();

        // prefix: prefix[i] is the minimum length of sub-array that ends before i and has sum = k
        // nothing can end before index 0
        long prefix[n+1];
        prefix[0] = INT_MAX;

        int i = 0; // left index
        int j;
        int sum = 0;
        int mnLength = INT_MAX;
        for(j = 0; j < n; ++j) {
            sum += arr[j];
            // cout << "prefix i " << i << " j " << j << " sum " << sum << endl;

            if( sum < target ) {
                // cout << "sum < target" << endl;

                prefix[j+1] = mnLength;

                // expand sliding window
                continue;
            } else if( sum == target) {
                // cout << "sum == target" << endl;

                int length = j-i+1;
                mnLength = min(mnLength,length);
                prefix[j+1] = mnLength;

                //sum -= arr[i];
                //++i;
            } else {
                // sum > target
                // cout << "sum > target" << endl;

                // shrink the sliding window
                while( i < j && sum > target ) {
                    sum -= arr[i];
                    ++i;
                }
                if( sum == target) {
                    int length = j-i+1;
                    mnLength = min(mnLength,length);
                    prefix[j+1] = mnLength;
                } else {
                   prefix[j+1] = mnLength;
                }
            }
        }

        // debug print prefix
        /*
        for(i = 0; i < n; ++i) {
            cout << i << ":" << prefix[i] << " ";
        }
        cout << endl;
        */

        // suffix: suffix[i] is the minimum length of sub-array starting at or after i and has sum = k
        long suffix[n];
        suffix[n-1] = INT_MAX;

        j = n-1; // right index
        sum = 0;
        mnLength = INT_MAX;
        for(i = n-1; i >= 0; --i) {
            sum += arr[i];
            // cout << "suffic i " << i << " j " << j << " sum " << sum << endl;

            if( sum < target ) {
                // cout << "sum < target" << endl;

                suffix[i] = mnLength;

                // expand sliding window
                continue;
            } else if( sum == target) {
                // cout << "sum == target" << endl;

                int length = j-i+1;
                mnLength = min(mnLength,length);
                suffix[i] = mnLength;

                //sum -= arr[i];
                //++i;
            } else {
                // sum > target
                // cout << "sum > target" << endl;

                // shrink the sliding window
                while( j > i && sum > target ) {
                    sum -= arr[j];
                    --j;
                }
                if( sum == target) {
                    int length = j-i+1;
                    mnLength = min(mnLength,length);
                    suffix[i] = mnLength;
                } else {
                   suffix[i] = mnLength;
                }
            }
        }

        // debug print suffix
        /*
        for(i = 0; i < n; ++i) {
            cout << i << ":" << suffix[i] << " ";
        }
        cout << endl;
        */

        long ans = LONG_MAX;
        for(i = 0; i < n; ++i) {
            ans = min(ans,prefix[i]+suffix[i]);
        }

        return ans > INT_MAX ? -1 : ans;
    }
};
