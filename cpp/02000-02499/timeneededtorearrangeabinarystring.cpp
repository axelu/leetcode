
// 2380. Time Needed to Rearrange a Binary String
// https://leetcode.com/problems/time-needed-to-rearrange-a-binary-string/




class Solution {
public:
    int secondsToRemoveOccurrences(string s) {
        // rephrasing the problem statement:
        //    move each 1 to its leftmost position
        // observation:
        //    let x (0-indexed) be the position of a 1,
        //        then if there are a total of k 1s to its left,
        //        its final position will be k (0-indexed)
        //        it will at least take x-k seconds
        //        to reach its final position
        //        however, we cannot reach our final position
        //        faster nor equally fast as the 1 to our
        //        left reaches its final position, it will take
        //        at minimum 1s longer.

        int t = 0;
        int ones = 0;
        for(int i = 0; i < s.size(); ++i) { // going left to right
            if( s[i] == '1' ) {
                if( i > ones ) {
                    int mn_time = i - ones;
                    if( mn_time > t ) {
                        t = mn_time;
                    } else {
                        t = t + 1;
                    }
                }
                ++ones;
            }
        }

        return t;
    }
};
