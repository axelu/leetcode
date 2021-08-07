
// 1301. Number of Paths with Max Score
// https://leetcode.com/problems/number-of-paths-with-max-score/





class Solution {
private:
    int t;
    long MOD = 1000000007;

    // directions UP, LEFT or UP-LEFT (diagonally)
    int dirR[3] = {-1, 0,-1};
    int dirC[3] = { 0,-1,-1};


    pair<int,int> rec(vector<string>& board, int i, int j, int length[], int cnt[]) {
        // returns max distance to node 0 or -1 if no path to node 0
        // returns count of possible path to node 0
        // {dist,cnt}

        if( i == 0 && j == 0 )
            return {0,1};

        int idx = i*t+j;
        if( length[idx] != -2 )
            return {length[idx],cnt[idx]};


        int ret = -1;

        // we have a choice

        // explore all three directions
        int i_new,j_new,d;
        pair<int,int> res[3] = {{-1,-1},{-1,-1},{-1,-1}};
        long c;
        for(int k = 0; k < 3; ++k) {

            i_new = i + dirR[k];
            if( i_new < 0 || i_new >= t )
                continue;

            j_new = j + dirC[k];
            if( j_new < 0 || j_new >= t )
                continue;

            if( board[i_new][j_new] == 'X' )
                continue;

            pair<int,int> p = rec(board,i_new,j_new,length,cnt);
            d = p.first;
            c = p.second;
            if( d != -1 ) {
                d += board[i_new][j_new] == 'E' ? 0 : board[i_new][j_new]-48;
                ret = max(ret,d);
                res[k].first  = d;
                res[k].second = c;
            }

        }

        c = 0;
        if( ret != -1 ) {
            if( res[0].first == ret )
                c = (c + res[0].second) % MOD;
            if( res[1].first == ret )
                c = (c + res[1].second) % MOD;
            if( res[2].first == ret )
                c = (c + res[2].second) % MOD;

            length[idx] = ret;
            cnt[idx] = c;
            return {length[idx],cnt[idx]};
        }

        length[idx] = -1;
        cnt[idx] = -1;
        return {-1,-1};
    }




public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        t = board.size();   // 2 <= board.length == board[i].length <= 100
        int n = t*t;        // number nodes

        int length[n]; // holds the max path length from node i to node n-1
        int cnt[n];    // holds the number of path with max length from node i to node n-1
        for(int i = 0; i < n; ++i)
            length[i] = -2; // -2 signals not seen!

        pair<int,int> p = rec(board,t-1,t-1,length,cnt);
        if( p.first == -1 )
            return {0,0};
        else
            return {p.first,p.second};
    }
};
