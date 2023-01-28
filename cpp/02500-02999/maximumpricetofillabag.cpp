
// 2548. Maximum Price to Fill a Bag
// https://leetcode.com/problems/maximum-price-to-fill-a-bag/



class Solution {
public:
    double maxPrice(vector<vector<int>>& items, int capacity) {
        // to maximize by price, we want to stuff the greatest price/weight in first - greedy

        sort(items.begin(),items.end(),[](vector<int>& a, vector<int>& b){
           return (double)a[0]/a[1] > (double)b[0]/b[1];
        });

        double ans = 0.0;
        double f = capacity;
        int n = items.size();
        for(int i = 0; i < n; ++i) {
            // stuff as much as we can into the remaining capacity
            double t = (double)f/items[i][1];
            if( t > 1 ) {
                ans += items[i][0];
                f -= items[i][1];
            } else {
                ans += items[i][0] * t;
                f -= items[i][1];
                break;
            }
        }

        return f > 0 ? -1 : ans;  // TODO compare float to integer?
    }
};
