
// 213. House Robber II
// day 14 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/560/week-2-october-8th-october-14th/3494/
// https://leetcode.com/problems/house-robber-ii/


class Solution {
public:
    int rob(vector<int>& nums) {
        auto n = nums.size();
        // base cases
        if( n == 0 ) return 0;
        if( n == 1 ) return nums[0];
        if( n == 2 ) return max(nums[0],nums[1]);
        if( n == 3 ) return max({nums[0],nums[1],nums[2]});

        // n >= 4
        // House[1]-House[n-1]
        int a = rob(nums.begin(), nums.end() - 2);
        // House[2]-House[n]
        int b = rob(nums.begin() + 1, nums.end() - 1);

        return max(a,b);
    }
private:
    int rob(vector<int>::iterator itb, vector<int>::iterator ite) {
        if( ite - itb == 0 )   // size 1
            return *itb;
        if( ite - itb == 1 )   // size 2
            return max(*itb, *ite);
        if( ite - itb == 2 )   // size 3
            return max(*itb + *ite, *(itb+1));
        if( ite - itb == 3 )   // size 4
            return max({*itb + *ite, *(itb+1) + *ite, *itb + *(itb+2)});

        int m = ( ite - itb ) / 2;
        auto itm = itb + m;

        // left
        int a = 0;
        int b = 0;
        if ( itm - itb >= 2 )
            a = rob(itb, itm - 2);
        if ( itm - itb >= 3 )
            b = rob(itb, itm - 3);

        // right
        int c = 0;
        int d = 0;
        if ( ite - itm >= 2 )
            c = rob(itm + 2, ite);
        if ( ite - itm >= 3 )
            d = rob(itm + 3, ite);

        int m1 = *itm + max(a,b) + max(c,d);

        // shift the middle by one
        itm = itm + 1;

        int e = b + *(itm-2);
        int m2 = *itm + max(a,e) + d;

        int m3 = b + *(itm-2) + c;

        return max({m1,m2,m3});
    }
};
