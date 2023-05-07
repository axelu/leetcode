
// 2443. Sum of Number and Its Reverse
// https://leetcode.com/problems/sum-of-number-and-its-reverse/



class Solution {
public:
    bool sumOfNumberAndReverse(int num) {

        // brute force
        for(int i = 0; i <= num; ++i) {
            string b_str = to_string(i);
            reverse(b_str.begin(),b_str.end());
            int b = stoi(b_str);

            if( i + b == num )
                return true;
        }

        return false;
    }
};
