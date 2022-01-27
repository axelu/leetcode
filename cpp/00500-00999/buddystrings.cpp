
// 859. Buddy Strings
// day 12 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/560/week-2-october-8th-october-14th/3492/
// https://leetcode.com/problems/buddy-strings/



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
public:
    bool buddyStrings(string A, string B) {
        auto n = A.size();
        if( n != B.size() ) return false;
        if( n < 2 ) return false;

        bool r = false;

        if( A == B ) {
            if( n > 26 ) return true;

            // need at least one duplicate letter for swap
            int seen = 0; // bitmask to track if char already seen
            for(auto itA = begin(A); itA != end(A); ++itA) {
                char ch = *itA - 'a';
                if( (seen >> ch) & 1 ) {
                    // char has been seen before
                    r = true;
                    break;
                }
                seen ^= 1 << ch; // mark char as seen
            }

        } else {
            string::iterator it1 = end(B);
            string::iterator it2;
            for(auto itA = begin(A), itB = begin(B); itA != end(A) && itB != end(B); ++itA, ++itB) {
                if( *itA == *itB ) continue;

                if( it1 == end(B) ) {
                    // first mismatch encountered
                    it1 = itB;
                    it2 = itA;
                    continue;
                }

                if( r ) {
                    // swapped once already
                    r = false;
                    break;
                }

                if( *it1 == *itA && *it2 == *itB ) {
                    r = true;
                } else {
                    // cannot swap
                    r = false;
                    break;
                }
            }
        }

        return r;
    }
};


int main() {

    Solution s;
    string A,B;

    // Example 1
    A = "ab";
    B = "ba";
    assert(s.buddyStrings(A,B) == true);

    // Example 2
    A = "ab";
    B = "ab";
    assert(s.buddyStrings(A,B) == false);

    // Example 3
    A = "aa";
    B = "aa";
    assert(s.buddyStrings(A,B) == true);

    // Example 4
    A = "aaaaaaabc";
    B = "aaaaaaacb";
    assert(s.buddyStrings(A,B) == true);

    // Example 5
    A = "";
    B = "aa";
    assert(s.buddyStrings(A,B) == false);

    A = "efg";
    B = "efg";
    assert(s.buddyStrings(A,B) == false);

    A = "efgbcgh";
    B = "efgcbhg";
    assert(s.buddyStrings(A,B) == false);

    A = "efgbccgh";
    B = "efgcbbhg";
    assert(s.buddyStrings(A,B) == false);

    A = "efe";
    B = "efd";
    assert(s.buddyStrings(A,B) == false);

    A = "efe";
    B = "eef";
    assert(s.buddyStrings(A,B) == true);

    A = "abcdefghijklmnopqrstuvwxyz";
    B = "abcdefghijklmnopqrstuvwxyz";
    assert(s.buddyStrings(A,B) == false);

    srand(time(nullptr)); // use current time as seed for random generator

    cout << "random 20000 equal -> true" << endl;
    int rdm;
    A = "";
    int n = 20000;
    for(int i = 0; i < n; ++i) {
        int rdm = rand() % 26; // random in the range 0 to 25
        A += rdm + 'a';
    }
    B = A;
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

    return 0;
}
