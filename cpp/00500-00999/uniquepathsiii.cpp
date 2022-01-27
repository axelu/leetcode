
// day 20 September 2020 challenge
// 980. Unique Paths III
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/556/week-3-september-15th-september-21st/3466/
// https://leetcode.com/problems/unique-paths-iii/


#include <iostream>
#include <cassert>

#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {

        // find starting point
        pair<int,int> start = findStart(grid);
        // cout << "start x " << start.first << " y " << start.second << endl;

        // determine number of cells to visit so we know when
        // we arrive at 2 that the path is actually complete
        // grid.length * grid[0].length - number of obstacles
        // Note: will count start and finish
        int numberObstacles = getNumberObstacles(grid);
        // cout << "numberObstacles " << numberObstacles << endl;
        xend = grid[0].size();
        yend = grid.size();
        nodesToVisit = xend * yend - numberObstacles;
        // cout << "nodesToVisit " << nodesToVisit << endl;

        pathCount = 0;
        nodesVisited = 0;
        _walk(start.first, start.second, grid);

        return pathCount;
    }
private:
    int pathCount;
    int xend;
    int yend;
    int nodesToVisit;
    int nodesVisited;

    pair<int,int> findStart(vector<vector<int>>& grid) {
        pair<int,int> r;
        for(auto ity = grid.begin(); ity != grid.end(); ++ity) {
            auto f = find(ity->begin(),ity->end(), 1);
            if( f != ity->end() ) {
                r.first = distance(ity->begin(), f);
                r.second = distance(grid.begin(), ity);
                break;
            }
        }
        return r;
    }

    int getNumberObstacles(vector<vector<int>>& grid) {
        int r = 0;
        for(auto vi : grid) {
            r += count(vi.begin(),vi.end(), -1);
        }
        return r;
    }

    void _walk(int x, int y, vector<vector<int>>& grid) {
        // cout << "x " << x << " y " << y << endl;

        // outside
        if( x < 0 || x == xend || y < 0 || y == yend ) return;

        // obstacle
        if( grid[y][x] == -1 ) return;

        // visited
        if( grid[y][x] == -2 ) return;

        // start
        if( grid[y][x] == 1 ) {
            if( nodesVisited > 0 )
                return;
        }

        // end
        if( grid[y][x] == 2 ) {
            ++nodesVisited;
            if( nodesVisited == nodesToVisit )
                ++pathCount;
            -- nodesVisited;
            return;
        }

        ++nodesVisited;
        grid[y][x] = -2; // mark as visited;

        // north y - 1 aka up
        _walk(x, y - 1, grid);
        // east x + 1 aka right
        _walk(x + 1, y, grid);
        // south y + 1 aka down
        _walk(x, y + 1, grid);
        // west x - 1 aka left
        _walk(x - 1, y, grid);

        --nodesVisited;
        grid[y][x] = 0; // reset to not visited;
    }
};

int main() {

    Solution s;
    vector<vector<int>> grid;

    grid = {{1,0,0,0},{0,0,0,0},{0,0,2,-1}};
    assert(s.uniquePathsIII(grid) == 2);

    grid = {{1,0,0,0},{0,0,0,0},{0,0,0,2}};
    assert(s.uniquePathsIII(grid) == 4);

    grid = {{0,1},{2,0}};
    assert(s.uniquePathsIII(grid) == 0);

    return 0;
}
