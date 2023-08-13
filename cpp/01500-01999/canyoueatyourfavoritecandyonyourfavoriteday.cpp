
// 1744. Can You Eat Your Favorite Candy on Your Favorite Day?
// https://leetcode.com/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/



class Solution {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        // queries[i] = [favoriteTypei, favoriteDayi, dailyCapi]

        int n = candiesCount.size();
        int q_sz = queries.size();

        vector<bool> ans(q_sz,false);

        // question rephrased
        // can we eat all candies type [0,favoriteType-1] by favoriteDay?
        // maybe some candies of type 0 to favoriteType-1 even on our favoriteDay
        // example
        // candiesCount = {11,100}, queries = {{1,3,3}} => ans true
        // candiesCount = {12,100}, queries = {{1,3,3}} => ans false

        long prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + candiesCount[i-1];

        for(int i = 0; i < q_sz; ++i) {
            int favoriteType = queries[i][0];
            int favoriteDay = queries[i][1];
            int dailyCap = queries[i][2];

            // cout << prefixSum[favoriteType+1] << endl;
            // cout << prefixSum[favoriteType+1] / dailyCap << endl;
            // cout << prefixSum[favoriteType+1] % dailyCap << endl;

            if( prefixSum[favoriteType] / dailyCap <= favoriteDay &&
                prefixSum[favoriteType+1] > favoriteDay ) {

                ans[i] = true;

            } else if( favoriteType == 0 &&
                       candiesCount[0] > favoriteDay ) {

                ans[i] = true;
            }
        }

        return ans;
    }
};
