
// 2657. Find the Prefix Common Array of Two Arrays
// https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/



class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size(); // A.size() == B.size()

        vector<int> ans(n);

        int t = 0;
        int cnt[n+1];memset(cnt,0,sizeof cnt);
        for(int i = 0; i < n; ++i) {
            ++cnt[A[i]];
            if( cnt[A[i]] == 2 )
                ++t;
            ++cnt[B[i]];
            if( cnt[B[i]] == 2 )
                ++t;
            ans[i] = t;
        }

        return ans;
    }
};
