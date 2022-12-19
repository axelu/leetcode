
// 956. Tallest Billboard
// https://leetcode.com/problems/tallest-billboard/



class Solution {
private:
    int n;
    int * _rods;

    int mem[10001][20];

    int rec(int diff, int i) {
        if( i == n )
            return diff == 0 ? 0 : INT_MIN;

        if( mem[diff+5000][i] )
            return mem[diff+5000][i];

        // we have a choice
        //     don't use our rod at all
        //     use the rod on side A
        //     use the rod on side B

        int ret = rec(diff,i+1);

        ret = max(ret, _rods[i] + rec(diff+_rods[i],i+1));

        ret = max(ret, rec(diff - _rods[i],i+1));

        return mem[diff+5000][i] = ret;
    }


public:
    int tallestBillboard(vector<int>& rods) {
        // rephrasing the problem
        // partition rods into two subsets with
        // subset1sum == subset2sum and maximized

        n = rods.size();
        _rods = rods.data();

        memset(mem,0,sizeof mem);
        return rec(0,0);
    }
};
