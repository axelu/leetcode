#include <vector>
#include <iostream>
#include <cassert>


using namespace std;

vector<int> insertionsort(vector<int>& v) {
    int n = v.size();
    if( n < 2 ) return v;
    
    int i = 1;
    int j,k;
    for(; i < n; ++i) {
        k = v[i];
        j = i-1;
        while( j > -1 && v[j] > k  ) {
             v[j+1] = v[j];
            --j;
        }
        v[j+1] = k;
        for(int p : v)
            cout << p << " ";
        cout << endl;
    }
    
    return v;
}


int main() {
    vector<int> a{2,19,13,5,10,8,3,25,1,13};
    vector<int> r = insertionsort(a);

    // expected
    vector<int> b{1,2,3,5,8,10,13,13,19,25};
    assert(r == b);


    return 0;
}
