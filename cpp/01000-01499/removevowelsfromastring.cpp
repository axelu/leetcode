
// 1119. Remove Vowels from a String
// https://leetcode.com/problems/remove-vowels-from-a-string/



class Solution {
public:
    string removeVowels(string& s) {
        int n = s.size();
        if( n == 0 ) return s;

        for(int i = 0; i < n; ++i) {
            if( s[i]=='a' || s[i]=='e' || s[i]=='i' || s[i]=='o' || s[i]=='u' ) {
                s.erase(i,1);
                --i;
                --n;
            }
        }
        return s;
    }
};
