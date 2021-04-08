
// 909. Snakes and Ladders
// https://leetcode.com/problems/snakes-and-ladders/



class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();

        int target = m*n;
        int seen[target]; memset(seen,0,sizeof seen);

        queue<pair<int,int>> q;
        q.push({1,0});
        seen[0] = 1;
        int idx,idx_new,move,i,j;
        while(!q.empty()) {
            idx  = q.front().first;
            move = q.front().second;
            q.pop();

            // cout << "idx     " << idx << endl;

            for(int k = 1; k <= 6; ++k) {
                idx_new = idx + k;
                // cout << "idx_new " << idx_new << endl;
                if( idx_new > target ) continue;

                // convert idx to board row and col
                i = (m-1)-((idx_new-1)/n);  // row
                j = (idx_new-1)%n;          // col
                if( ((m-1)-i) % 2 == 1 )    // odd row number distance from bottom row
                    j = (n-1)-j;            // adjust column for row numbering right to left

                // cout << "board " << i << " " << j << endl;

                if( board[i][j] != -1 ) {
                    idx_new = board[i][j];
                    // cout << "snake or ladder, new idx " << idx_new << endl;
                }

                if( idx_new == target ) return move+1;
                if( seen[idx_new-1] ) continue;
                seen[idx_new-1] = 1;
                q.push({idx_new,move+1});
            }
        }
        return -1;
    }
};
