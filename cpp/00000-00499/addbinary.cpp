#include <iostream>
#include <string>
#include <cassert>

using namespace std;

// 67. Add Binary
// https://leetcode.com/problems/add-binary/

class Solution {
public:
    string addBinary(string a, string b) {

        if ( a == "0" ) return b;
        if ( b == "0" ) return a;

        string r;
        int carried = 0;
        
        auto it1 = a.rbegin();
        auto it2 = b.rbegin();

        while ( it1 != a.rend() || it2 != b.rend() || carried != 0 ) {

            carried += ( it1 != a.rend() ) ? *it1 - '0' : 0;
            carried += ( it2 != b.rend() ) ? *it2 - '0' : 0;

            switch ( carried ) {
                case 1: r.insert(0, "1");
                        carried = 0;
                        break;
                case 2: r.insert(0, "0");
                        carried = 1;
                        break;
                case 3: r.insert(0, "1");
                        carried = 1;
                        break;
                default: r.insert(0, "0");
                         break;
            }

            if ( it1 != a.rend() ) ++it1;
            if ( it2 != b.rend() ) ++it2;
        }

        return r;
    }
};

int main() {

    Solution s;

    assert(s.addBinary("0", "1011") == "1011");
    assert(s.addBinary("1010", "0") == "1010");
    assert(s.addBinary("0", "1") == "1");
    assert(s.addBinary("1", "1") == "10");
    assert(s.addBinary("11", "1") == "100");
    assert(s.addBinary("1010", "1011") == "10101");
    assert(s.addBinary("1010", "11") == "1101");
    assert(s.addBinary("100101", "10101") == "111010");
    assert(s.addBinary("1111", "1111") == "11110");

    return 0;
}


