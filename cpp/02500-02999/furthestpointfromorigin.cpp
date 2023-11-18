
// 2833. Furthest Point From Origin
// https://leetcode.com/problems/furthest-point-from-origin/



class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int n = moves.size();

        int ans;

        // pass 1 interpret _ as right
        int cur = 0;
        for(int i = 0; i < n; ++i) {
            if( moves[i] == 'L' )
                --cur;
            else
                ++cur;
        }
        ans = abs(cur);

        // pass 2 interpret _ as left
        cur = 0;
        for(int i = 0; i < n; ++i) {
            if( moves[i] == 'L' || moves[i] == '_' )
                --cur;
            else
                ++cur;
        }
        ans = max(ans, abs(cur));

        return ans;
    }
};
