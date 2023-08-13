
// 2166. Design Bitset
// https://leetcode.com/problems/design-bitset/




class Bitset {
private:
    vector<bool> btset;
    int n;
    bool flipped;
    int ones;
public:
    Bitset(int size) {
        btset.assign(size,false);
        n = size;
        flipped = false;
        ones = 0;
    }

    void fix(int idx) {
        if( !flipped ) {
            if( !btset[idx] ) {
                btset[idx] = true;
                ++ones;
            }
        } else {
            if( btset[idx] ) {
                btset[idx] = false;
                ++ones;
            }
        }
    }

    void unfix(int idx) {
        if( !flipped ) {
            if( btset[idx] ) {
                btset[idx] = false;
                --ones;
            }
        } else {
            if( !btset[idx] ) {
                btset[idx] = true;
                --ones;
            }
        }
    }

    void flip() {
        flipped = !flipped;
        ones = n - ones;
    }

    bool all() {
        return ones == n;
    }

    bool one() {
        return ones > 0;
    }

    int count() {
        return ones;
    }

    string toString() {
        string s(n, '0');
        for(int i = 0; i < n; ++i)
            if( flipped != btset[i] )
                s[i] = '1';
        return s;
    }
};

/**
 * Your Bitset object will be instantiated and called as such:
 * Bitset* obj = new Bitset(size);
 * obj->fix(idx);
 * obj->unfix(idx);
 * obj->flip();
 * bool param_4 = obj->all();
 * bool param_5 = obj->one();
 * int param_6 = obj->count();
 * string param_7 = obj->toString();
 */
