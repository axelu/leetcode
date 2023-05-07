
// 2498. Frog Jump II
// https://leetcode.com/problems/frog-jump-ii/



class Solution {
public:
    int maxJump(vector<int>& stones) {
        // stones is sorted in a strictly increasing order.
        // stones[0] == 0

        // cost of a path is the maximum length of a jump
        // we are looking for the minimum cost of a path
        // so ideally we could jump to every stone, but
        // because we need to jump back also, we will skip
        // every other stone in our forward jump to use them
        // when jumping back

        int n = stones.size();
        if( n == 2 )
            return stones[n-1];

        int mx = 0; // cout << mn << endl;
        for(int i = 2; i < n; i = i + 2) {
            mx = max(mx,stones[i] - stones[i-2]);

            if( i == n-1 ) {
                // we are at the last stone
                mx = max(mx,stones[n-1] - stones[n-2]);

                // jump back
                for(int j = n-4; j >= 0; --j) {
                    mx = max(mx,stones[j+2] - stones[j]);
                    if( j == 1 )
                        mx = max(mx,stones[1] - stones[0]);
                }

            } else if( i == n-2 ) {
                // the next stone is the last stone
                mx = max(mx,stones[n-1] - stones[n-2]);

                // jump back
                for(int j = n-3; j >= 0; --j) {
                    mx = max(mx,stones[j+2] - stones[j]);
                    if( j == 1 )
                        mx = max(mx,stones[1] - stones[0]);
                }
            }
        }

        return mx;
    }
};
