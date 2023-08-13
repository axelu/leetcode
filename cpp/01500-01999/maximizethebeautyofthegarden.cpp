
// 1788. Maximize the Beauty of the Garden
// https://leetcode.com/problems/maximize-the-beauty-of-the-garden/





class Solution {
public:
    int maximumBeauty(vector<int>& flowers) {
        int n = flowers.size();

        int prefixSum[n+1];
        prefixSum[0] = 0;

        unordered_map<int,int> last; // val, max idx
        for(int i = 1; i <= n; ++i) {
            last[flowers[i-1]] = i-1;
            if( flowers[i-1] > 0 )
                prefixSum[i] = prefixSum[i-1] + flowers[i-1];
            else
                prefixSum[i] = prefixSum[i-1];
        }

        unordered_set<int> seen;
        int ans = INT_MIN;
        for(int i = 0; i < n-1; ++i) {
            auto p = seen.insert(flowers[i]);
            if( p.second ) {
                int j = last[flowers[i]];
                int l = j-i-1;
                if( l >= 0 ) {
                    int t = 2 * flowers[i];
                    if( l > 0 )
                        t += prefixSum[j] - prefixSum[i+1];
                    ans = max(ans,t);
                }
            }
        }

        return ans;
    }
};
