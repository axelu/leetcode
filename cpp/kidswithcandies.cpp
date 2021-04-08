
// 1431. Kids With the Greatest Number of Candies
// https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        auto it = begin(candies);
        auto ite = end(candies);
        int mx = *max_element(it,ite);
        vector<bool> r;
        for(; it != ite; ++it)
            if( *it + extraCandies >= mx ) {
                r.push_back(true);
            } else {
                r.push_back(false);
            }

        return r;
    }
};
