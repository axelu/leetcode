
// 711. Number of Distinct Islands II
// https://leetcode.com/problems/number-of-distinct-islands-ii/


class Solution {
private:
    // debug
    void printMatrix(vector<vector<int>>& A) {
        int m = A.size();
        int n = A[0].size();
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j)
                cout << A[i][j];
            cout << endl;
        }
    }

    void printGrid(vector<vector<int>>& A) {
        int m = A.size();
        int n = A[0].size();
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j) {
                cout << A[i][j];
                if( j<n-1 ) cout << ',';
            }
            cout << endl;
        }
    }

    // directions
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    array<int,4> explore(vector<vector<int>>& grid, int m, int n, int i, int j, int id) {
        grid[i][j] = id;

        int imin = i;
        int jmin = j;
        int imax = i;
        int jmax = j;

        int i_new,j_new;
        // explore all 4 directions
        for(int k = 0; k < 4; ++k) {

            i_new = i+dirR[k];
            if( i_new < 0 || i_new == m ) continue;
            j_new = j+dirC[k];
            if( j_new < 0 || j_new == n ) continue;

            // water?
            if( grid[i_new][j_new] == 0 )
                continue;
            // land not seen?
            if( grid[i_new][j_new] == 1 ) {
                array<int,4> t = explore(grid,m,n,i_new,j_new,id);
                imin = min(imin,t[0]);
                jmin = min(jmin,t[1]);
                imax = max(imax,t[2]);
                jmax = max(jmax,t[3]);
            }
        }
        return {imin,jmin,imax,jmax};
    }

    vector<vector<int>> buildIsland(vector<vector<int>>& grid, array<int,4>& t, int id) {
        int m = t[2]-t[0]+1;
        int n = t[3]-t[1]+1;
        vector<vector<int>> ans(m,vector<int>(n,0));
        int localI = 0, localJ;
        for(int i = t[0]; i <= t[2]; ++i) {
            localJ = 0;
            for(int j = t[1]; j <= t[3]; ++j) {
                if( grid[i][j] == id )
                    ans[localI][localJ] = 1;
                ++localJ;
            }
            ++localI;
        }
        return ans;
    }

    string hashIsland(vector<vector<int>>& island) {
        int m = island.size();
        int n = island[0].size();

        string s = "";
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                s += island[i][j] ? 'z' : 'a';
            }
            s += "#";
        }
        //return hash<string>{}(s);
        return s;
    }

    vector<vector<int>> rotate90(vector<vector<int>>& A) {
        int m = A.size();
        int n = A[0].size();

        vector<vector<int>> B(n,vector<int>(m,0));
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                B[j][m-1-i] = A[i][j];

        return B;
    }

    void flipVertically(vector<vector<int>>& A) {
        int m = A.size();
        for(int i = 0; i < m; ++i)
            reverse(begin(A[i]),end(A[i]));
    }

    void flipHorizontally(vector<vector<int>>& A) {
        int m = A.size();
        int n = A[0].size();
        int t,b,p;
        for(int j = 0; j < n; ++j) {
            t = 0;   // top
            b = m-1; // bottom
            while(t<b) {
                p = A[t][j];   // park
                A[t][j] = A[b][j];
                A[b][j] = p;
                ++t;
                --b;
            }
        }
    }


public:
    int numDistinctIslands2(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int ans = 0;

        unordered_map<string,int> us;

        int id = 49;
        array<int,4> t;
        vector<vector<int>> island;
        string oh,r90,r180,r270,vh,hh;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if( grid[i][j] == 1 ) { // land not seen before
                    ++id;
                    t = explore(grid,m,n,i,j,id);
                    island = buildIsland(grid,t,id);

                    // cout << "island" << endl;
                    // printMatrix(island);


                    // hash the original island
                    oh = hashIsland(island);
                    // cout << "oh   " << oh << endl;
                    //if( us.empty() ) {
                    //    us.insert({oh,id});
                    //    continue;
                    //}
                    if( us.find(oh) != us.end() ) {
                        // cout << "seen oh" << endl;
                        continue;
                    }

                    // rotate90
                    island = rotate90(island);
                    r90 = hashIsland(island);
                    //cout << "r90  " << h << endl;
                    if( us.find(r90) != us.end() ) {
                        // cout << "seen r90 " << h << endl;
                        continue;
                    }

                    // rotate180
                    island = rotate90(island);
                    r180 = hashIsland(island);
                    //cout << "r180 " << h << endl;
                    if( us.find(r180) != us.end() ) {
                        // cout << "seen r180 " << h << endl;
                        continue;
                    }

                    // rotate270
                    island = rotate90(island);
                    r270 = hashIsland(island);
                    //cout << "r270 " << h << endl;
                    if( us.find(r270) != us.end() ) {
                        // cout << "seen r270 " << h << endl;
                        continue;
                    }

                    // rotate360 to restore original state
                    island = rotate90(island);

                    // reflect/mirror vertically
                    flipVertically(island);
                    vh = hashIsland(island);
                    //cout << "vh   " << h << endl;
                    if( us.find(vh) != us.end() ) {
                        // cout << "seen vh " << h << endl;
                        continue;
                    }
                    flipVertically(island); // restore

                    // reflect/mirror horizontally
                    flipHorizontally(island);
                    hh = hashIsland(island);
                    //cout << "hh   " << h << endl;
                    if( us.find(hh) != us.end() ) {
                        // cout << "seen hh " << h << endl;
                        continue;
                    }

                    us.insert({oh,  id});
                    us.insert({r90, id});
                    us.insert({r180,id});
                    us.insert({r270,id});
                    us.insert({vh,  id});
                    us.insert({hh,  id});

                    ++ans;
                }
            }
        }

        // printGrid(grid);
        // for(auto it = us.begin(); it != us.end(); ++it) {
        //     cout << it->second << ",";
        // }
        return ans;
    }
};
