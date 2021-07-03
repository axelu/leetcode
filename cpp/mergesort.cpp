#include <vector>
#include <iostream>
#include <cassert>

// https://www.khanacademy.org/computing/computer-science/algorithms/merge-sort/a/overview-of-merge-sort

using namespace std;

vector<int> mergesort(vector<int>& v, int p, int r) {
    if( p == r ) {
        return {v[p]};
    }
    if( p > r ) {
        return {};
    }

    // divide
    cout << "divide " << p << " " << r << endl;
    int q = p + ((r - p)/2);
    vector<int> a = mergesort(v,p,q);
    vector<int> b = mergesort(v,q+1,r);

    // combine aka merge
    cout << "merge  " << p << " " << r << endl;
    int i = 0, j = 0, k = 0;
    vector<int> res(r-p+1);
    while( i < a.size() && j < b.size() ) {
        if( a[i] < b[j] ) {
            res[k] = a[i];
            ++i;
        } else {
            res[k] = b[j];
            ++j;
        }
        ++k;
    }
    while( i < a.size() ) {
        res[k] = a[i];
        ++i;
        ++k;
    }
    while( j < b.size() ) {
        res[k] = b[j];
        ++j;
        ++k;
    }

    return res;
}


int main() {
    vector<int> a{2,19,13,5,10,8,3,25,1,13};
    vector<int> r = mergesort(a,0,a.size()-1);

    // expected
    vector<int> b{1,2,3,5,8,10,13,13,19,25};
    assert(r == b);


    return 0;
}
