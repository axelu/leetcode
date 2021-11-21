
// 1079. Letter Tile Possibilities
// https://leetcode.com/problems/letter-tile-possibilities/



class Solution {
private:
    unordered_set<string> us;

    // debug
    void toBinary(int x) {
        string s = "";
        while(x>0) {
            int rem = x%2;
            s = to_string(rem) + s;
            x /=2;
        }
        cout << s << endl;
    }

    void rec(string& tiles, int n, string& path, int state) {
        if( path.size() == n ) return;

        for(int i = 0; i < n; ++i) {
            if( !((state >> i) & 1) ) {
                state |= 1 << i;
                path.push_back(tiles[i]);
                us.insert(path);
                rec(tiles,n,path,state);
                // backtracking
                path.pop_back();
                state &= ~(1 << i);
            }
        }
    }

public:
    int numTilePossibilities(string& tiles) {
        int n = tiles.size();
        string path = "";
        rec(tiles,n,path,0);
        return us.size();
    }
};
