
// 3771. Total Score of Dungeon Runs
// https://leetcode.com/problems/total-score-of-dungeon-runs/


class Solution {
private:
    // binary search
    int search(vector<int>& prefixSum, int i, int s, int e, int target) {
        // s and e are lengths
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        int sum = prefixSum[i+1] - prefixSum[i+1-mid];
        if( sum <= target ) {
            // can we do better?
            int t = search(prefixSum, i, mid+1, e, target);
            return t != -1 ? t : mid;
        }

        return search(prefixSum, i, s, mid-1, target);
    }

public:
    long long totalScore(int hp, vector<int>& damage, vector<int>& requirement) {
        int n = damage.size(); // 1 <= n <= 1e5; damage.len == requirement.len
        // 1 <= hp <= 1e9; 1 <= damage[i], requirement[i] <= 1e4

        // example
        // let hp = 20
        // index            0  1  2  3  4  5
        // damage           2  3  1  6  4  3
        // damage prefixSum 0  2  5  6 12 16 19
        // req                             3
        // hp - req                       17
        // let us assume we are at i = 5
        // how often will index 5 contribute a score?
        // as long as the sum of damages starting at i=5
        //    going left is <= hp-req[5] = 17
        // damage sum        19 17 24 13 7 3
        //                      ------------
        // index 5 will contribute 5
        // we can determine this via a binary search

        long long score = 0LL;

        vector<int> prefixSum(n+1, 0);
        for(int i = 0; i < n; ++i) {
            prefixSum[i+1] = prefixSum[i] + damage[i];

            int t = hp - requirement[i];
            if( t - damage[i] < 0 )
                continue;

            // our ans is between 1 and i+1
            int l = search(prefixSum, i, 1, i+1, t);
            // cout << "i " << i << " l " << l << endl;
            score += (long long)l;
        }

        return score;
    }
};
