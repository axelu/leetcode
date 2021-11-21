
// 407. Trapping Rain Water II
// https://leetcode.com/problems/trapping-rain-water-ii/



class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        int n = heightMap[0].size();
        if( m < 3 || n < 3 ) return 0;

        // worst case
        // 1 <= m, n <= 200
        // 0 <= heightMap[i][j] <= 2 * 10^4
        // edges all height of 20000, inside all at 0
        // 198*198*20000 = 784080000

        // directions
        int dirR[4] = {0,1,0,-1};
        int dirC[4] = {1,0,-1,0};

        int seen[m][n];memset(seen,0,sizeof seen);

        // prioritize water runners on the lowest height as water can only run down
        auto cmp = [](const array<int,3>& a, const array<int,3>& b) {
            return a[2] > b[2];
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp); // i,j,height

        // we start from the edges as water will spill from there
        int i,j;
        for(i = 0; i < m; ++i)
            for(j = 0; j < n; ++j)
                if( i == 0 || i == m-1 || j == 0 || j == n-1 ) {
                    pq.push({i,j,heightMap[i][j]});
                    seen[i][j] = 1;
                }

        int ans = 0;
        int i_new,j_new,h,k;
        while(!pq.empty()) {
            i = pq.top()[0];
            j = pq.top()[1];
            h = pq.top()[2];
            pq.pop();

            // explore all four directions
            for(k = 0; k < 4; ++k) {

                i_new = i+dirR[k];
                if( i_new < 0 || i_new >= m )
                    continue;

                j_new = j+dirC[k];
                if( j_new < 0 || j_new >= n )
                    continue;

                if( seen[i_new][j_new] )
                    continue;

                seen[i_new][j_new] = 1;

                if( heightMap[i_new][j_new] < h) {
                    // fill ajacent cell up to height of our current cell
                    ans += (h - heightMap[i_new][j_new]);
                    heightMap[i_new][j_new] = h;
                }
                pq.push({i_new,j_new,heightMap[i_new][j_new]});
            }

        }

        return ans;
    }
};
