
// 1222. Queens That Can Attack the King
// https://leetcode.com/problems/queens-that-can-attack-the-king/




class Solution {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        int m = 8; // rows
        int n = 8; // cols
        int i;

        int queen[64];memset(queen,0,sizeof queen);
        for(i = 0; i < queens.size(); ++i)
            queen[queens[i][0]*n+queens[i][1]] = 1;

        // 8 directions, starting North, then clockwise
        int dirR[] = {-1,-1, 0, 1, 1, 1, 0,-1};
        int dirC[] = { 0, 1, 1, 1, 0,-1,-1,-1};

        vector<vector<int>> ans;

        // BFS
        queue<array<int,3>> q; // x,y,direction

        // seed the queue
        int x = king[0];
        int y = king[1];
        int x_new,y_new;
        for(i = 0; i < 8; ++i) {
            x_new = x + dirR[i];
            if( x_new < 0 || x_new == m ) continue;
            y_new = y + dirC[i];
            if( y_new < 0 || y_new == n ) continue;
            if( queen[x_new*n+y_new] ) ans.push_back({x_new,y_new});
            else q.push({x_new,y_new,i});
        }

        while( !q.empty() ) {
            x = q.front()[0];
            y = q.front()[1];
            i = q.front()[2];
            q.pop();
            x_new = x + dirR[i];
            if( x_new < 0 || x_new == m ) continue;
            y_new = y + dirC[i];
            if( y_new < 0 || y_new == n ) continue;
            if( queen[x_new*n+y_new] ) ans.push_back({x_new,y_new});
            else q.push({x_new,y_new,i});
        }

        return ans;
    }
};
