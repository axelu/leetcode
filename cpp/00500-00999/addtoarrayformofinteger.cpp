#include <iostream>
#include <cassert>
#include <vector>

// 989. Add to Array-Form of Integer
// https://leetcode.com/problems/add-to-array-form-of-integer/

using namespace std;

class Solution {
public:
    vector<int> addToArrayForm(vector<int>& A, int K) {
        vector<int> r;

        if ( K == 0 ) return A;

        auto it = A.rbegin(); // if A.empty() then A.rbegin() == A.rend()

        while ( it != A.rend() || K != 0 ) {
            K += ( it !=A.rend() ) ? *it : 0;
            r.insert(r.begin(), K % 10);
            K /= 10;
    
            if ( it != A.rend() ) ++it;
            
        }

        return r;
    }
};


int main() {

    Solution s;

    vector<int> v1in = {1,2,0,0};
    int k1 = 34;
    vector<int> v1out = {1,2,3,4};
    assert(s.addToArrayForm(v1in, k1) == v1out);

    vector<int> v2in = {2,7,4};
    int k2 = 181;
    vector<int> v2out = {4,5,5};
    assert(s.addToArrayForm(v2in, k2) == v2out);

    vector<int> v3in = {2,1,5};
    int k3 = 806;
    vector<int> v3out = {1,0,2,1};
    assert(s.addToArrayForm(v3in, k3) == v3out);

    vector<int> v4in = {9,9,9,9,9,9,9,9,9,9};
    int k4 = 1;
    vector<int> v4out = {1,0,0,0,0,0,0,0,0,0,0};
    assert(s.addToArrayForm(v4in, k4) == v4out);

    vector<int> v5in = {};
    int k5 = 100;
    vector<int> v5out = {1,0,0};
    assert(s.addToArrayForm(v5in, k5) == v5out);

    vector<int> v6in = {9,9,9,9,9,9,9,9,9,9};
    int k6 = 0;
    vector<int> v6out = {9,9,9,9,9,9,9,9,9,9};
    assert(s.addToArrayForm(v6in, k6) == v6out);


    return 0;
}
