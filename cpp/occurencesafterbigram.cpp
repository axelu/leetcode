
// 1078. Occurrences After Bigram
// https://leetcode.com/problems/occurrences-after-bigram/



class Solution {
public:
    vector<string> findOcurrences(string text, string first, string second) {
        string needle = first + " " + second + " ";
        size_t l = needle.size();
        size_t h = text.size();
        if( h < l ) return {};

        vector<string> r;
        int idx = 0;
        size_t n,thirdStart,thirdEnd;
        string s;
        while( true ) {
            n = text.find(needle,idx);
            if( n == string::npos ) break;
            if( n != 0 && text[n-1] != ' ' ) {
                idx = n+1;
                continue;
            }
            thirdStart = n + l;
            thirdEnd = text.find(" ",thirdStart);
            if( thirdEnd == string::npos ) {
                s = text.substr(thirdStart,h-thirdStart);
                r.push_back(s);
                break;
            } else {
                s = text.substr(thirdStart, thirdEnd-thirdStart);
                r.push_back(s);
                //idx = thirdEnd;
                idx = n+1;
            }
        }

        return r;
    }
};
