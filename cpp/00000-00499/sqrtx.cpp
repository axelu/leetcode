#include <iostream>
#include <cassert>

using namespace std;

// 69. Sqrt(x)
// https://leetcode.com/problems/sqrtx/

class Solution {
public:
    int mySqrt(int x) {
        // not using std::sqrt

        if ( x == 0 ) return 0;

        int i = 46340; // INT_MAX_SQRT
        for(; i > 0; --i){
            if (i*i <= x) break;
        }

        return i;
    }
};

int main() {
    Solution s;

    assert(s.mySqrt(2147483647) == 46340);

    return 0;
}
