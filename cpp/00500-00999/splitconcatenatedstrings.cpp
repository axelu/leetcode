
// 555. Split Concatenated Strings
// https://leetcode.com/problems/split-concatenated-strings/




class Solution {
public:
    string splitLoopedString(vector<string>& strs) {
        if( strs.size() == 1 && strs[0].size() == 1 )
            return strs[0];

        // find the lexicographically largest string (either forward or backward)
        // start the loop there
        // for every string after, determine if forward or back is larger and use that

        for(auto it = strs.begin(); it != strs.end(); ++it) {
            // is reversed string lexicographically larger?
            auto fi = it->begin();
            auto ri = it->rbegin();
            while( fi <= ri.base() ) {
                if( *fi == *ri ) {
                    ++fi;
                    ++ri;
                } else if( *fi > *ri ) {
                    break;
                } else { // *fi < *ri
                    reverse(it->begin(),it->end());
                    break;
                }
            }
        }

        string s = "";
        for(string& str: strs)
            s += str;

        // all words are in the best possible direction
        // they are still in the original order

        int n = s.size();
        string ans = s;

        for(auto it = strs.begin(); it != strs.end(); ++it) {
            int str_sz = it->size();

            // remove the current word from the front of s
            s.erase(0,str_sz);
            // reverse it
            reverse(it->begin(),it->end());
            // add to front
            s = *it + s;
            // rotate
            for(int i = 0; i < str_sz; ++i) {
                rotate(s.begin(),next(s.begin()),s.end());
                if( s > ans )
                    ans = s;
            }
            // remove from end
            s.erase(n-str_sz);
            // reverse it
            reverse(it->begin(),it->end());
            // add to front
            s = *it + s;
            // rotate
            for(int i = 0; i < str_sz; ++i) {
                rotate(s.begin(),next(s.begin()),s.end());
                if( s > ans )
                    ans = s;
            }
       }

        return ans;
    }
};
