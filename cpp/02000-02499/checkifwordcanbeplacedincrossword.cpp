
// 2018. Check if Word Can Be Placed In Crossword
// https://leetcode.com/problems/check-if-word-can-be-placed-in-crossword/




class Solution {
public:
    bool placeWordInCrossword(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        int word_sz = word.size();

        // brute force

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                // cout << "i " << i << " j " << j << endl;

                if( board[i][j] == '#' )
                    continue;

                // our current cell is either empty or a char

                // if we are at column 0 OR
                //    if left of us is a blocked cell and we are far enough from the right end that word could fit
                //    then we try to place word horizontally left to right
                if( j == 0 || (board[i][j-1] == '#' && n-j >= word_sz) ) {
                    int ci = j, wi = 0;
                    for(; wi < word_sz && ci < n; ++ci, ++wi)
                        if( board[i][ci] == '#' || (board[i][ci] != ' ' && board[i][ci] != word[wi]) )
                            break;
                    if( wi == word_sz && ( ci == n || board[i][ci] == '#') )
                        return true;
                }

                // if we are at column n-1 OR
                //    if right of us is a blocked cell and we are far enough from the left end that word could fit
                //    then we try to place word right to left
                if( j == n-1 || (board[i][j+1] == '#' && j+1 >= word_sz) ) {
                    int ci = j, wi = 0;
                    for(; wi < word_sz && ci >= 0; --ci, ++wi)
                        if( board[i][ci] == '#' || (board[i][ci] != ' ' && board[i][ci] != word[wi]) )
                            break;
                    if( wi == word_sz && ( ci == -1 || board[i][ci] == '#') )
                        return true;
                }

                // if we are at row 0 OR
                //    if above of us is a blocked cell and we are far enough from the bottom that word could fit
                //    then we try to place word top to bottom
                if( i == 0 || (board[i-1][j] == '#' && m-i >= word_sz) ) {
                    int ri = i, wi = 0;
                    for(; wi < word_sz && ri < m; ++ri, ++wi)
                        if( board[ri][j] == '#' || (board[ri][j] != ' ' && board[ri][j] != word[wi]) )
                            break;
                    if( wi == word_sz && ( ri == m || board[ri][j] == '#') )
                        return true;
                }

                // if we are at row m-1 OR
                //    if below of us is a blocked cell and we are far enough from the top that word could fit
                //    then we try to place word bottom to top
                if( i == m-1 || (board[i+1][j] == '#' && i+1 >= word_sz) ) {
                    int ri = i, wi = 0;
                    for(; wi < word_sz && ri >= 0; --ri, ++wi)
                        if( board[ri][j] == '#' || (board[ri][j] != ' ' && board[ri][j] != word[wi]) )
                            break;
                    if( wi == word_sz && ( ri == -1 || board[ri][j] == '#') )
                        return true;
                }
            }
        }

        return false;
    }
};
