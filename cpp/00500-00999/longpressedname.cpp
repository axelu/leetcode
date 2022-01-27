
// 925. Long Pressed Name
// https://leetcode.com/problems/long-pressed-name/




class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int nn = name.size();
        int nt = typed.size();

        if( nt < nn )  return false;
        if( nt == nn ) return name == typed;

        int i = 0, j = 0;
        for(; i < nn; ++i) {
            // cout << "i " << i << " j " << j << endl;
            if( j >= nt ) return false;
            if( name[i] == typed[j] ) {
                ++j;
            } else {
                if( j == 0 ) return false;
                while( j < nt && typed[j] != name[i] ) {
                    if( typed[j] != typed[j-1] ) return false;
                    ++j;
                }
                ++j;
            }
        }
        while( j < nt ) {
            if( typed[j-1] != typed[j] ) return false;
            ++j;
        }
        if( name[nn-1] != typed[nt-1] ) return false;
        return true;
    }
};
