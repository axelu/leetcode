
// 723. Candy Crush
// https://leetcode.com/problems/candy-crush/





class Solution {
private:
    int m,n;

    int seenV[2500];
    int seenH[2500];
    int added[2500];
    queue<pair<int,int>> toBeCrushed;
    stack<pair<int,int>> stck;
    stack<int> stckg;

    int crush(vector<vector<int>>& board) {

        memset(seenV,0,sizeof seenV);
        memset(seenH,0,sizeof seenH);
        memset(added,0,sizeof added);

        int r,c,seenIdx;
        bool flag;
        for(int i = 0; i < m; ++i) {                // row
            for(int j = 0; j < n; ++j) {            // col
                if( board[i][j] == 0 ) continue;
                // explore down aka vertically
                seenIdx = i*n+j;
                if( !seenV[seenIdx] ) {
                    flag = false;
                    stck.push({i,j});
                    r = i+1;
                    while( r < m && board[r][j] == board[i][j] ) {
                        stck.push({r,j});
                        ++r;
                    }
                    if( stck.size() >= 3 ) flag = true;
                    while( !stck.empty() ) {
                        if( flag ) {
                            toBeCrushed.push(stck.top());
                            seenIdx = stck.top().first*n+stck.top().second;
                            seenV[seenIdx] = 1;
                            added[seenIdx] = 1;
                        }
                        stck.pop();
                    }
                }
                // explore left aka horizontally
                seenIdx = i*n+j;
                if( !seenH[seenIdx] ) {
                    flag = false;
                    stck.push({i,j});
                    c = j+1;
                    while( c < n && board[i][c] == board[i][j] ) {
                        stck.push({i,c});
                        ++c;
                    }
                    if( stck.size() >= 3 ) flag = true;
                    while( !stck.empty() ) {
                        if( flag ) {
                            seenIdx = stck.top().first*n+stck.top().second;
                            if( !added[seenIdx] ) toBeCrushed.push(stck.top());
                            seenH[seenIdx] = 1;
                        }
                        stck.pop();
                    }
                }
            }
        }

        // crush
        int crushed = toBeCrushed.size();
        while(!toBeCrushed.empty()) {
            board[toBeCrushed.front().first][toBeCrushed.front().second] = 0;
            toBeCrushed.pop();
        }
        return crushed;
    }

    void gravity(vector<vector<int>>& board) {

        int i;
        for(int j = 0; j < n; ++j) {            // col
            for(i = 0; i < m; ++i) {            // row
                if( board[i][j] != 0 ) stckg.push(board[i][j]);
                board[i][j] = 0;
            }
            i = m-1;
            while(!stckg.empty()) {
                board[i][j] = stckg.top();
                stckg.pop();
                --i;
            }
        }
    }


public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        m = board.size();    // rows
        n = board[0].size(); // cols

        while(crush(board)>0) gravity(board);
        return board;
    }
};
