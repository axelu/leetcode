
// 1124. Longest Well-Performing Interval
// https://leetcode.com/problems/longest-well-performing-interval/



class Solution {
public:
    // longest well-performing interval (WPI)
    int longestWPI(vector<int>& hours) {
        int n = hours.size();

        int prefixSum[n+1];memset(prefixSum,0,sizeof prefixSum);
        int A[n]; // A[i] +1 or -1 corresponding to if hours[i] is > 8 or not

        int ans = 0;

        unordered_map<int,int> mp; // prefixSum,index when first seen
        mp.insert({0,0});

        int firstSeenIdx;
        for(int i = 0; i < n; ++i) {
            A[i] = hours[i] > 8 ? 1 : -1;
            prefixSum[i+1] = prefixSum[i] + A[i];

            if( prefixSum[i+1] > 0 ) {
                // number of days with hours > 8 is greater
                // than number of days with hours <= 8
                // because we are starting at prefixSum[0] = 0
                ans = i+1;

            } else {
                // have we seen prefixSum[i+1]-1 before?
                // it would have been inserted when we saw it the 1st time
                auto f = mp.find(prefixSum[i+1]-1);
                if( f != mp.end() )
                    ans = max(ans,i-f->second);

                mp.insert({prefixSum[i+1],i});
            }
        }

        return ans;
    }
};
