
// 1404. Number of Steps to Reduce a Number in Binary Representation to One
// https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/



class Solution {
public:
    int numSteps(string s) {
        int steps = 0;
        while( s.size() > 1 ) {
            ++steps;
            if( s.back() == '0' ) {
                s.pop_back(); // division by 2 -> right shift;
            } else {
                int carry = 1;
                for(int i = s.size()-1; i >= 0; --i) {
                    if( s[i] == '1' ) {
                        s[i] = '0';
                    } else {
                        s[i] = '1';
                        carry = 0;
                        break;
                    }
                }
                if( carry )
                    s = '1' + s;
            }
        }

        return steps;
    }
};
