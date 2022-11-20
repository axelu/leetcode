
// 964. Least Operators to Express Number
// https://leetcode.com/problems/least-operators-to-express-number/


class Solution {
private:
    unordered_map<int,int> seen;

    int rec(const int x, const int target) {
        // cout << "rec target " << target << endl;
        if( target == 1 )
            return 1;
        if( target == x )
            return 0;
        if( x > target )
            if( x - target < target )
                return (x - target) * 2;
            else
                return target * 2 - 1;

        auto f = seen.find(target);
        if( f != seen.end() )
            return f->second;

        // we have a choice
        // at each step we can use *, /, + or minus

        int ans = INT_MAX;

        // multiplication
        long m = x;
        int a = 0; // count of * operators
        while( m < target ) {
            ++a;
            m *= x;
        }
        if( m == target ) {
            // our solution is: x * x * ... * x = target
            ans = a;
        } else {
            // we did overshoot, meaning m > target
            // our solution is: x * x .... * x - <something> = target
            // it makes only sense to further pursue this path
            // if we can get back to the target
            if( m - target < target )
                ans = a + 1 + rec(x,m - target); // adding 1 for the minus operator
        }

        // as we did overshoot, we now need
        // to explore m < target, so we are dividing m by x
        // our solution is: x * x .... * x + <something> = target
        m = m / x;
        ans = min(ans,a + rec(x,target - m));

        return seen[target] = ans;
    }

public:
    int leastOpsExpressTarget(int x, int target) {

        return rec(x,target);
    }
};
