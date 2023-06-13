
// 1881. Maximum Value after Insertion
// https://leetcode.com/problems/maximum-value-after-insertion/




class Solution {
public:
    string maxValue(string& n, int x) {

        if( n[0] != '-' ) {
            // n represents a positive integer
            // going from left to right
            // insert digit x before the 1st digit in n that is smaller
            auto it = n.begin();
            bool inserted = false;
            for(; it != n.end(); ++it) {
                if( *it - '0' < x ) {
                    n.insert(it, x + '0');
                    inserted = true;
                    break;
                }
            }
            if( !inserted )
                n = n + char('0' + x);

        } else {
            // n represents a negative integer
            // going from left to right
            // insert digit x before the 1st digit in n that is greater
            auto it = next(n.begin());
            bool inserted = false;
            for(; it != n.end(); ++it) {
                if( *it - '0' > x ) {
                    n.insert(it, x + '0');
                    inserted = true;
                    break;
                }
            }
            if( !inserted )
                n = n + char('0' + x);
        }

        return n;
    }
};
