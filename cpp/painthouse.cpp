
// 256. Paint House
// https://leetcode.com/problems/paint-house/



class Solution {
private:
    size_t N;
    int mem[101][3];

    int minCost(vector<vector<int>>& costs, int idx, int notColor) {
        if( N-1 == idx ) {
            if( 0 == notColor )
                return min(costs[idx][1],costs[idx][2]);
            else if( 1 == notColor )
                return min(costs[idx][0],costs[idx][2]);
            else
                return min(costs[idx][0],costs[idx][1]);
        }

        int colorA,colorB;
        if( 0 == notColor ) {
            // i can be painted either color 1 or color 2
            if( mem[idx][1] != -1 ) {
                colorA = mem[idx][1];
            } else {
                colorA = costs[idx][1] + minCost(costs,idx+1,1);
                mem[idx][1] = colorA;
            }
            if( mem[idx][2] != -1 ) {
                colorB = mem[idx][2];
            } else {
                colorB = costs[idx][2] + minCost(costs,idx+1,2);
                mem[idx][2] = colorB;
            }
        } else if( 1 == notColor ) {
            // i can be painted either color 0 or color 2
            if( mem[idx][0] != -1 ) {
                colorA = mem[idx][0];
            } else {
                colorA = costs[idx][0] + minCost(costs,idx+1,0);
                mem[idx][0] = colorA;
            }
            if( mem[idx][2] != -1 ) {
                colorB = mem[idx][2];
            } else {
                colorB = costs[idx][2] + minCost(costs,idx+1,2);
                mem[idx][2] = colorB;
            }
        } else {
            // i can be painted either color 0 or color 1
            if( mem[idx][0] != -1 ) {
                colorA = mem[idx][0];
            } else {
                colorA = costs[idx][0] + minCost(costs,idx+1,0);
                mem[idx][0] = colorA;
            }
            if( mem[idx][1] != -1 ) {
                colorB = mem[idx][1];
            } else {
                colorB = costs[idx][1] + minCost(costs,idx+1,1);
                mem[idx][1] = colorB;
            }
        }
        return min(colorA,colorB);
    }

public:
    int minCost(vector<vector<int>>& costs) {
        N = costs.size();
        if( 0 == N )
            return 0;
        if( 1 == N )
            return min({costs[0][0],costs[0][1],costs[0][2]});

        for(int i = 0; i < N; ++i) {
            mem[i][0] = -1;
            mem[i][1] = -1;
            mem[i][2] = -1;
        }

        minCost(costs,0,0);minCost(costs,0,1);minCost(costs,0,2);
        return min({mem[0][0],mem[0][1],mem[0][2]});
    }
};
