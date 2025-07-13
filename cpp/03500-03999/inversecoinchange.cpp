
// 3592. Inverse Coin Change
// https://leetcode.com/problems/inverse-coin-change/





class Solution {
private:


    long can_make(vector<int> denominations, int pos, int amount, int target) {
        // return number of ways to make the target amount

        if( amount == target )
            return 1L;

        if( pos == denominations.size() )
            return 0L;

        // we have a choice
        //    don't take the denomination at cur pos OR
        //    take 1,2,3... of the cur denomination as long as less equal target

        long ret = 0L;

        for(int i = 0; amount + denominations[pos] * i <= target; ++i)
                ret += can_make(denominations, pos+1, amount + denominations[pos] * i, target);

        return ret;
    }

    int n;
    vector<int> curWays;
    vector<int> denominations;

    bool rec(vector<int>& numWays, int denomination) {
        if( denomination == n+1 )
            return true;

        // we have a choice
        //     don't pick the denomination OR
        //     pick the denomination (if we can)

        // if numWays[denomination] == 0, we can NOT pick
        // with the coins picked so far and pick,
        // we need to check any amounts >= denomination,
        // to make sure we are not violating numWays

        int target_ways = numWays[denomination];
        int curnbr_ways = curWays[denomination];
        if( target_ways == 0 || target_ways == curnbr_ways ) {
            // we cannot pick the denomination
            return rec(numWays, denomination+1);

        } else if( target_ways == curnbr_ways + 1 ) {
            // we must pick the denomination

            // update curWays and make sure it does not violate numWays
            for(int i = n; i > denomination; --i) { // amount
                int ways = curWays[i];

                // as we are picking, we must update
                int addend = 0;
                for(int f = 1; f * denomination <= i; ++f) {
                    int val = f * denomination;
                    int diff = i - val;
                    // how many times can we make diff?
                    addend += curWays[diff];
                }

                if( ways + addend > numWays[i] )
                    return false;

                curWays[i] = ways + addend;
            }
            ++curWays[denomination];
            denominations.push_back(denomination);
            return rec(numWays, denomination+1);

        }

        return false;
    }




public:
    vector<int> findCoins(vector<int>& numWays) {
        n = numWays.size();

        // coin denominations 1,2,3,...,n
        // we can have an unlimited supply of each
        // numWays is 1-indexed
        // how to read numWays;
        // let numWays[x] be y means that
        // we have y ways to make amount x
        // example: num[1] = 0 (1-indexed !!!) means
        //          that we do not have coins with value 1
        // example: num[2] = 1 means
        //          that we have 1 way to make value 2
        //          so we could either have 2 x coin with value 1 OR
        //                                  1 x coint with value 2


        // vector<int> denominations{2,4,6};
        // cout << can_make(denominations, 0, 0, 4) << endl;

        // to simplify, make numWays 0-indexed
        numWays.insert(numWays.begin(), 0);

        curWays.assign(n+1, 0);
        curWays[0] = 1;

        // cout << rec(numWays, 1) << endl;

        return rec(numWays, 1) ? denominations : vector<int>();
    }
};
