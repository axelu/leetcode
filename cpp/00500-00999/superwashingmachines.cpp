
// 517. Super Washing Machines
// https://leetcode.com/problems/super-washing-machines/





/*
 * example [9,1,8,8,9] test case 116/120
 *  step 1  8 3 8 8 8
 *  step 2  7 5 8 8 7
 *  step 3  7 6 8 7 7
 *  step 4  7 7 7 7 7
 */

class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int n = machines.size();
        if( n == 1 )
            return 0;

        // the number of dresses must be a
        // multiple of the number of machines
        int nbrDresses = 0;
        for(int i = 0; i < n; ++i)
            nbrDresses += machines[i];

        if( nbrDresses == 0 )
            return 0;
        if( nbrDresses % n != 0 )
            return -1;

        int target = nbrDresses / n; // dresses we need in each washing machine
        int mxOverTarget = 0;
        int ans = 0;
        int surplus = 0;
        for(int i = 0; i < n; ++i) {
            // cout << "i " << i << " machines[i] " << machines[i];

            mxOverTarget = max(mxOverTarget,machines[i]-target);
            surplus += machines[i] - target;

            ans = max({ans,mxOverTarget,abs(surplus)});

        }

        return ans;
    }
};
