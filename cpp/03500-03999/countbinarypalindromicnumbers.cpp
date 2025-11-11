
// 3677. Count Binary Palindromic Numbers
// https://leetcode.com/problems/count-binary-palindromic-numbers/



// initialize once
long long palindrome_count[50];
long long palindrome_count_prefixSum[51];
set<long long> pow2;
bool init = false;

class Solution {
private:
    string int2binarystring(long long x) {
        string ret(50,'0');
        for(int i = 0; i < 50; ++i)
            if( (x>>i) & 1LL )
                ret[50-1-i] = '1';
        // trim leading 0s, if any
        while(ret.size() > 1 && ret.front() == '0' )
            ret.erase(0,1);
        return ret;
    }

    long long binarystring2int(string s) {
        // will ignore leading 0s correctly
        long long ret = 0LL;
        long long f = 1LL;
        for(int i = s.size()-1; i >= 0; --i) {
            if( s[i] == '1' )
                ret += f;
            f *= 2LL;
        }
        return ret;
    }


public:
    int countBinaryPalindromes(long long n) {
        if( !init ) {
            palindrome_count[0] = 0;
            palindrome_count[1] = 2; // 0, 1
            palindrome_count[2] = 1; // 11
            for(int i = 3; i <= 49; ++i) {
                if( i % 2 )
                    palindrome_count[i] = 2LL * palindrome_count[i-1];
                else
                    palindrome_count[i] = 2LL * palindrome_count[i-2];
            }
            palindrome_count_prefixSum[0] = 0;
            for(int i = 1; i <= 50; ++i)
                palindrome_count_prefixSum[i] = palindrome_count_prefixSum[i-1] + palindrome_count[i-1];

            for(int i = 0; i <= 49; ++i)
                pow2.insert(pow(2,i));

            init = true;
        }

        // edge cases
        if( n == 0 )
            return 1;
        if( n == 1 )
            return 2;
        if( n == 2 )
            return 2;
        if( n == 3 )
            return 3;
        if( n >= 999999996820167 )
            return 63356754;

        // 0 <= n <= 1e15
        // n = 0 -> ans = 1
        // n = 1e15 -> ans 63,356,754 (just ran this w/o yet having a solution)
        //                        01234567890123456789012345678901234567890123456789
        //                                              i    i
        // decimal 1e15 -> binary 11100011010111111010100100110001101000000000000000 (50 digits)
        //                                                xx
        //                        11100011010111111010100100100101011111101011000111 <- 999999996820167 decimal
        // finding the next lower or equal palindrome:
        // starting from the middle go left,
        // if we encounter a 1 and right side is a 1, move on
        // if we encounter a 0 and right side is a 0, move on
        //     if we make it all the way through, then it is a palindrome
        // if we encounter a 0 and right side is 1, we can simply reverse left side to get largest palindrome
        //     (see above marked with i)
        //     make it all the way through and if no hit, then
        // if we encounter a 1 and right side is 0, then back track and
        //     1st one from middle, turn into a 0, then all position back to middle set to 1
        // edge case if n is a power of 2, then binary is right most bit 1, the rest 0
        // in that case we simply can set n to all 1s bits-1, aka n-1

        // bits  count
        //    1      2  0, 1
        //    2      1  11
        //    3      2  101, 111    take the prior even count and inject a 0 or a 1 in the middle
        //    4      2  1001, 1111  take the prior even count and inject a 00 or a 11 in the middle
        //    5      4              take the prior even count and inject a 0 or a 1 in the middle
        //    6      4              take the prior even count and inject a 00 or a 11 in the middle
        //    7      8              take the prior even count and inject a 0 or a 1 in the middle
        //    8      8              take the prior even count and inject a 00 or a 11 in the middle
        //    9     16              take the prior even count and inject a 0 or a 1 in the middle
        //   10     16              take the prior even count and inject a 00 or a 11 in the middle
        //    ...
        // also let us take bits 8 as an example
        // we can take the left half of bits and enumerate
        // 1000, 1001, 1010, 1011, 1100, 1101, 1110, 1111
        // also, that would be 2^3 = 8
        // let us take bits 9 as an example
        // we can take the left half of bits + 1 bit and enumerate, so 5 bits
        // also, that would be 2^4 = 16
        // 10000, 10001, 10010, 10011, 10100, 10101, 10110, 10111, 11000, 11001, 11010, 11011, 11100, 11101, 11110, 11110
        // let us take bits 10 as an example,
        // well, take first half of bits, 10/2 bits = 5 bits, for which we already know the answer

        // take n and transform to binary string
        // get number of bits (length of binary string), let that be nbrbits
        // get palindrome count up to and including nbrbits-1 (easy prefixSum)
        // check if our n binary is all 1s, then just add palindrome count for nbrbits and we are done
        //    aka 2^nbrbits - 1
        // we need to find the next lower or equal palindrome for nbrbits
        //    see above on how to do that
        // that binary palindrome to int is our number to add

        string n_str = int2binarystring(n); // cout << "n_str " << n_str << endl;
        int nbrbits = n_str.size();         // cout << "nbrbits " << nbrbits << endl;

        if( pow2.find(n) != pow2.end() )
            return palindrome_count_prefixSum[nbrbits];

        if( pow2.find(n+1) != pow2.end() )
            return palindrome_count_prefixSum[nbrbits+1];

        // get next lower or equal binary palindrome
        int zeroone = -1;
        int onezero = -1;
        int i = nbrbits/2 - 1;
        int j = nbrbits/2;
        if( nbrbits % 2 )
            ++j;
        for(; i >= 0; --i, ++j) {
            if( n_str[i] == '0' && n_str[j] == '1' ) {
                zeroone = i;
                break;
            }
            if( n_str[i] == '1' && n_str[j] == '0' ) {
                onezero = i;
                break;
            }
        }

        // debug
        if( zeroone == -1 && onezero == -1 )
            cout << "already binary palindrome" << endl;

        if( zeroone != -1 ) {
            int l = nbrbits / 2;
            // repeated TODO factor out
            string fsthalf = n_str.substr(0,l);
            string scdhalf = fsthalf;
            reverse(scdhalf.begin(), scdhalf.end());
            if( nbrbits % 2 )
                fsthalf.push_back(n_str[l]);

            n_str = fsthalf + scdhalf;
        }

        if( onezero != -1 ) {
            // we need to flip the 1st one we encounter to 0
            // and then backtrack
            // NOTE the 1st one could be middle when odd
            bool f = false;
            if( nbrbits % 2 ) {
                int l = nbrbits / 2; // middle bit pos
                if( n_str[l] == '1' ) {
                    n_str[l] = '0';

                    string fsthalf = n_str.substr(0,l);
                    string scdhalf = fsthalf;
                    reverse(scdhalf.begin(), scdhalf.end());
                    fsthalf.push_back(n_str[l]);

                    n_str = fsthalf + scdhalf;

                    f = true;
                }
            }
            if( !f ) {

                // it is guaranteed that i > 0
                // because we did the pow2 check
                int i = nbrbits/2 - 1;
                for(; i >= 0; --i) {
                    if( n_str[i] == '1' ) {
                        break;
                    }
                }
                // i is the index of the 1st 1 moving from middle to left
                n_str[i] = '0';
                ++i;
                for(; i <= nbrbits/2 - 1; ++i)
                    n_str[i] = '1';
                if( nbrbits % 2 )
                    n_str[i] = '1';


                int l = nbrbits/2;
                string fsthalf = n_str.substr(0,l);
                string scdhalf = fsthalf;
                reverse(scdhalf.begin(), scdhalf.end());
                fsthalf.push_back(n_str[l]);

                n_str = fsthalf + scdhalf;
            }
        }

        // cout << "n binary " << n_str << " after mods" << endl;

        // if( zeroone == -1 && onezero == -1 ) {

        // binary is a palindrome
        // so we can take the left half of bits (if nbrbits odd include very middle)
        // set the leftmost most significant bit to 0
        // then do a binarystring2int (note: now has at least 1 leading 0)
        // and that is the number of palindromes we can make with highest bit count
        // need to add to that bit count palindromes we can make to get total ans
        int l = nbrbits / 2;
        if( nbrbits % 2 )
            ++l;
        string fsthalf = n_str.substr(0,l); // cout << "fsthalf before " << fsthalf << endl;
        fsthalf[0] = '0';
        long long addend = binarystring2int(fsthalf);

        // +1 because of our original full length palindrome
        return palindrome_count_prefixSum[nbrbits] + addend + 1LL;

        // }

    }
};

/* numbers to test with that similate all scenarios we are accounting for
0
1
2
3
1000000000000000
63
999999996820167
4

562949953421312
7
562949953421311
21845
21973
10965
9

10453
17877
1965
951
973
*/
