
// 3088. Make String Anti-palindrome
// https://leetcode.com/problems/make-string-anti-palindrome/





class Solution {
public:
    string makeAntiPalindrome(string s) {
        int n = s.size(); // s.length % 2 == 0

        // let cnt[i] be the count of a given char in s
        // if there is a char[i] > n/2, then we do not have a solution

        map<int,int> cnt;
        for(char c: s)
            ++cnt[c-'a'];
        for(auto p: cnt)
            if( p.second > n/2 )
                return "-1";

        sort(s.begin(),s.end());
        /*
        cout << s << endl;
        for(int i = 0; i < n/2; ++i)
            cout << s[i];
        cout << endl;
        */

        // go from middle to left and see if we pivoted a letter around the midpoint
        // if so, 'rotate second half around first letter different than current letter'

        int j = n / 2;
        int i = j - 1;
        if( s[i] == s[j] ) {

            int k = n/2;
            auto it = cnt.begin();
            for(; it != cnt.end() && k > 0; ) {
                int freq = it->second;
                if( k >= freq ) {
                    k -= freq;
                    it = cnt.erase(it);
                } else {
                    it->second -= k;
                    break;
                }
            }
            // for(auto p: cnt)
            //      cout << (char)('a' + p.first) << ":" << p.second << " ";
            // cout << endl;

            char c = s[i];
            int k1 = 0;
            while( s[i] == c ) {
                --i;
                ++k1;
            }
            // we need to shift k1 chars in the second half
            // cout << "k1 " << k1 << endl;

            it = cnt.find(c-'a');
            advance(it,1);
            for(; k1 > 0; ++j, --k1) {
                s[j] = it->first + 'a';
                --it->second;
                if( it->second == 0 )
                    it = cnt.erase(it);
            }

            // reset
            it = cnt.begin();
            for(; j < n; ++j) {
                s[j] = it->first + 'a';
                --it->second;
                if( it->second == 0 )
                    it = cnt.erase(it);
            }
        }

        /*
        cout << s << endl;
        for(int i = 0; i < n/2; ++i)
            cout << s[i];
        cout << endl;
        */

        return s;
    }
};
