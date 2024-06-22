
// 3015. Count the Number of Houses at a Certain Distance I
// https://leetcode.com/problems/count-the-number-of-houses-at-a-certain-distance-i/




class Solution {
public:
    vector<int> countOfPairs(int n, int x, int y) {
        // 2 <= n <= 100 -> small constraint, use Floyd-Warshall

        // initialize our distance matrix (1-indexed) considering that
        // there is a connection from house i with the house i + 1 for all 1 <= i <= n - 1
        int dist[n+1][n+1];memset(dist,0,sizeof dist);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j) {
                if( i > j )
                    dist[i][j] = i - j;
                else if( i < j )
                    dist[i][j] = j - i;
            }

        // preconstruct our answer
        vector<int> ans(n);
        for(int i = 0, x = (n-1) * 2; i < n; ++i, x -= 2)
            ans[i] = x;

        // if x != y add our one extra edge and run Floyd-Warshall
        if( x != y ) {
            // current distance x y
            int t = dist[x][y];
            ans[t-1] -= 2; // adjust answer
            dist[x][y] = 1;
            dist[y][x] = 1;
            ans[0] += 2; // adjust answer

            for(int k = 1; k <= n; ++k)
                for(int i = 1; i <= n; ++i)
                    for(int j = 1; j <= n; ++j)
                        if( dist[i][j] > dist[i][k] + dist[k][j] ) {
                            //cout << "cur dist[" << i << "][" << j << "] " << dist[i][j] << endl;
                            //cout << "new dist[" << i << "][" << j << "] " << dist[i][k] + dist[k][j] << " ";
                            //cout << "dist[" << i << "][" << k << "] " << dist[i][k] << " + " << "dist[" << k << "][" << j << "] " << dist[k][j] << endl;
                            --ans[dist[i][j]-1]; // adjust answer
                            dist[i][j] = dist[i][k] + dist[k][j];
                            ++ans[dist[i][j]-1]; // adjust answer
                        }
        }


        return ans;
    }
};
