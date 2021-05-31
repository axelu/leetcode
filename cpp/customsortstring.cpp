
// 791. Custom Sort String
// https://leetcode.com/problems/custom-sort-string/



class Solution {
public:
    string customSortString(string S, string T) {
        int i;
        unordered_map<char,int> s;
        for(i = 0; i < S.size(); ++i)
            s.insert({S[i],i});

        sort(T.begin(),T.end(),[s](const char& a, const char& b){
            auto fa = s.find(a);
            auto fb = s.find(b);
            auto e  = s.end();
            if( fa != e && fb != e ) {
                if( fa->second < fb->second ) return true;
                else return false;
            } else if( fa == e && fb != e ) {
                return false;
            } else if( fa != e && fb == e ) {
                return true;
            } else {
                // fa == e && fb == e
                return false;
            }
        });

        return T;
    }
};
