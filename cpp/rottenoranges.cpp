#include <iostream>
#include <cassert>

#include <vector>
#include <utility>

using namespace std;

// Rotting Oranges
// day 7 problem of the August 2020 challenge
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/550/week-2-august-8th-august-14th/3418/

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) { 
        max = 0;

        vector<pair<vector<vector<int>>::iterator, vector<int>::iterator>> r;

        vector<vector<int>>::iterator it1; // rows
        vector<int>::iterator it2; // columns

        for (it1 = grid.begin(); it1 != grid.end(); ++it1) {
            for (it2 = it1->begin(); it2 != it1->end(); ++it2) {
                if ( *it2 == 2 ) {
                    // debug
                    // cout << "found rotten orange at ";
                    // cout << "row " << it1 - grid.begin();
                    // cout << " column " << it2 - it1->begin() << endl;
                    max = -1;
                    r.push_back(make_pair(it1, it2));
                }
            }
        }

        if ( !r.empty() ) rot(grid, r);

        // debug
        // cout << "max before checking for remaining fresh oranges " << max << endl;

        // check for any remaining fresh oranges
        for (auto it1 = grid.begin(); it1 != grid.end(); ++it1) {
            for (auto it2 = it1->begin(); it2 != it1->end(); ++it2) {
                if (*it2 == 1) return -1;
            }
        }

        return max;
    }
private:

    int max;

    void rot(vector<vector<int>>& grid, vector<pair<vector<vector<int>>::iterator, vector<int>::iterator>> v) {

        int cmax = max;

        vector<pair<vector<vector<int>>::iterator, vector<int>::iterator>> r;

        for (auto p : v) {

            if ( *p.second != 0 && *p.second != 3 ) {
                // rot the organge
                *p.second = 3;
                if (cmax == max) max++;

                // calculate current column
                int current_column = p.second - p.first->begin();

                // up
                if ( p.first != grid.begin() ) {
                    r.push_back(make_pair(p.first - 1, (p.first-1)->begin() + current_column));
                }
                // left
                if( current_column > 0 ) {
                    r.push_back(make_pair(p.first, p.second - 1));
                }
                // right
                if( p.second + 1 != p.first->end() ) {
                    r.push_back(make_pair(p.first, p.second + 1));
                }
                // down
                if ( p.first + 1 != grid.end() ) {
                    r.push_back(make_pair(p.first + 1, (p.first+1)->begin() + current_column));
                }
            }
        }

        if ( !r.empty() ) {
            rot(grid, r);
        }
    }
};

int main() {

    Solution s;

    cout << "[[2,1,1],[1,1,0],[0,1,1]]" << endl;
    vector<int> v11 = {2,1,1};
    vector<int> v12 = {1,1,0};
    vector<int> v13 = {0,1,1};
    vector<vector<int>> v1 = {v11,v12,v13};
    assert(s.orangesRotting(v1) == 4);

    cout << "[[2,1,1],[0,1,1],[1,0,1]]" << endl;
    vector<int> v21 = {2,1,1};
    vector<int> v22 = {0,1,1};
    vector<int> v23 = {1,0,1};
    vector<vector<int>> v2 = {v21,v22,v23};
    assert(s.orangesRotting(v2) == -1);

    cout << "[[0,2]]" << endl;
    vector<int> v31 = {0,2};
    vector<vector<int>> v3 = {v31};
    assert(s.orangesRotting(v3) == 0);

    cout << "[[0]]" << endl;
    vector<int> v41 = {0};
    vector<vector<int>> v4 = {v41};
    assert(s.orangesRotting(v4) == 0);

    cout << "[[2,2,2,1,1]]" << endl;
    vector<int> v51 = {2,2,2,1,1};
    vector<vector<int>> v5 = {v51};
    assert(s.orangesRotting(v5) == 2);

    cout << "[[2,0,1,2,1,2]]" << endl;
    vector<int> v61 = {2,0,1,2,1,2};
    vector<vector<int>> v6 = {v61};
    assert(s.orangesRotting(v6) == 1);

    cout << "[[1,2,1,1,2,1,1]]" << endl;
    vector<int> v71 = {1,2,1,1,2,1,1};
    vector<vector<int>> v7 = {v71};
    // cout << s.orangesRotting(v7) << endl;
    assert(s.orangesRotting(v7) == 2);

    
    return 0;
}
