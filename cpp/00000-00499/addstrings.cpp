#include <iostream>
#include <cassert>
#include <string>

// 415. Add Strings
// https://leetcode.com/problems/add-strings/

using namespace std;

class Solution {
public:
    string addStrings(string num1, string num2) {

        // if ( num1.empty() && num2.empty return "";
        if ( num1.empty() || num1 == "0" ) return num2;
        if ( num2.empty() || num2 == "0" ) return num1;

        string r;
        auto it1 = num1.rbegin();
        auto it2 = num2.rbegin();
        int carried = 0;

        while ( it1 != num1.rend() || it2 != num2.rend() || carried != 0 ) {
            carried += ( it1 != num1.rend() ) ? *it1 - '0' : 0;
            carried += ( it2 != num2.rend() ) ? *it2 - '0' : 0;
            r.insert(r.begin(), (carried % 10) + '0');
            carried /= 10;

            if ( it1 != num1.rend() ) ++it1;
            if ( it2 != num2.rend() ) ++it2;

            if ( carried == 0 ) {
                if ( it1 == num1.rend() && it2 != num2.rend() ) {
                    r.insert(r.begin(), num2.begin(), it2.base());
                    break;
                } else if (  it1 != num1.rend() && it2 == num2.rend() ) {
                    r.insert(r.begin(), num1.begin(), it1.base());
                    break;
                }
            }
        }

        return r;
    }
};

int main() {

    Solution s;

    assert(s.addStrings("0", "123") == "123");
    assert(s.addStrings("456", "0") == "456");
    assert(s.addStrings("123", "123") == "246");
    assert(s.addStrings("999", "1") == "1000");
    assert(s.addStrings("1999", "2000") == "3999");
    assert(s.addStrings("1", "1000000000000") == "1000000000001");
    assert(s.addStrings("1000000000000", "1") == "1000000000001");

    return 0;
}
