
// 1402. Reducing Dishes
// https://leetcode.com/problems/reducing-dishes/

class Solution {
private:
    int mem[501][501];

    int rec(vector<int>& satisfaction, int n, int i, int k) {
        if( i == n )
            return 0;

        if( mem[i][k] != -1 )
            return mem[i][k];
        // we have a choice
        //   don't make the current dish
        //   make the current dish or

        int a = rec(satisfaction,n,i+1,k);
        int b = k * satisfaction[i] + rec(satisfaction,n,i+1,k+1);

        return mem[i][k] = max({a,b,0});
    }

public:
    int maxSatisfaction(vector<int>& satisfaction) {
        int n = satisfaction.size();
        sort(satisfaction.begin(),satisfaction.end());

        memset(mem,-1,sizeof mem);
        return rec(satisfaction,n,0,1);
    }
};
