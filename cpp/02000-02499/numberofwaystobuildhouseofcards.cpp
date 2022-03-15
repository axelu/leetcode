
// 2189. Number of Ways to Build House of Cards
// https://leetcode.com/problems/number-of-ways-to-build-house-of-cards/


class Solution {
private:

    int rec(int k, int l, int mem[][168]) {
        // cout << "in  k " << k << " l " << l << endl;
        // k is cards, l is runway, 1 <= l
        if( k <= 1 || k == 3 || k == 4 ) {
            return 0;
        } if( k == 2 ) {
            return 1;
        }

        if( mem[k][l] != -1 )
            return mem[k][l];

        // we have a choice
        // add to the current row till we are out of cards or reach
        // a point were only 2 or one card is left
        // build up
        // for building up, we have to have at least 2 triangles in the current row
        // we cannot build more triangles than we have runway or cards

        int ret = 0;
        // add to the current row
        int l_new = 1;
        int k_new = k - 2;
        while( k_new >= 3 && l_new < l ) {
            k_new -= 3;
            ++l_new;
        }

        if( k_new == 0 || k_new == 2 ) {
            ret = 1;
        } else {
            ret += rec(k_new,l_new-1,mem);
        }

        // backtrack respectively build up
        k_new += 3;
        --l_new;
        while(l_new -1 >= 1 ) {
            ret += rec(k_new,l_new-1,mem);
            k_new += 3;
            --l_new;
        }

        // cout << "out k " << k << " l " << l << " ret " << ret << endl;
        return mem[k][l] = ret;
    }

public:
    int houseOfCards(int n) {
        // it takes 3*k-1 cards to build a row with k triangles
        // 1 <= n <= 500
        // so the max k of bottowm row is 167
        // 500 = 3*k-1 -> 501 = 3*k -> 501/3 = k -> 501/3 = 167

        int mem[n+1][168];memset(mem,-1,sizeof mem);
        return rec(n,167,mem);
    }
};
