
// 1616. Split Two Strings to Make Palindrome
// https://leetcode.com/problems/split-two-strings-to-make-palindrome/


#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <iterator>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <map>
#include <cmath>
#include <climits>
#include <bitset>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
private:
    bool checkPalindromeFormation(string& a, string& b, int i, int j, int n) {
        bool r = true;

        string * prefix = &a; // pointer to avoid copying the string
        string * suffix = &a;
        for(; i < n && j >= 0; ++i, --j) {
            if( (*prefix)[j] == (*suffix)[i] ) continue;
            r = false;
            break;
        }
        int id = i;
        int jd = j;
        if( !r ) {
            // try to continue with a as suffix and b as prefix
            r = true;
            prefix = &b;
            for(; i < n && j >= 0; ++i, --j) {
                if( (*prefix)[j] == (*suffix)[i] ) continue;
                r = false;
                break;
            }
        }
        if( !r ) {
            // try to continue with a as prefix and b as suffix
            i = id;
            j = jd;
            r = true;
            prefix = &a;
            suffix = &b;
            for(; i < n && j >= 0; ++i, --j) {
                if( (*prefix)[j] == (*suffix)[i] ) continue;
                r = false;
                break;
            }
        }

        return r;
    }
public:
    bool checkPalindromeFormation(string& a, string& b) {
        // check if aprefix + bsuffix or bprefix + asuffix forms a palindrome
        // 1 <= a.length, b.length <= 10e5
        // a.length == b.length
        // a and b consist of lowercase English letters

        auto n = a.size();
        if( n == 1 ) return true;

        int i = i = n / 2;
        int j = n % 2 == 1 ? i : i - 1;

        bool r;

        r = checkPalindromeFormation(a,b,i,j,n);
        if( r ) return r;
        r = checkPalindromeFormation(b,a,i,j,n);
        return r;
    }
};


int main() {

    Solution s;
    string str, a, b;

    // str = "abba";
    // assert(s.isPalindrome(str) == true);

    // str = "abcba";
    // assert(s.isPalindrome(str) == true);

    ////////////////////////////////////

    // true for bprefix + asuffix
    a = "dbba";
    b = "abcd";
    assert(s.checkPalindromeFormation(a,b) == true);

    // true for aprefix + bsuffix
    a = "abcd";
    b = "dbba";
    assert(s.checkPalindromeFormation(a,b) == true);

    a = "abc";
    b = "abc";
    assert(s.checkPalindromeFormation(a,b) == false);

    a = "x";
    b = "y";
    assert(s.checkPalindromeFormation(a,b) == true);

    a = "abdef";
    b = "fecab";
    assert(s.checkPalindromeFormation(a,b) == true);

    a = "ulacfd";
    b = "jizalu";
    assert(s.checkPalindromeFormation(a,b) == true);

    a = "xbdef";
    b = "xecab";
    assert(s.checkPalindromeFormation(a,b) == false);

    a = "fbccba";
    b = "abcdeg";
    assert(s.checkPalindromeFormation(a,b) == true);

    a = "abcdeg";
    b = "fbccba";
    assert(s.checkPalindromeFormation(a,b) == true);

    a = "fbccba";
    b = "defgkf";
    assert(s.checkPalindromeFormation(a,b) == true);

    a = "defgkf";
    b = "fbccba";
    assert(s.checkPalindromeFormation(a,b) == true);


    srand(time(nullptr)); // use current time as seed for random generator

    cout << "random 100000 a palindrom -> true" << endl;
    int rdm;
    a = "";
    int n = 50000;
    for(int i = 0; i < n; ++i) {
        int rdm = rand() % 26; // random in the range 0 to 25
        a += rdm + 'a';
    }
    string a2 = a;
    reverse(begin(a2),end(a2));
    a += a2;
    b = "";
    n = 100000;
    for(int i = 0; i < n; ++i) {
        int rdm = rand() % 26; // random in the range 0 to 25
        b += rdm + 'a';
    }
    assert(s.checkPalindromeFormation(a,b) == true);

    cout << "random 100000 asuffix + bprefix palindrom -> true" << endl;
    string bt1 = a.substr(0,50000);
    string bt2 = b.substr(50000,50000);
    string at1 = b.substr(0,50000);
    string at2 = a.substr(50000,50000);
    a = at1 + at2;
    b = bt1 + bt2;
    assert(s.checkPalindromeFormation(a,b) == true);


/*
    cout << A << endl;
    assert(s.buddyStrings(A,B) == true);

    int rdm1 = rand() % 20001; // random in the range 0 to 20000
    int rdm2 = rand() % 20001; // random in the range 0 to 20000

    // swap
    B[rdm2] = A[rdm1];
    B[rdm1] = A[rdm2];
    cout << "random 20000 not equal -> true" << endl;
    cout << B << endl;
    assert(s.buddyStrings(A,B) == true);

    // switch out last
    char lA = A[19999];
    char c = 'a';
    while( lA == c ) ++c;
    A[19999] = c;
    cout << "random 20000 not equal -> false" << endl;
    assert(s.buddyStrings(A,B) == false);
*/
    return 0;
}
