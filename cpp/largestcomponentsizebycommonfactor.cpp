
// Largest Component Size by Common Factor
// https://leetcode.com/problems/largest-component-size-by-common-factor/



#include <iostream>
#include <cassert>

#include <vector>
#include <numeric>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <cmath>

using namespace std;

// kicker explanation here
// https://www.hackerearth.com/practice/notes/disjoint-set-union-union-find/

class Solution {
public:
    int largestComponentSize(vector<int>& A) {
        // if( A.size() == 1 ) return 1;
        parent.clear(); // only needed for our development
        size.clear(); // only needed for our development
        // get max element so we can initialize the vector<int> we will use to
        // keep track of the connectivity of our elements.  As the max element
        // could be a prime, the max element determines the size for the vector.
        int me = *max_element(A.begin(), A.end());

        // initialize the parent vector with every node connected to itself,
        // parent[k] = k
        for(int k = 0; k <= me; ++k) {
            parent.push_back(k);
            size.push_back(0);
        }

        // create connectivity between our elements based on their prime factors
        for (int k : A) {
			int a = k;
			for (int i = 2; i * i <= k; ++i)
				if (k % i == 0) {
					while (k % i == 0)
						k /= i;
                    unite(i, a);
				}
			if (k > 1) {
				unite(k, a);
            }
		}

        // get connected component size by going through each element in the array, finding
        // its parent and incrementing the count on the parent, because that will count
        // how many of our elements are part of that component.
        int r = 0;
        for (int k : A)
			r = max(r, ++size[findRoot(k)]);

        return r;
    }
private:
    vector<int> parent;
    vector<int> size;

    int findRoot(int i) {
		// chase parent of current element until it reaches root

        while(parent[i] != i) {
            // path compression
            // set each i to point to its grandparent
            // (thereby halving the path length), where i
            // is the node which comes in between path,
            // while computing root
            parent[i] = parent[parent[i]] ;
            i = parent[i];
        }
		return i;
	}

	void unite(int p, int c) {
		p = findRoot(p);
		c = findRoot(c);
        if( p == c ) return;
		parent[c] = p;
	}
};

int main() {
    Solution s;
    vector<int> A;

    cout << "{4}" << endl;
    A = {4};
    // cout << s.largestComponentSize(A) << endl;
    assert(s.largestComponentSize(A) == 1);

    cout << "{4,6,15,35}" << endl;
    A = {4,6,15,35};
    // cout << s.largestComponentSize(A) << endl;
    assert(s.largestComponentSize(A) == 4);

    cout << "{20,50,9,63}" << endl;
    A = {20,50,9,63};
    // cout << s.largestComponentSize(A) << endl;
    assert(s.largestComponentSize(A) == 2);

    cout << "{2,3,6,7,4,12,21,39}" << endl;
    A = {2,3,6,7,4,12,21,39};
    // cout << s.largestComponentSize(A) << endl;
    assert(s.largestComponentSize(A) == 8);

    // case 6/100 initial error: time limit exceeded
    cout << "{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19}" << endl;
    A = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    // cout << s.largestComponentSize(A) << endl;
    assert(s.largestComponentSize(A) == 14);

    // case 31 initial error: wrong answer (I had 5, expected is 6)
    cout << "{1,2,3,4,5,6,7,8,9}" << endl;
    A = {1,2,3,4,5,6,7,8,9};
    // cout << s.largestComponentSize(A) << endl;
    assert(s.largestComponentSize(A) == 6);

    // case 45 initial error: wrong anwer (I had 8, expected is 9)
    cout << "{32,5,8,11,13,78,61,16,83,22,28,93}" << endl;
    A = {32,5,8,11,13,78,61,16,83,22,28,93};
    // cout << s.largestComponentSize(A) << endl;
    assert(s.largestComponentSize(A) == 9);

    // case 46 initial error: time limit exceeded
    cout << "{64,866,838,300,906,843,172,398,472,718,246,536,89,383,213}" << endl;
    A = {64,866,838,300,906,843,172,398,472,718,246,536,89,383,213};
    // cout << s.largestComponentSize(A) << endl;
    assert(s.largestComponentSize(A) == 13);

    // case 59 initially wrong answer 3, expected is 4
    cout << "{83,99,39,11,19,30,31}" << endl;
    A = {83,99,39,11,19,30,31};
    // cout << s.largestComponentSize(A) << endl;
    assert(s.largestComponentSize(A) == 4);


    return 0;
}

