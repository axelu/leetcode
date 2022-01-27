
// 575. Distribute Candies
// https://leetcode.com/problems/distribute-candies/
// day 1 march 2021 challenge
// https://leetcode.com/explore/featured/card/march-leetcoding-challenge-2021/588/week-1-march-1st-march-7th/3657/




class Solution {
public:
    int distributeCandies(vector<int>& candyType) {
        int n = candyType.size();
        unordered_set<int> us;
        for(int i = 0; i < n; ++i)
            us.insert(candyType[i]);
        int nbrDifferentCandy = us.size();
        return nbrDifferentCandy > n/2 ? n/2 : nbrDifferentCandy;
    }
};
