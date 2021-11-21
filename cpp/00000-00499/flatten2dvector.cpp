
// 251. Flatten 2D Vector
// https://leetcode.com/problems/flatten-2d-vector/




class Vector2D {
private:
    vector<vector<int>> Vec;
    vector<vector<int>>::iterator ito;
    vector<int>::iterator iti;

public:
    Vector2D(vector<vector<int>>& vec) {
        Vec = vec;
        ito = Vec.begin();
        while( ito != Vec.end() ) {
            iti = ito->begin();
            if( iti != ito->end() ) break;
            ++ito;
        }
    }

    int next() {
        int ans = *iti;
        // advance
        ++iti;
        if( iti == ito->end() ) {
            ++ito;
            while( ito != Vec.end() ) {
                iti = ito->begin();
                if( iti != ito->end() ) break;
                ++ito;
            }
        }
        return ans;
    }

    bool hasNext() {
        return ito != Vec.end();
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D* obj = new Vector2D(vec);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
