
// 2250. Count Number of Rectangles Containing Each Point
// https://leetcode.com/problems/count-number-of-rectangles-containing-each-point/

// improved solution
// instead of using a simple array to store lengths at a certain heights
// we store in a binary index tree, which saves us from having to check
// every index meaning height of point, which makes it run much faster

class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
        // rectangles[i] = [li, hi] <- top right corner, bottom left corner [0,0]
        // points[j]     = [xj, yj]
        // 1 <= li, xj <= 10^9
        // 1 <= hi, yj <= 100
        // 1 <= rectangles.length, points.length <= 5 * 10^4
        // with that we have max 50000+1 (+1 because of 0) distinct li values only

        sort(rectangles.begin(),rectangles.end());

        vector<int> bit[101]; // Binary Index Tree BIT

        for(auto& v: rectangles)
            for(int idx = v[1]; idx > 0; idx -= idx & -idx)
                bit[idx].push_back(v[0]);

        int k = points.size();
        vector<int> ans(k,0);

        for(int i = 0; i < k; ++i) {
            int idx = points[i][1];
            while(idx <= 100) {
                 // binary search
                int s = 0;
                int e = bit[idx].size();
                int mid;
                while(s < e) {
                    mid = s + ((e-s)/2);
                    if( points[i][0] <= bit[idx][mid] )
                        e = mid;
                    else
                        s = mid+1;
                }
                if( s < bit[idx].size() && bit[idx][s] < points[i][0] )
                    ++s;
                ans[i] += bit[idx].size()-s;
                idx += (idx & -idx);
            }
        }

        return ans;
    }
};





// original solution passes

class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
        // rectangles[i] = [li, hi] <- top right corner, bottom left corner [0,0]
        // points[j]     = [xj, yj]
        // 1 <= li, xj <= 10^9
        // 1 <= hi, yj <= 100
        // 1 <= rectangles.length, points.length <= 5 * 10^4
        // with that we have max 50000+1 (+1 because of 0) distinct li values only

        sort(rectangles.begin(),rectangles.end());
        vector<int> b[101];
        for(auto& v: rectangles)
            b[v[1]].push_back(v[0]);

        int k = points.size();
        vector<int> ans(k,0);

        for(int i = 0; i < k; ++i) {
            for(int j = points[i][1]; j < 101; ++j) {
                // binary search
                int s = 0;
                int e = b[j].size();
                int mid;
                while(s < e) {
                    mid = s + ((e-s)/2);
                    if( points[i][0] <= b[j][mid] )
                        e = mid;
                    else
                        s = mid+1;
                }
                if( s < b[j].size() && b[j][s] < points[i][0] )
                    ++s;
                ans[i] += b[j].size()-s;
            }
        }

        return ans;
    }
};
