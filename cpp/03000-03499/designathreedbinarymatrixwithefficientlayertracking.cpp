
// 3391. Design a 3D Binary Matrix with Efficient Layer Tracking
// https://leetcode.com/problems/design-a-3d-binary-matrix-with-efficient-layer-tracking/



class matrix3D {
private:
    bool mat[100][100][100];
    map<int,set<int>> byCount;
    unordered_map<int,int> byX;

public:
    matrix3D(int n) {
        memset(mat,false,sizeof mat);
        set<int> st;
        for(int i = 0; i < n; ++i) {
            byX[i] = 0;
            st.insert(i);
        }
        byCount[0] = st;
    }

    void setCell(int x, int y, int z) {
        if( !mat[x][y][z] ) {
            mat[x][y][z] = true;
            int cur_cnt = byX[x];

            byCount[cur_cnt].erase(x);
            if( byCount[cur_cnt].empty() )
                byCount.erase(cur_cnt);

            int new_cnt = cur_cnt + 1;
            byX[x] = new_cnt;
            byCount[new_cnt].insert(x);
        }

        return;
    }

    void unsetCell(int x, int y, int z) {
        if( mat[x][y][z] ) {
            mat[x][y][z] = false;
            int cur_cnt = byX[x];

            byCount[cur_cnt].erase(x);
            if( byCount[cur_cnt].empty() )
                byCount.erase(cur_cnt);

            int new_cnt = cur_cnt - 1;
            byX[x] = new_cnt;
            byCount[new_cnt].insert(x);
        }

        return;
    }

    int largestMatrix() {
        /*
        cout << "largest Matrix" << endl;
        for(auto it = byCount.begin(); it != byCount.end(); ++it) {
            cout << "count " << it->first << endl;
            for(auto iit = it->second.begin(); iit != it->second.end(); ++iit)
                cout << *iit << " ";
            cout << endl;
        }
        */
        return *(byCount.rbegin()->second.rbegin());
    }
};

/**
 * Your matrix3D object will be instantiated and called as such:
 * matrix3D* obj = new matrix3D(n);
 * obj->setCell(x,y,z);
 * obj->unsetCell(x,y,z);
 * int param_3 = obj->largestMatrix();
 */
