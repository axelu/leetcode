
// 906. Super Palindromes
// https://leetcode.com/problems/super-palindromes/
// day 8 May 2021 challenge
// https://leetcode.com/explore/featured/card/may-leetcoding-challenge-2021/599/week-2-may-8th-may-14th/3736/




class Solution {
private:
    // https://leetcode.com/problems/palindrome-number/
    bool isPalindrome(long long x) {

        if ( x < 0 ) return false;
        if ( x < 10 ) return true;

        long long o = x;
        long long int r = 0;
        while ( x > 0 ) {

            r = (r * 10) + (x % 10);
            x /= 10;

        }
        return ( r == o ) ? true : false;
    }
public:
    int superpalindromesInRange(string left, string right) {
        // 1 <= left.length, right.length <= 18
        // left and right represent integers in the range [1, 10^18]
        // worst case:
        // ULONG_MAX 18446744073709551615 (20)
        //             999999999999999999 max string with lenght 18
        //            1000000000000000000 hm... the constraints given do not line up!!!
        // sqrt(1000000000000000000) = 1000000000
        // worst case input: left = "1", right = "999999999999999999"; answer 70
        // 1, 4, 9, 121, 484, 10201, 12321, 14641, 40804, 44944, 1002001, 1234321, 4008004, 100020001, 102030201, 104060401, 121242121, 123454321, 125686521, 400080004 ,404090404, 10000200001l, 10221412201l, 12102420121l, 12345654321l, 40000800004l , 1000002000001l, 1002003002001l, 1004006004001l, 1020304030201l, 1022325232201l, 1024348434201l, 1210024200121l, 1212225222121l, 1214428244121l, 1232346432321l, 1234567654321l, 4000008000004l, 4004009004004l, 100000020000001l, 100220141022001l, 102012040210201l, 102234363432201l, 121000242000121l, 121242363242121l, 123212464212321l, 123456787654321l, 400000080000004l, 10000000200000001l, 10002000300020001l, 10004000600040001l, 10020210401202001l, 10022212521222001l, 10024214841242001l, 10201020402010201l, 10203040504030201l, 10205060806050201l, 10221432623412201l, 10223454745432201l, 12100002420000121l, 12102202520220121l, 12104402820440121l, 12122232623222121l, 12124434743442121l, 12321024642012321l, 12323244744232321l, 12343456865434321l, 12345678987654321l, 40000000800000004l, 40004000900040004l

        long long l = stoll(left);
        long long r = stoll(right);

        int ans = 0;

        string s;
        long long n;
        for(int k = 1; k < 1e5; ++k) {
            s = to_string(k);
            for(int i = s.size()-1; i >= 0; --i)
                s = s + s[i];
            n = stoll(s);
            n *= n;
            if( n > r ) break;
            if( n >= l && isPalindrome(n) ) ++ans;
        }
        for(int k = 1; k < 1e5; ++k) {
            s = to_string(k);
            for(int i = s.size()-2; i >= 0; --i)
                s = s + s[i];
            n = stoll(s);
            n *= n;
            if( n > r ) break;
            if( n >= l && isPalindrome(n) ) ++ans;
        }

        return ans;
    }
};
