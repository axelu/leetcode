
// 631. Design Excel Sum Formula
// https://leetcode.com/problems/design-excel-sum-formula/



class Excel {
private:
    unordered_map<int,int> * G;
    int * A;
    int n,N;

    void update(int u, int d) {
        A[u] += d;
        for(auto it = G[u].begin(); it != G[u].end(); ++it) {
            int v = it->first;
            int weight = it->second;
            update(v,weight*d);
        }
    }



public:
    Excel(int height, char width) {
        n = width - 64; // cols
        N = height * n;
        G = new unordered_map<int,int>[N];
        A = new int[N];
        for(int i = 0; i < N; ++i)
            A[i] = 0;
    }

    void set(int row, char column, int val) {
        int c = column - 65;
        int u = (row-1) * n + c;
        // cout << "set row " << row << " column " << column << " u " << u << endl;

        // we could be a sum cell, in which case
        // we need to break all incoming edges
        for(int i = 0; i < N; ++i) {
            if( i == u )
                continue;
            G[i].erase(u);
        }

        // update all outgoing edges with the difference
        int d = val - A[u];
        A[u] = val;
        for(auto it = G[u].begin(); it != G[u].end(); ++it) {
            int v = it->first;
            int weight = it->second;
            update(v,weight*d);
        }
    }

    int get(int row, char column) {
        int col = column - 65;
        return A[(row-1) * n + col];
    }

    int sum(int row, char column, vector<string> numbers) {
        int v = (row-1) * n + (column - 65);
        // cout << "sum row " << row << " column " << column << " v " << v << endl;

        // we could already be a sum cell, in which case
        // we need to break all incoming edges
        for(int i = 0; i < N; ++i) {
            if( i == v )
                continue;
            G[i].erase(v);
        }

        // remember our current value
        int t = A[v];

        // reset our value
        A[v] = 0;

        int u;
        int c,r;         // c column, r row
        int c1,r1,c2,r2; // c column, r row
        int x1,y1,x2,y2; // x column, y row
        int i,j;         // i row, j column
        for(int k = 0; k < numbers.size(); ++k) {
            // the string numbers[i] is either one cell OR
            // it is a rectangle of cells
            // 1 cell -> A1 ... Z26
            if( numbers[k].size() <= 3 ) { // single cell
                c = numbers[k][0] - 65;
                r = stoi(numbers[k].substr(1)) - 1;
                u = r * n + c;
                auto p = G[u].insert({v,1});
                if( !p.second )
                    ++p.first->second;
                A[v] += A[u];
            } else {
                // get the corners of the rectangle
                // where is the ':', its either at pos 2 or 3
                if( numbers[k][2] == ':' ) {
                    c1 = numbers[k][0] - 65;
                    r1 = stoi(numbers[k].substr(1,1)) - 1;
                    c2 = numbers[k][3] - 65;
                    r2 = stoi(numbers[k].substr(4)) - 1;
                } else {
                    c1 = numbers[k][0] - 65;
                    r1 = stoi(numbers[k].substr(1,2)) - 1;
                    c2 = numbers[k][4] - 65;
                    r2 = stoi(numbers[k].substr(5)) - 1;
                }
                // c1,r1 could be any corner: top left, top right, bottom left, bottom right
                // c2,r2 will be opposite
                x1 = min(c1,c2);
                x2 = max(c1,c2);
                y1 = min(r1,r2);
                y2 = max(r1,r2);
                for(i = y1; i <= y2; ++i) {     // row
                    for(j = x1; j <= x2; ++j) { // col
                        u = i * n + j;
                        auto p = G[u].insert({v,1});
                        if( !p.second )
                            ++p.first->second;
                        A[v] += A[u];
                    }
                }
            }
        }

        // update all outgoing edges with the difference
        int d = A[v] - t;
        for(auto it = G[v].begin(); it != G[v].end(); ++it) {
            int u = it->first;
            int weight = it->second;
            update(u,weight*d);
        }

        return A[v];
    }
};

/**
 * Your Excel object will be instantiated and called as such:
 * Excel* obj = new Excel(height, width);
 * obj->set(row,column,val);
 * int param_2 = obj->get(row,column);
 * int param_3 = obj->sum(row,column,numbers);
 */
