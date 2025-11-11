
// 3722. Lexicographically Smallest String After Reverse
// https://leetcode.com/problems/lexicographically-smallest-string-after-reverse/description/



class Solution {
public:
    string lexSmallest(string s) {
        int n = s.size(); // 1 <= n <= 1000; lowercase chars
        if( n == 1 )
            return s;
        if( n == 2 ) {
            if( s[0] > s[1] )
                swap(s[0],s[1]);
            return s;
        }

        // brute force
        string best = s;

        // reverse some left part up to entire string
        for(int l = 2; l <= n; ++l) {
            string a = s.substr(0,l);
            reverse(a.begin(), a.end());
            string b = s.substr(l);
            best = min(best, a+b); // cout << "l " << l << " best " << best << endl;
        }
        // reverse some right part
        // no point trying if best[0] < s[0]
        for(int i = 0; i < n-1; ++i) {
            if( best[i] < s[i] )
                break;

            string a = s.substr(0, i+1);
            string b = s.substr(i+1);
            reverse(b.begin(), b.end());
            best = min(best, a+b);
        }

        return best;
    }
};
