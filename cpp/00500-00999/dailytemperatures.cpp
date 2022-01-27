
// 739. Daily Temperatures
// https://leetcode.com/problems/daily-temperatures/





class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int n = T.size();
        vector<int> ans(n,0);
        if( n == 1 ) return ans;

        stack<array<int,2>> stck;
        stck.push({T[n-1],n-1});
        int i,k;
        for(i = n-2; i >= 0; --i) {
            k = 0;
            while( !stck.empty() ) {
                if( stck.top()[0] <= T[i] ) {
                    stck.pop();
                } else {
                    k = stck.top()[1]-i;
                    break;
                }
            }
            ans[i] = k;
            stck.push({T[i],i});
        }

        return ans;
    }
};
