
// 2145. Count the Hidden Sequences
// https://leetcode.com/problems/count-the-hidden-sequences/




class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        //                   differences[i] = hidden[i + 1] - hidden[i]
        //   ->  differences[i] + hidden[i] = hidden[i + 1]

        int n = differences.size();

        // construct a hidden sequence with an arbitrary starting point
        // keep track of min and max

        long mn = 10000000000;
        long mx = 10000000000;
        long hiddeni = 10000000000;

        for(int i = 0; i < n; ++i) {
            hiddeni = differences[i] + hiddeni;
            mn = min(mn,hiddeni);
            mx = max(mx,hiddeni);
        }

        long diff = upper - lower;

        if( mx - mn > diff ) {
            return 0;
        } else if( mx - mn == diff ) {
            return 1;
        } else { // mx - mn < diff
            return diff - (mx - mn) + 1;
        }
    }
};
