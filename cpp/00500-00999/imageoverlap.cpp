
// day 6 September 2020 challenge
// 835. Image Overlap
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/554/week-1-september-1st-september-7th/3450/
// https://leetcode.com/problems/image-overlap/

#include <iostream>
#include <cassert>

#include <vector>
#include <utility>
#include <map>

using namespace std;

class Solution {
public:
    int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {

        vector<pair<int, int>> onePxsA = onePxs(A);
        vector<pair<int, int>> onePxsB = onePxs(B);

        int overlap = 0;

        map<pair<int,int>,int> count;

        for(auto a : onePxsA) {
            for(auto b : onePxsB) {
                pair<int, int> v = make_pair(b.first - a.first, b.second - a.second);

                auto p = count.insert({v,1});
                if( !p.second )
                    ++p.first->second;

                overlap = max(overlap, p.first->second);
            }
        }

        return overlap;
    }
private:
    vector<pair<int, int>> onePxs(vector<vector<int>>& img) {

        vector<pair<int, int>> r;
        size_t imgsz = img.size(); // square matrices
        for (int z = 0; z < imgsz; ++z)
            for (int s = 0; s < imgsz; ++s)
                if (img[z][s] == 1)
                    r.push_back(make_pair(z, s));

        return r;
    }
};

int main() {
    Solution s;

    // [[1,1,0],[0,1,0],[0,1,0]]
    // [[0,0,0],[0,1,1],[0,0,1]]
    vector<int> v111 = {1,1,0};
    vector<int> v112 = {0,1,0};
    vector<int> v113 = {0,1,0};
    vector<vector<int>> v11 = {v111,v112,v113};
    vector<int> v121 = {0,0,0};
    vector<int> v122 = {0,1,1};
    vector<int> v123 = {0,0,1};
    vector<vector<int>> v12 = {v121,v122,v123};

    assert(s.largestOverlap(v11,v12) == 3);

  return 0;
}
