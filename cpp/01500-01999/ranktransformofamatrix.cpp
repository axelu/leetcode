
// 1632. Rank Transform of a Matrix
// https://leetcode.com/problems/rank-transform-of-a-matrix/
// day 8 August 2021 challenge
// https://leetcode.com/explore/featured/card/august-leetcoding-challenge-2021/614/week-2-august-8th-august-14th/3874/




class Solution {
private:
    void rowRankTransform(vector<vector<int>>& matrix, int n) {
        // the matrix has only one row
        // n cols
        map<int,vector<int>> mp; // val,{coli,colj,...}
        pair<map<int,vector<int>>::iterator,bool> p;
        for(int i = 0; i < n; ++i) {
            p = mp.insert({matrix[0][i],{i}});
            if( !p.second)
                p.first->second.push_back(i);
        }

        int r = 1; // rank
        for(auto it = mp.begin(); it != mp.end(); ++it) {
            for(int i = 0; i < it->second.size(); ++i)
                matrix[0][it->second[i]] = r;
            ++r;
        }
    }

    void colRankTransform(vector<vector<int>>& matrix, int m) {
        // the matrix has only one col
        // m rows
        map<int,vector<int>> mp; // val,{rowi,rowj,...}
        pair<map<int,vector<int>>::iterator,bool> p;
        for(int i = 0; i < m; ++i) {
            p = mp.insert({matrix[i][0],{i}});
            if( !p.second)
                p.first->second.push_back(i);
        }

        int r = 1; // rank
        for(auto it = mp.begin(); it != mp.end(); ++it) {
            for(int i = 0; i < it->second.size(); ++i)
                matrix[it->second[i]][0] = r;
            ++r;
        }
    }

public:
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
        int m = matrix.size();      // rows
        int n = matrix[0].size();   // cols

        if( m == 1 && n == 1 )
            return {{1}};
        if( m == 1 ) {
            rowRankTransform(matrix,n);
            return matrix;
        }
        if( n == 1 ) {
            colRankTransform(matrix,m);
            return matrix;
        }

        // we will need to connect the same values along rows and colums
        // example (x represents some arbitrary different but unique values)
        //     0  1  2  3  4
        //  0  x  x 19  x 19
        //  1  x 19  x  x  x
        //  2  x  x  x  x  x
        //  3  x 19  x 19  x
        //  4  x  x  x  x  x
        //  5  x  x  x 19  x
        //  the two 19's in row 0 should be connected into one component
        //  the remaining 19's should be connected into one component
        //    because they share a row/col connection

        int i,j;

        map<array<int,2>,int> cvr;          // {col,val},row
        set<array<int,3>> sorted;           // {val,row,col}


        // undirected graph
        // we will create an edge between cells in the same col or row
        // if the cell's value is the same
        vector<int> G[m*n];

        int val,u,v;
        unordered_map<int,int> vc;      // val,col
        for(i = 0; i < m; ++i) {        // rows
            vc.clear();
            for(j = 0; j < n; ++j) {    // cols
                u = i*n+j;

                val = matrix[i][j];
                sorted.insert({val,i,j});

                // have we seen the same value in the current row?
                auto f = vc.find(val);
                if( f != vc.end() ) {
                    v = i*n+f->second;
                    G[u].push_back(v);
                    G[v].push_back(u);
                } else {
                    vc.insert({val,j});
                }

                // have we seen the same value in the current col?
                auto p = cvr.insert({{j,val},i});
                if( !p.second ) {
                    v = p.first->second*n+j;
                    G[u].push_back(v);
                    G[v].push_back(u);
                }
            }
        }


        // ranks start at 1
        int highestRankByRow[m];memset(highestRankByRow,0,sizeof highestRankByRow);
        int highestRankByCol[n];memset(highestRankByCol,0,sizeof highestRankByCol);

        int row,col,rank;

        int seen[m*n];memset(seen,0,sizeof seen);
        queue<int> q;
        queue<int> c;

        for(auto it = sorted.begin(); it != sorted.end(); ++it) {
            // val = (*it)[0];
            row = (*it)[1];
            col = (*it)[2];

            u = row*n+col;
            if( seen[u] )
                continue;

            // get all other cells in this component
            // figure rank from our row and col AND
            // all other cells in this component
            // BFS
            q.push(u);
            seen[u] = 1;
            c.push(u);
            rank = 0;
            while( !q.empty() ) {
                u = q.front();
                q.pop();

                row = u/n;
                col = u%n;
                rank = max({rank,highestRankByRow[row],highestRankByCol[col]});

                for(i = 0; i < G[u].size(); ++i) {
                    v = G[u][i];

                    if( seen[v] )
                        continue;

                    seen[v] = 1;
                    c.push(v);
                    q.push(v);
                }
            }

            ++rank;
            while( !c.empty() ) {
                u = c.front();
                c.pop();

                row = u/n;
                col = u%n;
                matrix[row][col] = rank;
                highestRankByRow[row] = rank;
                highestRankByCol[col] = rank;
            }
        }

        return matrix;

    }
};
