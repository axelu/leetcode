
// 3588. Find Maximum Area of a Triangle
// https://leetcode.com/problems/find-maximum-area-of-a-triangle/




class Solution {
public:
    long long maxArea(vector<vector<int>>& coords) {
        int x_min = INT_MAX;
        int x_max = INT_MIN;
        int y_min = INT_MAX;
        int y_max = INT_MIN;

        map<int,set<int>> xs_by_y;
        map<int,set<int>> ys_by_x;

        for(auto& p: coords) {
            int x = p[0];
            x_min = min(x_min, x);
            x_max = max(x_max, x);

            int y = p[1];
            y_min = min(y_min, y);
            y_max = max(y_max, y);

            xs_by_y[y].insert(x);
            ys_by_x[x].insert(y);
        }

        long long ans = 0LL;

        for(auto it = xs_by_y.begin(); it != xs_by_y.end(); ++it) {
            int y = it->first;
            int mn_x = *(it->second.begin());
            int mx_x = *(it->second.rbegin());
            long long base = mx_x - mn_x;

            ans = max(ans, base * (long long)abs(y-y_min));
            ans = max(ans, base * (long long)abs(y-y_max));
        }

        for(auto it = ys_by_x.begin(); it != ys_by_x.end(); ++it) {
            int x = it->first;
            int mn_y = *(it->second.begin());
            int mx_y = *(it->second.rbegin());
            long long base = mx_y - mn_y;

            ans = max(ans, base * (long long)abs(x-x_min));
            ans = max(ans, base * (long long)abs(x-x_max));
        }

        return ans != 0LL ? ans : -1LL;
    }
};
