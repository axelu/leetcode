
// 2184. Number of Ways to Build Sturdy Brick Wall
// https://leetcode.com/problems/number-of-ways-to-build-sturdy-brick-wall/



/*
 * possible wall configurations represented as bitmask
 * example wall width = 10
 * lets say our brick with is 2
 * 0  1  2  3  4  5  6  7  8  9  10
 * |     |     |     |     |     |
 *    0  1  2  3  4  5  6  7  8       bit (from right)
 *    0  1  0  1  0  1  0  1  0       bitmask
 */
class Solution {
private:
    // debug
    void printBinary(int x) {
        for(int i = 8; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }

    void solve(vector<int>& bricks, int width, int i, int& mask, vector<int>& c) {
        if( i == width ) {
            c.push_back(mask);
            return;
        }

        if( i > 0 )
            mask |= 1 << (i-1);

        // we have a choice
        // use a brick that fits from the list of possible bricks
        for(int k = 0; k < bricks.size(); ++k) {
            int w = bricks[k]; // width of current brick
            if( i + w <= width )
                solve(bricks,width,i+w,mask,c);
        }

        // backtrack
        if( i > 0 )
            mask &= ~(1 << (i-1));
    }

public:
    int buildWall(int height, int width, vector<int>& bricks) {
        // remove any bricks wider than our wall
        for(auto it = bricks.begin(); it != bricks.end(); )
            if( *it > width )
                it = bricks.erase(it);
            else
                ++it;

        int n = bricks.size();
        if( n == 0 )
            return 0;

        // sort(bricks.begin(),bricks.end());

        // get all possible 1-height wall configurations
        vector<int> c;
        int mask = 0;
        solve(bricks,width,0,mask,c);

        int wall_sz = c.size();
        if( wall_sz == 0 )
            return 0;
        if( height == 1 )
            return wall_sz;


        // for each wall config, construct the list of competitve walls
        vector<vector<int>> comp(wall_sz);
        for(int i = 0; i < wall_sz; ++i) {
            for(int j = 0; j < wall_sz; ++j) {
                if( c[i] & c[j] ) // walls have a brick seem in the same position
                    continue;
                comp[i].push_back(j);
            }
        }

        long mod = 1000000007;

        // bottom up
        // let dp[wall][k] be the number of wall configurations
        //                 with wall being the configuration in row k
        long dp[wall_sz][height];
        for(int i = 0; i < wall_sz; ++i)
            dp[i][0] = 1;

        for(int k = 1; k < height; ++k) {           // row
            for(int i = 0; i < wall_sz; ++i) {      // wall
                long t = 0;
                for(int j = 0; j < comp[i].size(); ++j)
                    t = (t + dp[comp[i][j]][k-1]) % mod;
                dp[i][k] = t;
            }
        }

        long ans = 0;
        for(int i = 0; i < wall_sz; ++i)
            ans = (ans + dp[i][height-1]) % mod;

        return ans;
    }
};
