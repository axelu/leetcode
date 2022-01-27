#include <iostream>
#include <cassert>

#include <vector>
#include <algorithm>

using namespace std;

// day 29 August 2020 challenge
// 969. Pancake Sorting
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/553/week-5-august-29th-august-31st/3441/
// https://leetcode.com/problems/pancake-sorting/




void printpsv(vector<int>& A) {
    for(int i : A) cout << i << " ";
    cout << endl;
}


class Solution {
public:
    vector<int> pancakeSort(vector<int>& A) {
        size_t as = A.size();
        if( as == 1 ) return {};

        vector<int> r;

        // find the pos of max (initially max = A.size())
        // flip on that pos if > 0, flip entire vector on length, now max is at the end
        // repeat: find max ( A.size() - 1) pos in remaining array ( length is A.size() - 1)
        // flip that position to front and then flip remaining array length
        // don't flip is max is at end
        // monitor if it is sorted

        bool isSorted = false;
        while( !isSorted && as > 1 ) {   
            isSorted = true;
            for(size_t i = 0; i < as; ++i) {
                if( i > 0 )
                    if( A[i - 1] > A[i] ) isSorted = false;
                if( A[i] == as ) {
                    if( i < as - 1 ) {
                        isSorted = false;
                        if( i > 0 ) {
                            reverse(A.begin(), A.begin() + i + 1);
                            r.push_back(i + 1);
                        }
                        reverse(A.begin(), A.begin() + as);
                        r.push_back(as);
                    }
                }
            }
            --as;
        }

        // the length of r should be less than 10 * A.length
        // no check needed, above algo will achieve that in all cases
        return r;
    }
};

int main() {
    Solution s;
    vector<int> A;
    vector<int> r;

    A = {1,2,3};
    printpsv(A);
    r = s.pancakeSort(A);
    cout << "result ";
    printpsv(r); // expect empty line
    assert( r.size() == 0);

    A = {3,2,4,1};
    printpsv(A);
    r = s.pancakeSort(A);
    cout << "result ";
    printpsv(r); // expect 3,4,2,3,2
    assert( r.size() <= A.size() * 10);

    A = {2,1};
    printpsv(A);
    r = s.pancakeSort(A);
    cout << "result ";
    printpsv(r); // expect 1
    assert( r.size() <= A.size() * 10);

    A = {1,3,2,4};
    printpsv(A);
    r = s.pancakeSort(A);
    cout << "result ";
    printpsv(r); // expect 2,3,2
    assert( r.size() <= A.size() * 10);

    A = {2,1};
    printpsv(A);
    r = s.pancakeSort(A);
    cout << "result ";
    printpsv(r); // expect 2
    assert( r.size() <= A.size() * 10);

    A = {1,2};
    printpsv(A);
    r = s.pancakeSort(A);
    cout << "result ";
    printpsv(r); // expect empty line
    assert( r.size() <= A.size() * 10);
   
    return 0;
}
