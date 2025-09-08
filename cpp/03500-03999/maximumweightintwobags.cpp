
// 3647. Maximum Weight in Two Bags
// https://leetcode.com/problems/maximum-weight-in-two-bags/





class Solution {
private:

    int mem[100][301][301];

    int rec(vector<int>& weights, int w1, int w2, int i, int b1, int b2) {
        // w1 and w2 max capacit7 of bag1 respectively of bag2
        // b1 and b2 weight in bag1 respectively of bag2
        int n = weights.size();
        if( i == n )
            return b1 + b2;

        if( mem[i][b1][b2] != -1 )
            return mem[i][b1][b2];

        // we have a choice
        //     skip OR
        //     load bag1 if it fits OR
        //     load bag2 if it fits

        int ret = rec(weights, w1, w2, i+1, b1, b2);

        if( weights[i] + b1 <= w1 )
            ret = max(ret, rec(weights, w1, w2, i+1, weights[i] + b1, b2));

        if( weights[i] + b2 <= w2 )
            ret = max(ret, rec(weights, w1, w2, i+1, b1, weights[i] + b2));

        return mem[i][b1][b2] = ret;
    }
public:
    int maxWeight(vector<int>& weights, int w1, int w2) {
        memset(mem,-1,sizeof mem);
        return rec(weights, w1, w2, 0, 0, 0);
    }
};
