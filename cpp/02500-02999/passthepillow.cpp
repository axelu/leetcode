
// 2582. Pass the Pillow
// https://leetcode.com/problems/pass-the-pillow/



class Solution {
public:
    int passThePillow(int n, int time) {

        int t = time / (n-1);
        int rem = time % (n-1);

        if( t % 2 == 0 ) {
            return 1 + rem;
        } else {
            return n - rem;
        }

    }
};
