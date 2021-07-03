#include <vector>
#include <iostream>
#include <cassert>
#include <climits>

// https://www.khanacademy.org/computing/computer-science/algorithms/merge-sort/a/overview-of-merge-sort

using namespace std;

void mergesort(vector<int>& v, int p, int r) {
    if(p < r) {
        // divide
        cout << "divide " << p << " " << r << endl;
        int q = p + ((r - p)/2);
        mergesort(v,p,q);
        mergesort(v,q+1,r);

        // combine aka merge
        cout << "merge  " << p << " " << r << endl;
        int n1 = q-p+1;
        int n2 = r-q;
        vector<long> L(n1+1);
        vector<long> R(n2+1);
        for(int i = 0; i < n1; ++i)
            L[i] = v[p+i];
        for(int i = 0; i < n2; ++i)
            R[i] = v[q+1+i];
        L[n1] = (long)INT_MAX+1;
        R[n2] = (long)INT_MAX+1;
        int i = 0;
        int j = 0;
        for(int k = p; k <= r; ++k) {
            if( L[i] <= R[j] ) {
                v[k] = L[i];
                ++i;
            } else {
                v[k] = R[j];
                ++j;
            }
        }
    }
}


int main() {
    vector<int> a{2,19,13,5,10,8,3,3,25,1,13};
    mergesort(a,0,a.size()-1);

    // expected
    vector<int> b{1,2,3,3,5,8,10,13,13,19,25};
    assert(a == b);


    return 0;
}
