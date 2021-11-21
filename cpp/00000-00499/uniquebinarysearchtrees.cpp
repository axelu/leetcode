
// 96. Unique Binary Search Trees
// https://leetcode.com/problems/unique-binary-search-trees/
// Catalan number

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int numTrees(int n) {

        // dynamic programming
        vector<int> dp(n + 1, 0);

        dp[0] = 1; // so we calculate correctly if no nodes on a given side
        dp[1] = 1;

        for (int i = 2; i <= n; ++i)
            for (int k = 1; k <= i; ++k)
                dp[i] += dp[k - 1] * dp[i - k];

        return dp[n];
    }
};

int main() {

    Solution s;

    cout << s.numTrees(8) << endl;


    return 0;
}
