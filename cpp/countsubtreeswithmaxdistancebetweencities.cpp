
// Count Subtrees With Max Distance Between Cities
// https://leetcode.com/contest/weekly-contest-210/problems/count-subtrees-with-max-distance-between-cities/
// https://leetcode.com/problems/count-subtrees-with-max-distance-between-cities/



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
#include <bitset>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
private:
    int getDiameter(int from, int start, int end, int dic[], int subtree) {
        int u = dic[start];
        if( (u >> end) & 1 ) return 1;

        int r = 0;
        for(int i = 0; i < 15; ++i) {
            if( i == from) continue; // avoid circular reference
            if( ((subtree >> i) & 1) == 0 ) continue; // not in subtree
            if( (u >> i) & 1 ) {
                r = getDiameter(start,i,end,dic,subtree);
                if( r != 0 ) break; // found it
            }
        }
        return r == 0 ? 0 : r + 1;
    }

    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }
public:
    vector<int> countSubgraphsForEachDiameter(int n, vector<vector<int>>& edges) {
        // 2 <= n <= 15
        if( n == 2 ) return {1}; // base case

        // init list of cities (zero indexed!)
        // holds a bitmask per city, a set bit indicates a direct neighbor
        int dic[15];
        for(int i = 0; i < 15; ++i) dic[i] = 0;

        // process edges
        for(auto i = 0; i < n - 1; ++i) {
            dic[edges[i][0]-1] ^= 1 << (edges[i][1]-1); // connecting u -> v
            dic[edges[i][1]-1] ^= 1 << (edges[i][0]-1); // connecting v -> u
        }

        // debug
        // for(int i = 0; i < n; ++i)
        //     cout << "vertice " << i << " " << bitset<15>(dic[i]).to_string() << endl;

        vector<int> r(n-1,0);
        r[0] = n-1; // always n-1 distinct subtrees for diameter 1 for n nodes

        // process all possible subtrees
        int mask = 0;
        int maxdiameter,diameter;
        for(int k = 0; k < pow(2,n); ++k) {
            if( countSetBits(k) < 3 ) continue;
            // let each city in subtree be the root
            // record length of path from root to each other city
            // if this subtree is not valid, the return will be 0

            // cout << "subtree " << bitset<15>(k).to_string() << endl;

            maxdiameter = 0;
            bool isSubtree = true;
            for(int i = 0; i < 14; ++i) {
                if( ((k >> i) & 1) == 0 ) continue;
                for(int j = i + 1; j < 15; ++j) {
                    if( ((k >> j) & 1) == 0 ) continue;
                    diameter = getDiameter(-1,i,j,dic,k);
                    if( diameter == 0 ) {
                        isSubtree = false;
                        break;
                    }
                    maxdiameter = max(maxdiameter,diameter);
                }
                if( !isSubtree ) break;
            }
            if( isSubtree && maxdiameter > 1 ) ++r[maxdiameter-1];
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
    int n;
    vector<vector<int>> edges;
    vector<int> r, expected;

    // Example 1 Leetcode
    edges = {{1,2},{2,3},{2,4}};
    n = 4;
    r = s.countSubgraphsForEachDiameter(n,edges);
    cout << "result ";
    for(int i : r) cout << i << " ";
    cout << endl;
    expected = {3,4,0};
    assert(r == expected);
//return 0;
    // Example 2 Leetcode
    edges = {{1,2}};
    n = 2;
    r = s.countSubgraphsForEachDiameter(n,edges);
    cout << "result ";
    for(int i : r) cout << i << " ";
    cout << endl;
    expected = {1};
    assert(r == expected);

    // Example 2 Leetcode
    edges = {{1,2},{2,3}};
    n = 3;
    r = s.countSubgraphsForEachDiameter(n,edges);
    cout << "result ";
    for(int i : r) cout << i << " ";
    cout << endl;
    expected = {2,1};
    assert(r == expected);

    // Example 1 Axel
    edges = {{1,2},{2,3},{3,4}};
    n = 4;
    r = s.countSubgraphsForEachDiameter(n,edges);
    cout << "result ";
    for(int i : r) cout << i << " ";
    cout << endl;
    expected = {3,2,1};
    assert(r == expected);

    // Example 2 Axel
    edges = {{1,2},{1,3},{1,4},{1,5},{1,6},{1,7},{1,8},{1,9},{1,10},{1,11},{1,12},{1,13},{1,14},{1,15}};
    n = 15;
    start = chrono::system_clock::now();
    r = s.countSubgraphsForEachDiameter(n,edges);
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "elapsed_seconds " << elapsed_seconds.count() << endl;
    cout << "result ";
    for(int i : r) cout << i << " ";
    cout << endl;
    expected = {14,16369,0,0,0,0,0,0,0,0,0,0,0,0};
    assert(r == expected);

    // Example 3 Axel
    edges = {{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15}};
    n = 15;
    start = chrono::system_clock::now();
    r = s.countSubgraphsForEachDiameter(n,edges);
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "elapsed_seconds " << elapsed_seconds.count() << endl;
    cout << "result ";
    for(int i : r) cout << i << " ";
    cout << endl;
    expected = {14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    assert(r == expected);

    return 0;
}
