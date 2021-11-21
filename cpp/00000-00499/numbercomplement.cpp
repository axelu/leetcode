
// Complement of base 10 integer
// 476. Number Complement

// https://leetcode.com/problems/complement-of-base-10-integer/
// https://leetcode.com/problems/number-complement/

// day 6 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/559/week-1-october-1st-october-7th/3484/


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


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789
class Solution {
public:
    int bitwiseComplement(int N) {
        if( N == 0 ) return 1;

        // to binary string
        string b = "";
        while( N > 0) {
            int rem = N % 2;
            b = to_string(rem) + b;
            N /= 2;
        }
        // cout << b << endl;
        // to complement string
        string c;
        for(char ch : b) {
            if( ch == '1' && c.empty() ) continue;
            c += ( ch == '1' ) ? "0" : "1";
        }
        if( c.empty() ) c = "0";
        // cout << c << endl;
        // complement string to int
        int r = 0;
        int e = 0;
        for(auto itr = c.rbegin(); itr != c.rend(); ++itr) {
            if( *itr == '1' ) r += pow(2,e);
            ++e;
        }
        return r;
    }
};

int main() {

    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end;
    chrono::duration<double> elapsed_seconds;

    // start = chrono::system_clock::now();
    // do something
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    Solution s;
    int N;
    int r;

    // Example 1
    N = 5;
    cout << "intput " << N << endl;
    r = s.bitwiseComplement(N);
    cout << "result " << r << endl;
    assert(r == 2);

    // Example 2
    N = 7;
    cout << "input " << N << endl;
    r = s.bitwiseComplement(N);
    cout << "result " << r << endl;
    assert(r == 0);

    // Example 3
    N = 10;
    cout << "input " << N << endl;
    r = s.bitwiseComplement(N);
    cout << "result " << r << endl;
    assert(r == 5);

    N = 1;
    cout << "input " << N << endl;
    r = s.bitwiseComplement(N);
    cout << "result " << r << endl;
    assert(r == 0);

    N = 11;
    cout << "input " << N << endl;
    r = s.bitwiseComplement(N);
    cout << "result " << r << endl;
    assert(r == 4);

    N = 1000000000;
    cout << "input " << N << endl;
    r = s.bitwiseComplement(N);
    cout << "result " << r << endl;
    assert(r == 73741823);

    N = 536870911;
    cout << "input " << N << endl;
    r = s.bitwiseComplement(N);
    cout << "result " << r << endl;
    assert(r == 0);

    N = 2147483647;
    cout << "input " << N << endl;
    r = s.bitwiseComplement(N);
    cout << "result " << r << endl;
    assert(r == 0);

    return 0;
}
