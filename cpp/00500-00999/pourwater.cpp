
// 755. Pour Water
// https://leetcode.com/problems/pour-water/



class Cmpl {
public:
  bool operator()(const array<int,2>& a, const array<int,2>& b){
        if( a[0] > b[0] ) {
            return true;
        } else if( a[0] == b[0] ) {
            if( a[1] < b[1] ) {
                return true;
            }
        }
        return false;
    }
};

class Cmpr {
public:
  bool operator()(const array<int,2>& a, const array<int,2>& b){
        if( a[0] > b[0] ) {
            return true;
        } else if( a[0] == b[0] ) {
            if( a[1] > b[1] ) {
                return true;
            }
        }
        return false;
    }
};

class Solution {
private:
    int idxl;
    priority_queue<array<int,2>,vector<array<int,2>>,Cmpl> pql;

    void maintainl(vector<int>& heights, int n, int k) {
        if( idxl >= 0 && pql.empty() && heights[idxl] <= heights[k] ) {
            pql.push({heights[idxl],idxl});
            --idxl;
        }
        while( idxl >= 0 && !pql.empty() && heights[idxl] <= pql.top()[0] ) {
            pql.push({heights[idxl],idxl});
            --idxl;
        }
    }

    int idxr;
    priority_queue<array<int,2>,vector<array<int,2>>,Cmpr> pqr;

    void maintainr(vector<int>& heights, int n, int k) {
        if( idxr < n && pqr.empty() && heights[idxr] <= heights[k] ) {
            pqr.push({heights[idxr],idxr});
            ++idxr;
        }
        while( idxr < n && !pqr.empty() && heights[idxr] <= pqr.top()[0] ) {
            pqr.push({heights[idxr],idxr});
            ++idxr;
        }
    }

public:
    vector<int> pourWater(vector<int>& heights, int volume, int k) {
        // edge case
        if( volume == 0 )
            return heights;

        int n = heights.size();

        // array<int,2> height, index

        // left
        idxl = k-1;
        maintainl(heights,n,k);

        // right
        idxr = k+1;
        maintainr(heights,n,k);

        // let it rain
        for(int i = 1; i <= volume; ++i) {

            // try left
            if( !pql.empty() && pql.top()[0] < heights[k] ) {
                auto p = pql.top();
                pql.pop();
                ++p[0];
                ++heights[p[1]]; // update heights
                pql.push(p);
                maintainl(heights,n,k);
                continue;
            }

            // try right
            if( !pqr.empty() && pqr.top()[0] < heights[k] ) {
                auto p = pqr.top();
                pqr.pop();
                ++p[0];
                ++heights[p[1]]; // update heights
                pqr.push(p);
                maintainr(heights,n,k);
                continue;
            }

            ++heights[k];
            maintainl(heights,n,k);
            maintainr(heights,n,k);
        }

        return heights;
    }
};
