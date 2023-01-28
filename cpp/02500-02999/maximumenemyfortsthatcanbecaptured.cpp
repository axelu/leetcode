
// 2511. Maximum Enemy Forts That Can Be Captured
// https://leetcode.com/problems/maximum-enemy-forts-that-can-be-captured/


class Solution {
public:
    int captureForts(vector<int>& forts) {
        // we are looking for the longest consecutive streak of 0s
        // that has a 1 to its left or right

        int n = forts.size();

        int ans = 0;

        int s = -1;
        for(int i = 1; i < n; ++i) {
            if( forts[i] == 0 ) {
                if( s == -1 )
                    s = i-1;
                continue;
            }
            if( s != -1 && forts[s] != 0 ) {
                if( (forts[i] == 1 && forts[s] == -1) ||
                    (forts[i] == -1 && forts[s] == 1) )
                    ans = max(ans,i-(s+1));
            }
            s = -1;
        }

        return ans;
    }
};
