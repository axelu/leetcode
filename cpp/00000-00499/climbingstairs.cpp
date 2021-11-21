#include <iostream>
#include <cassert>

#include <vector>

using namespace std;

// 70. Climbing Stairs
// https://leetcode.com/problems/climbing-stairs/

class Solution {
public:
    int climbStairs(int n) {
        if( n < 4 ) return n;

        vector<int> v(n+1,0);
        v[1] = 1;
        v[2] = 2;
        for (auto it = v.begin() + 3; it != v.end(); ++it) {
            *it = *(it - 1) + *(it - 2);
        }
        return v[n];
    }
};

int main() {

    Solution s;

    // 1 <= n <= 2


    assert(s.climbStairs(1) == 1);
    assert(s.climbStairs(2) == 2);
    assert(s.climbStairs(3) == 3);
    assert(s.climbStairs(4) == 5);
    assert(s.climbStairs(5) == 8);
    assert(s.climbStairs(6) == 13);

    // assert(s.climbStairs(45) == 1836311903);

    for(int i = 1; i <= 45; ++i)
        cout << i << " " << s.climbStairs(i) << endl;



    return 0;
}
