#include <iostream>
#include <cassert>

#include <unordered_set>

using namespace std;

// 202. Happy Number
// https://leetcode.com/problems/happy-number/

class Solution {
public:
    bool isHappy(int n) {
        if( n == 0 ) return false;

        unordered_set<int> c;
        int h = 0;
        while(true){

            while(true){
                int rem = n % 10;
                int rm2 = rem*rem;

                // circuit breaker
                if( rm2 > INT_MAX - h ) return false; 

                h += rm2;

                n /= 10;
                if ( n == 0 ) break;
            }
            
            cout << h << endl;
            
            if( h == 1 ) return true;

            if( !c.insert(h).second ) return false;

            n = h;
            h = 0;
        }

        return false;
    }
};

int main() {

    Solution s;

    // assert(s.isHappy(19) == true);
    // assert(s.isHappy(11) == false);
    cout << "INT_MAX " << INT_MAX << endl;
    assert(s.isHappy(INT_MAX) == false);



    return 0;
}
