
// 3587. Minimum Adjacent Swaps to Alternate Parity
// https://leetcode.com/problems/minimum-adjacent-swaps-to-alternate-parity/





class Solution {
private:
    int solve(vector<int>& _nums, int n, int first, stack<int> odds, stack<int> evens) {
        vector<bool> swapped(n, false);
        int ret = 0;
        int cur = first;
        for(int i = 0; i < n; ++i) {
            while( !odds.empty() && odds.top() <= i )
                odds.pop();
            while( !evens.empty() && evens.top() <= i )
                evens.pop();

            int real = _nums[i];
            if( swapped[i] )
                real = !real;

            if( real != cur ) {
                // we must 'swap'
                if( cur ) {
                    int next_odd = odds.top();
                    odds.pop();
                    int dist = next_odd - i;
                    ret += dist;
                    swapped[next_odd] = !swapped[next_odd];
                } else {
                    int next_even = evens.top();
                    evens.pop();
                    int dist = next_even - i;
                    ret += dist;
                    swapped[next_even] = !swapped[next_even];
                }
            }

            cur = !cur;
        }

        return ret;
    }

public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0;
        if( n == 2 )
            return nums[0] % 2 != nums[1] % 2 ? 0 : -1;

        // quick check
        //     if n is odd, we must have abs(evens-odds) = 1
        //     if n is odd, if evens > odds, then e,o,e,o,...o,e
        //                  else                  o,e,o,e,...e,o
        //     if n is even, we must have same number of even and odds
        //     if n is even, we can start with even or odd

        vector<int> _nums(n,0);
        stack<int> odds;
        stack<int> evens;
        for(int i = n-1; i >= 0; --i) {
            if( nums[i] % 2 ) {
                odds.push(i);
                _nums[i] = 1;
            } else {
                evens.push(i);
            }
        }

        int first;
        if( n % 2 ) {
            if( abs((int)evens.size() - (int)odds.size()) != 1 )
                return -1;
            first = evens.size() > odds.size() ? 0 : 1;
            return solve(_nums, n, first, odds, evens);

        } else {
            if( evens.size() != odds.size() )
                return -1;
            int a = solve(_nums, n, 0, odds, evens);
            int b = solve(_nums, n, 1, odds, evens);
            return min(a,b);
        }
    }
};
