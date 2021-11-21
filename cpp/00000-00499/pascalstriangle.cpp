#include <iostream>
#include <cassert>

#include <vector>

using namespace std;

// 118. Pascal's Triangle
// https://leetcode.com/problems/pascals-triangle

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        if ( numRows == 0 ) return {};
        
        vector<vector<int>> r;
        r.reserve(numRows);
        r.push_back({1});
        if ( numRows == 1 ) return r;
    
        vector<int> p;
        p.reserve(2);
        p.push_back(1);
        p.push_back(1);
        r.push_back(p);
        if ( numRows == 2 ) return r;
        /*        
        for(int i = 3; i <= numRows; ++i) {
            vector<int>* v = new vector<int>;
            v->reserve(i);
            v->push_back(1);            
            for(auto it = r[i-2].begin(); it <= r[i-2].end()-2; ++it) {
                v->push_back(*it + *(it+1));
            }
            v->push_back(1);
            r.push_back(*v);
        }
        */
        for(int i = 3; i <= numRows; ++i) {
            vector<int> v;
            v.reserve(i);
            v.push_back(1);            
            for(auto it = r[i-2].begin(); it <= r[i-2].end()-2; ++it) {
                v.push_back(*it + *(it+1));
            }
            v.push_back(1);
            r.push_back(v);
        }

        return r;
    }
};

int main() {

    Solution s;

    vector<vector<int>> v = s.generate(4);
    for(auto vi : v) {
        cout << "[";
        for(auto i : vi) {
            cout << i << ",";
        }
        cout << "],";
    }
    cout << endl;


    return 0;
}
