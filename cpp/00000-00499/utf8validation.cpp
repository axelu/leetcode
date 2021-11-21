
// 393. UTF-8 Validation
// https://leetcode.com/problems/utf-8-validation/



class Solution {
private:
    void printIntBinary(unsigned int x) {
        for(int i = 7; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
    }

    int charLength(int x) {
        // checking the first bits of the least significant 8 bits
        if( !(x & (1 << 7)) ) {
            return 1;
        } else {
            if( !(x & (1 << 6)) ) return -1;
            int res = 2;
            if( !(x & (1 << 5)) ) return res;
            ++res;
            if( !(x & (1 << 4)) ) return res;
            ++res;
            if( !(x & (1 << 3)) ) return res;
        }
        return -1;
    }

public:
    bool validUtf8(vector<int>& data) {
        // 0 <= data[i] <= 255
        int n = data.size();

        /*
        // debug
        for(int i = 0; i < n; ++i) {
            printIntBinary(data[i]);
            cout << " ";
        }
        cout << endl;
        */

        int l,j;
        for(int i = 0; i < n; ++i) {
            // are we dealing with a 1,2,3 or 4 byte long char?
            l = charLength(data[i]);
            if( l == -1 ) return false;
            if( l > 1 ) {
                for( j = i+1; j < i+l; ++j) {
                    if( j == n )
                        return false;
                    if( !(data[j] & (1 << 7)) || (data[j] & (1 << 6)) )
                        return false;
                }
                i = j-1;
            }
        }
        return true;
    }
};
