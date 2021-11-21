
// 1854. Maximum Population Year
// https://leetcode.com/problems/maximum-population-year/



class Solution {
public:
    int maximumPopulation(vector<vector<int>>& logs) {
        // logs[i] = [birthi, deathi]
        // 1950 <= birthi < deathi <= 2050

        int cnt[101];memset(cnt,0,sizeof cnt);
        sort(logs.begin(),logs.end(),[](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] )
                    return true;
            }
            return false;
        });

        int ans = 0;
        int yr = 101;
        int j;
        for(int i = 0; i < logs.size(); ++i) {
            for(j = logs[i][0]-1950; j < logs[i][1]-1950; ++j) {
                ++cnt[j];
                if( cnt[j] > ans ) {
                    ans = cnt[j];
                    yr = j;
                } else if( cnt[j] == ans ) {
                    if( j < yr ) yr = j;
                }
            }
        }
        return yr+1950;
    }
};
