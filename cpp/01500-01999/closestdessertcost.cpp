
// 1774. Closest Dessert Cost
// https://leetcode.com/problems/closest-dessert-cost/





class Solution {
private:
    int minDiff;

    int mem[10][10000];

    void rec(vector<int>& toppingCosts, int m, int pos, int rem) {
        // cout << "rec pos " << pos << " rem " << rem << endl;
        if( abs(rem) < abs(minDiff) )
            minDiff = rem;
        else if( abs(rem) == abs(minDiff) ) {
            if( rem > 0 )
                minDiff = rem;
        }

        if( rem < 0 || pos == m )
            return;

        if( mem[pos][rem] )
            return;

        mem[pos][rem] = 1;

        // we have a choice
        // don't add the current topping
        // add the current topping 1 time
        // add the current topping 2 times

        rec(toppingCosts,m,pos+1,rem);
        rec(toppingCosts,m,pos+1,rem-toppingCosts[pos]);
        rec(toppingCosts,m,pos+1,rem-2*toppingCosts[pos]);

    }
public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        int n = baseCosts.size();
        int m = toppingCosts.size();

        sort(begin(toppingCosts),end(toppingCosts));
        memset(mem,0,sizeof mem);

        minDiff = INT_MAX;
        int base;
        for(int i = 0; i < n; ++i) { // for each base
            base = baseCosts[i];

            if( base > target ) {
                // no need to add any toppings
                int rem = target-base; // less than 0
                if( abs(rem) < abs(minDiff) )
                    minDiff = rem;
                continue;
            } else if( base == target ) {
                return target;
            }

            rec(toppingCosts,m,0,target-base);
        }

        return target-minDiff;
    }
};
