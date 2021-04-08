
// 1769. Minimum Number of Operations to Move All Balls to Each Box
// https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/




class Solution {
public:
    vector<int> minOperations(string boxes) {
        int n = boxes.size();
        vector<int> ans(n,0);
        if( n == 1 ) return ans;

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if( i == j ) continue;
                if( boxes[j] == '1' ) {
                    ans[i] += abs(i-j);
                }
            }
        }

        return ans;
    }
};
