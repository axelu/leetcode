
// 1297. Maximum Number of Occurrences of a Substring
// https://leetcode.com/problems/maximum-number-of-occurrences-of-a-substring/



class Solution {
public:
    int maxFreq(string& s, int maxLetters, int minSize, int maxSize) {
        int n = s.size();

        int ans = 0;

        for(int size = minSize; size <= maxSize; ++size) {
            // cout << "size " << size << endl;
            // count the occurences of any substring of size 'size'
            // where number of unique characters in the substring <= maxLetters

            int t = 0;
            string ss = "";                 // substring
            unordered_map<char,int> uc;     // unique chars in substring and their number of occurences
            unordered_map<string,int> us;   // unique substrings and their number of occurences
            int i = 0;                      // left idx
            for(int j = 0; j < n; ++j) {    // right idx
                char c = s[j];

                ss = ss + c;
                ++uc[c];
                if( j - i + 1 == size ) {
                    // cout << "  ss " << ss << endl;
                    if( uc.size() <= maxLetters )
                        t = max(t,++us[ss]);

                    auto f = uc.find(s[i]);
                    if( --f->second == 0 )
                        uc.erase(f);
                    ++i;
                    ss.erase(0,1);
                }
            }
            ans = max(ans,t);
        }

        return ans;
    }
};
