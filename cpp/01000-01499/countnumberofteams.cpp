
// 1395. Count Number of Teams
// https://leetcode.com/problems/count-number-of-teams/



class Solution {
public:
    int numTeams(vector<int>& rating) {
        int n = rating.size();
        int ans = 0;
        int i,j;

        int leftLessi,rightGreateri,leftGreateri,rightLessi;
        for(i = 1; i < n-1; ++i) {
            leftLessi     = 0;
            rightGreateri = 0;
            leftGreateri  = 0;
            rightLessi    = 0;

            // left side of i
            for(j = i-1; j >= 0; --j) {
                if( rating[j] < rating[i] ) ++leftLessi;
                else ++leftGreateri;
            }

            // right side of i
            for(j = i+1; j < n; ++j) {
                if( rating[j] > rating[i] ) ++rightGreateri;
                else ++rightLessi;

            }

            ans += leftLessi*rightGreateri + leftGreateri*rightLessi;
        }
        return ans;
    }
};
