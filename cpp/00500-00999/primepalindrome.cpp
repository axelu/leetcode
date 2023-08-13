
// 866. Prime Palindrome
// https://leetcode.com/problems/prime-palindrome/




class Solution {
private:
    bool isPrime(int n) {
        if( n == 2 || n == 3 )
            return true;

        if( n <= 1 || n % 2 == 0 || n % 3 == 0  )
            return false;

        for(int i = 5; i * i <= n; i += 6 ) {
            if( n % i == 0 || n % (i + 2) == 0 )
                return false;
        }

        return true;
    }

    // inspired by https://www.geeksforgeeks.org/generate-palindromic-numbers-less-n/
    int createPalindrome(int input, bool isOdd) {
        int n = input;
        int palin = input;

        if( isOdd )
            n /= 10;

        while( n > 0 ) {
            palin = palin * 10 + (n % 10);
            n /= 10;
        }
        return palin;
    }

    int generatePalindromes(int k, int n) {
        int number;
        int ret = 200000001;

        for(int j = 0; j < 2; ++j) {
            int i = 1;
            while( (number = createPalindrome(i, j % 2) ) < n) {
                if( number >= k && number < ret && isPrime(number) )
                    ret = number;
                i++;
            }
        }

        return ret;
    }
public:
    int primePalindrome(int n) {
        // from the problem description:
        // The test cases are generated so that the answer always exists and is in the range [2, 2 * 10^8].
        return generatePalindromes(n,200000000);
    }
};
