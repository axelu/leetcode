
// 870. Advantage Shuffle
// https://leetcode.com/problems/advantage-shuffle/
// day 24 March 2021 challenge
// https://leetcode.com/explore/featured/card/march-leetcoding-challenge-2021/591/week-4-march-22nd-march-28th/3683/



class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        int n = A.size(); // 1 <= A.length = B.length <= 10000

        sort(A.begin(),A.end());
        vector<int> ans(n,-1);

        vector<int>::iterator f;
        for(int i = 0; i < n; ++i) {
            f = upper_bound(A.begin(),A.end(),B[i]);
            if( f != A.end() ) {
                ans[i] = *f;
                A.erase(f);
            }
        }
        for(int i = 0; i < n; ++i) {
            if( ans[i] == -1 ) {
                ans[i] = *A.begin();
                A.erase(A.begin());
            }
        }

        return ans;
    }
};
