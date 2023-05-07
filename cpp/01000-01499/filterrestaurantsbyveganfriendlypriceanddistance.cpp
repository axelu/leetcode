
// 1333. Filter Restaurants by Vegan-Friendly, Price and Distance
// https://leetcode.com/problems/filter-restaurants-by-vegan-friendly-price-and-distance/



class Solution {
public:
    vector<int> filterRestaurants(vector<vector<int>>& restaurants, int veganFriendly, int maxPrice, int maxDistance) {

        // filter and transform
        vector<vector<int>> out;
        for(auto& v: restaurants) {
            if( v[2] >= veganFriendly && v[3] <= maxPrice && v[4] <= maxDistance) {
                out.push_back({v[0],v[1]});
            }
        }

        // sort
        sort(out.begin(),out.end(),[](const vector<int>& a, const vector<int>& b){
            if( a[1] > b[1] ) {
                return true;
            } else if( a[1] == b[1] ) {
                if( a[0] > b[0] ) {
                    return true;
                }
            }
            return false;
        });

        // transform
        vector<int> ans;
        for(auto& v: out)
            ans.push_back(v[0]);

        return ans;
    }
};
