
// 2100. Find Good Days to Rob the Bank
// https://leetcode.com/problems/find-good-days-to-rob-the-bank/



class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int n = security.size();
        vector<int> ans;
        if( time == 0 ) {
            ans.resize(n);
            for(int i = 0; i < n; ++i)
                ans[i] = i;
            return ans;
        }

        if( n < 2*time+1 )
            return ans;

        // example
        // 0  1  2  3  4  5  6
        // 5  3  3  3  5  6  2      n=7
        // 0  1  2  3  0  0  1      lcnt
        // 0  4  3  2  1  0  0      rcnt

        // count from left and right
        int lcnt[n];
        lcnt[0] = 0;
        int rcnt[n];
        rcnt[n-1] = 0;
        for(int i = 1, j = n-2; i < n; ++i, --j) {
            lcnt[i] = security[i-1] >= security[i] ? lcnt[i-1]+1 : 0;
            rcnt[j] = security[j+1] >= security[j] ? rcnt[j+1]+1 : 0;
        }

        for(int i = 0; i < n; ++i)
           if( lcnt[i] >= time && rcnt[i] >= time )
               ans.push_back(i);

        return ans;
    }
};
