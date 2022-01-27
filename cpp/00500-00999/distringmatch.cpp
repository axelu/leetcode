
// 942. DI String Match
// https://leetcode.com/problems/di-string-match/

class Solution {
public:
    vector<int> diStringMatch(string S) {
        int n = S.size();

        int i;
        deque<int> dq;
        for(int i = 0; i <= n; ++i) dq.push_back(i);

        vector<int> ans(n+1);
        for( i = 0; i < n; ++i)
            if( S[i] == 'I' ) {
                ans[i] = dq.front();
                dq.pop_front();
            } else {
                ans[i] = dq.back();
                dq.pop_back();
            }
        ans[n] = dq.front();
        return ans;
    }
};
