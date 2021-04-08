
// 605. Can Place Flowers
// https://leetcode.com/problems/can-place-flowers/
// day 5 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/569/week-1-december-1st-december-7th/3555/


class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        if( n == 0 ) return true;

        int c = 1, k = 0;
        for(int i : flowerbed) {
            if( i == 0 ) {
                if( c == 2 ) {
                    ++k;
                    if( k == n )
                        return true;
                    c = 0;
                }
                ++c;
            } else {
                c = 0;
            }
        }
        if( c == 2 ) ++k;
        return k == n;
    }
};
