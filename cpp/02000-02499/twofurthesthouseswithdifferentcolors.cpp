
// 2078. Two Furthest Houses With Different Colors
// https://leetcode.com/problems/two-furthest-houses-with-different-colors/




class Solution {
public:
    int maxDistance(vector<int>& colors) {
        int n = colors.size();

        int fstSeen[101];memset(fstSeen,-1,sizeof fstSeen);
        int lstSeen[101];

        int color;
        for(int i = 0; i < n; ++i) {
            color = colors[i];
            if( fstSeen[color] == -1 )
                fstSeen[color] = i;

            lstSeen[color] = i;
        }

        int ans = 0;
        int l,r;
        for(int i = 0; i < 101; ++i) {
            if( fstSeen[i] == -1 )
                continue;
            r = lstSeen[i];

            for(int j = 0; j < 101; ++j) {
                if( j == i || fstSeen[j] == -1 )
                    continue;
                l = fstSeen[j];
                ans = max(ans,abs(r-l));
            }
        }

        return ans;
    }
};
