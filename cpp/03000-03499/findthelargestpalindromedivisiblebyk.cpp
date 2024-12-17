
// 3260. Find the Largest Palindrome Divisible by K
// https://leetcode.com/problems/find-the-largest-palindrome-divisible-by-k/





// https://www.omnicalculator.com/math/divisibility-test
// https://www.omnicalculator.com/math/divisibility-test#divisibility-test-of-7
// https://www.mathwarehouse.com/arithmetic/numbers/divisibility-rules-and-tests.php
// https://www.geeksforgeeks.org/divisibility-rule-of-7/

class Solution {
private:

    // check divisibility by 7 using alternating sum of blocks of three digits from right to left test
    bool is_divisible_by7(int n, char mid) {
        //cout << "is_divisible_by7 mid " << mid << endl;
        // 3 <= n <= 100000
        // TODO we can improve by calculating number of blocks,
        // and only checking what we need

        // brute force
        int sum = 0;
        if( n % 2 == 0 ) {
            //cout << n << " is even" << endl;
            // mid must be 2 digits
            int ml_idx = (n-1) / 2; //cout << "ml_idx " << ml_idx << endl;
            int mr_idx = ml_idx + 1;//cout << "mr_idx " << mr_idx << endl;
            for(int i = n-1, blk = 0; i >= 0; i -= 3, ++blk) {
                // current block (i-2)...i
                // cout << "blk " << blk << " " << max(0, i-2) << ".." << i << endl;
                string t_str;
                if( i-2 < 0 ) {
                    int l = i+1;
                    t_str = l == 1 ? "9" : "99";
                } else {
                    t_str = "999";
                    if( (i-2) <= ml_idx && ml_idx <= i )
                       t_str[ml_idx - (i-2)] = mid;
                    if( (i-2) <= mr_idx && mr_idx <= i )
                       t_str[mr_idx - (i-2)] = mid;
                }
                //cout << t_str << endl;
                int t = stoi(t_str);
                if( blk % 2 == 0 )
                    sum += t;
                else
                    sum -= t;
            }

        } else {
            // mid must be 1 digit
            int m_idx = (n-1) / 2;
            for(int i = n-1, blk = 0; i >= 0; i -= 3, ++blk) {
                // current block (i-2)...i
                // cout << "blk " << blk << " " << max(0, i-2) << ".." << i << endl;
                string t_str;
                if( i-2 < 0 ) {
                    int l = i+1;
                    t_str = l == 1 ? "9" : "99";
                } else {
                    t_str = "999";
                    if( (i-2) <= m_idx && m_idx <= i )
                       t_str[m_idx - (i-2)] = mid;
                }
                int t = stoi(t_str);
                if( blk % 2 == 0 )
                    sum += t;
                else
                    sum -= t;
            }
        }

        return sum % 7 == 0;
    }


public:
    string largestPalindrome(int n, int k) {
        // 1 <= k <= 9

        if( k == 1 || k == 3 || k == 9 ) {
            string s(n, '9');
            return s;
        }

        if( k == 2 ) {
            // A number is divisible by 2 if it is even aka
            // if the last digit is divisible by 2.
            if( n == 1 ) {
                return "8";
            } else if( n == 2 ) {
                return "88";
            } else {
                string mid(n-2, '9');
                return "8" + mid + "8";
            }
        }

        if( k == 4 ) {
            // A number is divisible by 4 if the number's last two digits are divisible by 4.
            if( n <= 4 ) {
                string s(n, '8');
                return s;
            } else {
                string mid(n-4, '9');
                return "88" + mid + "88";
            }
        }

        if( k == 8 ) {
            if( n <= 6 ) {
                string s(n, '8');
                return s;
            } else {
                string mid(n-6, '9');
                return "888" + mid + "888";
            }
        }

        if( k == 5 ) {
            if( n <= 2 ) {
                string s(n, '5');
                return s;
            } else {
                string mid(n-2, '9');
                return "5" + mid + "5";
            }
        }

        if( k == 6 ) {
            // A number is divisible by 6 if it is even and
            // if the sum of its digits is divisible by 3.
            if( n <= 2 ) {
                string s(n, '6');
                return s;

            } else {
                // 1st and last digit will be 8, sum of 16
                int sum = 16;

                if( n % 2 ) {
                    sum += (n-2-1) * 9;
                    int x = 9;
                    while( x >= 1 && ((sum + x) % 3) != 0 )
                        x -= 1;
                    string mid(1,(char)('0' + x));
                    string lr((n-2)/2, '9');
                    return "8" + lr + mid + lr + "8";

                } else {
                    sum += (n-2-2) * 9;
                    int x = 99;
                    while( x >= 11 && ((sum + x) % 3) != 0 )
                        x -= 11;
                    string mid = to_string(x);
                    string lr((n-2-2)/2, '9');
                    return "8" + lr + mid + lr + "8";
                }
            }
        }

        // k == 7
        // 7, 77, 959, 9779, 99799, 999999, 9994999, 99944999, 999969999, ...
        // one rule:
        // Take the last digit (unit digit) of the number and double it.
        // Subtract this doubled value from the rest of the digits in the number.
        // Check the result: If the difference is divisible by 7 (or is 0), then the original number is divisible by 7.
        // another rule:
        // A number is divisible by 7 if and only
        // if the alternating sum of blocks of three digits from right to left is divisible by 7
        if( n <= 2 ) {
            string s(n, '7');
            return s;
        }

        for(int i = 9; i >= 0; --i)
            if( is_divisible_by7(n, (char)('0' + i)) ) {
                if( n % 2 == 0 ) {
                    string lr((n-2)/2, '9');
                    string mid(2, (char)('0' + i));
                    return lr + mid + lr;
                } else {
                    string lr((n-1)/2, '9');
                    string mid(1, (char)('0' + i));
                    return lr + mid + lr;
                }
            }

        return "-1"; // we should never get here
    }
};
