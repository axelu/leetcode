
// 1842. Next Palindrome Using Same Digits
// https://leetcode.com/problems/next-palindrome-using-same-digits/





// see solution for 556. Next Greater Element III
// https://leetcode.com/problems/next-greater-element-iii/

class Solution {
public:
    string nextPalindrome(string num) {
        int n = num.size();
        if( n == 1 )
            return "";

        int i = n/2 - 1;
        // quick check if there even is a digit we could swap
        for(; i > 0 && num[i] <= num[i - 1]; --i);
        if( !i )
            return "";

        int j = i, k = i;
        for(; k < n/2; ++k)
            if( num[k] > num[i - 1] && num[k] <= num[j] )
                j = k;

        swap(num[i - 1], num[j]);
        reverse(num.begin() + i, num.begin() + n/2);

        i = 0, j = n-1;
        while( i < j ) {
            num[j] = num[i];
            ++i;
            --j;
        }

        return num;
    }
};
