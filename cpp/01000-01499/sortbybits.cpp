
// 1356. Sort Integers by The Number of 1 Bits
// https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/



class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {

        sort(begin(arr),end(arr),[](const int &a, const int &b){
            // count set bits in a
            int A = a;
            int ca = 0;
            while (A) {
                ca += A & 1;
                A >>= 1;
            }
            // count set bits in b
            int B = b;
            int cb = 0;
            while (B) {
                cb += B & 1;
                B >>= 1;
            }

            if(ca < cb) {
                return true;
            } else if(ca == cb) {
                if( a < b ) return true;
            }

            return false;
        });

        return arr;
    }
};
