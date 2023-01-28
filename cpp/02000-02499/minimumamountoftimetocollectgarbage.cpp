
// 2391. Minimum Amount of Time to Collect Garbage
// https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage/




class Solution {
public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        int n = garbage.size();

        int mx_m = -1; // max house index at which there is metal garbage
        int mx_p = -1; // max house index at which there is paper garbage
        int mx_g = -1; // max house index at which there is glass garbage

        int tt[n]; tt[0] = 0; // travel time to house i

        int m = 0, p = 0, g = 0; // running sum of metal, paper, glass
        for(int i = 0; i < n; ++i) {

            // how much if any of each garbage at current house
            for(char c: garbage[i] )
                if( c == 'M' ) {
                    ++m;
                    mx_m = i;
                } else if( c == 'P' ) {
                    ++p;
                    mx_p = i;
                } else { // c == 'G'
                    ++g;
                    mx_g = i;
                }

            if( i > 0 )
                tt[i] = tt[i-1] + travel[i-1]; // travel time to house i
        }

        int ans = 0;
        if( mx_m != -1 )
            ans += tt[mx_m] + m;
        if( mx_p != -1 )
            ans += tt[mx_p] + p;
         if( mx_g != -1 )
            ans += tt[mx_g] + g;

        return ans;
    }
};
