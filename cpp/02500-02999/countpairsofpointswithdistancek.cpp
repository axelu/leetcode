
// 2857. Count Pairs of Points With Distance k
// https://leetcode.com/problems/count-pairs-of-points-with-distance-k/





class Solution {
public:
    int countPairs(vector<vector<int>>& coordinates, int k) {
        int n = coordinates.size();

        // distance between two points (x1,y1) and (x2,y2):
        // k = (x1 XOR x2) + (y1 XOR y2)
        //     -----------   -----------
        // k =      x      +      y         -> y = k - x
        // Note: in order for x + y to sum to k, we have [x,y] combination range from [0,k] to [k,0].
        // x = x1 XOR x2  ->  x2 = x XOR x1
        // y = y1 XOR y2  ->  y2 = y XOR y1
        //                         -
        //                    y2 = (k-x) XOR y1
        //                    x2 =    x  XOR x1
        // x can range between 0 and 100, so we could iterate reasonably over x

        int ans = 0;

        unordered_map<long,int> um; // key, count
        long key = ((long)coordinates[0][0]<<20) + coordinates[0][1];
        um[key] = 1;
        for(int i = 1; i < n; ++i) {
            long x2 = coordinates[i][0];
            int  y2 = coordinates[i][1];
            for(int x = 0; x <= k; ++x) {
                long x1 =    x  ^ x2;
                int  y1 = (k-x) ^ y2;

                key = (x1<<20) + y1;
                ans += um[key];
            }
            key = (x2<<20) + y2;
            ++um[key];
        }

        return ans;
    }
};
