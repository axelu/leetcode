
// 3552. Grid Teleportation Traversal
// https://leetcode.com/problems/grid-teleportation-traversal/





class Solution {
public:
    int minMoves(vector<string>& matrix) {
        int m = matrix.size();    // rows
        int n = matrix[0].size(); // cols

        char char_dest = matrix[m-1][n-1];
        if( char_dest == '#' )
            return -1;

        // TODO consider a quickcheck if dest is even reachable
        // using like a DFS

        // positions of chars (uppercase) in our matrix
        vector<array<int,2>> char_pos[26];
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( isupper(matrix[i][j]) ) {
                    char_pos[matrix[i][j]-'A'].push_back({i, j});
                }
            }
        }

        // directions   R  D  L  U
        int dirR[4] = { 0, 1, 0,-1};
        int dirC[4] = { 1, 0,-1, 0};


        // BFS Breadth-First-Search
        // in our priority queue
        // moves, i, j, seen


        // TODO keep track of seen and at what step
        // only put equal or better into queue
        // we could also use two queue and empty all steps
        vector<vector<int>> visited(m, vector<int>(n,INT_MAX));

        auto cmp = [&](const array<int,4>& a, const array<int,4>& b) {
            if( a[0] > b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                // prefer if one of them is the same char as destination
                char char_b = matrix[b[1]][b[2]];
                if( char_b == char_dest )
                    return true;
            }
            return false;
        };
        priority_queue<array<int,4>, vector<array<int,4>>, decltype(cmp)> pq(cmp);
        pq.push({0,0,0,0});
        visited[0][0] = 0;
        while( !pq.empty() ) {
            int moves = pq.top()[0];
            int i = pq.top()[1];
            int j = pq.top()[2];
            int seen = pq.top()[3];
            pq.pop();

            char chr = matrix[i][j];
            if( isupper(chr) && chr == char_dest )
                return moves;

            if( i == m-1 && j == n-1 )
                return moves;

            // are we on a letter and can jump?
            int chr_idx = chr - 'A';
            if( isupper(matrix[i][j]) && !(seen & (1<<chr_idx)) ) {
                for(auto& pos: char_pos[chr_idx] ) {
                    int i_new = pos[0];
                    int j_new = pos[1];
                    if( i_new == i && j_new == j )
                        continue;

                    if( visited[i_new][j_new] <= moves )
                        continue;

                    int seen_new = seen | (1<<chr_idx);
                    pq.push({moves, i_new, j_new, seen_new});
                    visited[i_new][j_new] = moves;
                }
            }

            // explore all 4 directions
            for(int k = 0; k < 4; ++k) {
                int i_new = i + dirR[k];
                if( i_new < 0 || i_new == m )
                    continue;
                int j_new = j + dirC[k];
                if( j_new < 0 || j_new == n )
                    continue;

                if( matrix[i_new][j_new] == '#' )
                    continue;

                // if we the new cell is a letter and we have seen this letter already in our journey,
                // then there is no point of going there
                if( isupper(matrix[i_new][j_new]) ) {
                    int chr_idx_new = matrix[i_new][j_new] - 'A';
                    if( seen & (1<<chr_idx_new) )
                        continue;
                }

                if( visited[i_new][j_new] <= moves + 1 )
                    continue;

                pq.push({moves+1, i_new, j_new, seen});
                visited[i_new][j_new] = moves + 1;
            }
        }

        return -1;
    }
};



/* test cases used
["A..",".A.","..."]
[".#...",".#.#.",".#.#.","...#."]
["..#C","..A.","BC.#"]
["..#C","..A.","BC.."]
["..#."]
["....AN...U.....Z..G....QCI...","SV.....C...XRB...........J...",".......OX....Z..K........D...","M.#...K..Q......L..L..PD.....",".X.R.......ZNB.E..........C..","...............MBA.....XN....","U.K...X..............N.....R.","J.....DB.....BY....Q.......NQ",".Z...RV.NK..................H","....#...U#...JQU.......F....H","EW......Z.....P...R..D...A.C.","..EA.......BHZP.U..E..NU..P..","...I.N...X..........HD...T...",".P..W.....K..TH..L.W..G..E...","Z..R..V...#...D..Y...L...K...","...I.....T..........W......L.","..........W......W........UI.","..N.....C.B.....IC.K.........","......M....Z..............Z..","...EY.....E......J..U.Y.P....",".....XMN.W.........K.FR......","........N..J...W.A..#......B.","..T......G..F..OM.......V...K","D.N.X....O......H....GAV.V.H.","..B..I.EH.P..K...K..F..X.....","..BFJ.FF..O....G..J...O...#..","......B.A.J.QMR.Y.X...Q......",".E.......#.......OG.G.U....CF","HZ.I.V...EZ......E...........",".............Y......W........","QP.X.E..QJ..I......YN.Q.E.NL.","......Q.F.....G..W...UN...D..","......NU..B...N....R...G....D","...J..O..H..H.....H.....Q....","O......C..........DC.....T...",".E.ZQ.....N.....DW.....W.J..A",".T.......VV.I....FE...N....N.",".U......CE...G...M.........H.","T.SCT.......#.RP...W.........","......O..N..XWU#IH...S.L..Y..","..Q..I..I.A...CMV....RYV.F.J.","J........Q....H.....W........","....#.F............R...PI....",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................",".............................","............................."]
*/
