
// 276. Paint Fence
// https://leetcode.com/problems/paint-fence/submissions/


// approach per Solution #1
class Solution {
private:
    vector<int> mem;

    int totalWays(int posts, int k) {
        if( 1 == posts )
            return k;

        if( 2 == posts )
            return k * k;

        if( 0 == mem[posts-1] )
            mem[posts-1] = totalWays(posts-1,k);

        if( 0 == mem[posts-2] )
            mem[posts-2] = totalWays(posts-2,k);

        return (mem[posts-1] + mem[posts-2]) * (k-1);
    }
public:
    int numWays(int n, int k) {
        if( 0 == n ) return 0;
        mem = vector<int>(n+1);
        return totalWays(n,k);
    }
};
