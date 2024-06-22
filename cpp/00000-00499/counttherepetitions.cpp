
// 466. Count The Repetitions
// https://leetcode.com/problems/count-the-repetitions/

class Solution {
private:
    bool quick_check(string s1, int n1, string s2, int n2) {
        // char test
        int cnt1[26];memset(cnt1,0,sizeof cnt1);
        for(char c: s1)
            ++cnt1[c-'a'];
        int cnt2[26];memset(cnt2,0,sizeof cnt2);
        for(char c: s2)
            ++cnt2[c-'a'];
        for(int i = 0; i < 26; ++i)
            if( cnt2[i] != 0 && cnt1[i] == 0 )
                return false;
        
        // length test
        int str1_sz = s1.size() * n1;
        int str2_sz = s2.size() * n2;
        if( str2_sz > str1_sz )
            return false;
        if( str2_sz == str1_sz ) {
            // examples
            // s1 = "aaaaa", n1 = 3, s2 = "aaa", n2 = 5
            // str1  a a a a a|a a a a a|a a a a a
            // str2  a a a|a a a|a a a|a a a|a a a
            // s1 = "aaa", n1 = 5, s2 = "aaaaa", n2 = 3
            // str1  a a a|a a a|a a a|a a a|a a a
            // str2  a a a a a|a a a a a|a a a a a    
            // s1 = "cdeabc", n1 = 2, s2 = "abccde", n2 = 2
            // str1  c d e a b c|c d e a b c
            //             -----------
            // str2  a b c c d e|a b c c d e
            //       -----------
            int s1_sz = s1.size();
            int s2_sz = s2.size();
            int l_max = max(s1_sz, s2_sz);
            for(int l = 0; l < l_max; ++l) {
                int i = l % s1_sz;  // index in s1
                int j = l % s2_sz;  // index in s2
                if( s1[i] != s2[j] )
                    return false;
            }
        }
                    
        return true;
    }
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
     
        // quick checks
        // if there is a char in s2 that does not exist in s1, then there is no solution
        // if str2 = [s2, n2] length > str1 = [s1, n1] length, then there is no solution
        // if str2 = [s2, n2] length > str1 = [s1, n1] length, then there has to be a match till the longer s1 or s2 on every position
        if( !quick_check(s1, n1, s2, n2) )
            return 0;
        
        int s1_sz = s1.size();
        int str1_sz = s1_sz * n1;
        int s2_sz = s2.size();
        int str2_sz = s2_sz * n2;
        if( str2_sz == str1_sz )
            return 1;
        
        // brute force
        // we know str1_sz > str2_sz
        int m = 0;                          // index in str1
        int k = 0;                          // index in str2
        for(; m < str1_sz; ++m) {  
            int i = m % s1_sz;              // index in s1
            int j = k % s2_sz;              // index in s2
            if( m != 0 && i == 0 && j == 0 )// we are starting over
                break;
            
            // advance in str1 till matching char
            while( s1[i] != s2[j] ) {
                ++m;
                if( m == str1_sz )
                    break;
                i = m % s1_sz;
            }
            if( m < str1_sz )
                ++k;
        }
        
        // TODO do we need to handle the m == str1 _sz but we never hit 'starting over'?
        
        // cout << "str1 idx m " << m << " str2 idx k " << k << endl;
        // it took (m / s1_sz) s1's to make (k / s2_sz) s2's
        // but str1 is composed out of n1 s1's and 
        //     str2 is composed out of n2 s2's
        
        int x = m / s1_sz; // it took x * s1 to make y * s2
        int y = k / s2_sz;
        // cout << "it took " << x << " s1 to make " << y << " s2's" << endl;
        
        long long t1 = (long long)n1 * y / x; // cout << "str1 will make " << t1 << " s2's" << endl;
        
        return t1 / n2;
    }
};



// brute force solution
// 49 / 49 test cases passed, but took too long as of 4/26/2024


class Solution {
private:
    bool quick_check(string s1, int n1, string s2, int n2) {
        // char test
        int cnt1[26];memset(cnt1,0,sizeof cnt1);
        for(char c: s1)
            ++cnt1[c-'a'];
        int cnt2[26];memset(cnt2,0,sizeof cnt2);
        for(char c: s2)
            ++cnt2[c-'a'];
        for(int i = 0; i < 26; ++i)
            if( cnt2[i] != 0 && cnt1[i] == 0 )
                return false;
        
        // length test
        int str1_sz = s1.size() * n1;
        int str2_sz = s2.size() * n2;
        if( str2_sz > str1_sz )
            return false;
        if( str2_sz == str1_sz ) {
            // examples
            // s1 = "aaaaa", n1 = 3, s2 = "aaa", n2 = 5
            // str1  a a a a a|a a a a a|a a a a a
            // str2  a a a|a a a|a a a|a a a|a a a
            // s1 = "aaa", n1 = 5, s2 = "aaaaa", n2 = 3
            // str1  a a a|a a a|a a a|a a a|a a a
            // str2  a a a a a|a a a a a|a a a a a    
            // s1 = "cdeabc", n1 = 2, s2 = "abccde", n2 = 2
            // str1  c d e a b c|c d e a b c
            //             -----------
            // str2  a b c c d e|a b c c d e
            //       -----------
            int s1_sz = s1.size();
            int s2_sz = s2.size();
            int l_max = max(s1_sz, s2_sz);
            for(int l = 0; l < l_max; ++l) {
                int i = l % s1_sz;  // index in s1
                int j = l % s2_sz;  // index in s2
                if( s1[i] != s2[j] )
                    return false;
            }
        }
                    
        return true;
    }
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
     
        // quick checks
        // if there is a char in s2 that does not exist in s1, then there is no solution
        // if str2 = [s2, n2] length > str1 = [s1, n1] length, then there is no solution
        // if str2 = [s2, n2] length > str1 = [s1, n1] length, then there has to be a match till the longer s1 or s2 on every position
        if( !quick_check(s1, n1, s2, n2) )
            return 0;
        
        int s1_sz = s1.size();
        int str1_sz = s1_sz * n1;
        int s2_sz = s2.size();
        int str2_sz = s2_sz * n2;
        if( str2_sz == str1_sz )
            return 1;
        
        // brute force
        // we know str1_sz > str2_sz
        int k = 0;                          // index in str2
        for(int m = 0; m < str1_sz; ++m) {  // index in str1
            int i = m % s1_sz;              // index in s1
            int j = k % s2_sz;              // index in s2
            
            // advance in str1 till matching char
            while( s1[i] != s2[j] ) {
                ++m;
                if( m == str1_sz )
                    break;
                i = m % s1_sz;
            }
            if( m < str1_sz )
                ++k;
        }
        
        return k / str2_sz;
    }
};

/*
"acb"
4
"ab"
2
"acb"
1
"acb"
1
"cdeabc"
2
"abccde"
1
"cdeabc"
1
"abccde"
1
"cdeabc"
2
"abccde"
2
"aaaaa"
3
"aaa"
5
"aaa"
5
"aaaaa"
3
"aaabaaa"
1
"aaaaaa"
1
"niconiconi"
99981
"nico"
81
*/
