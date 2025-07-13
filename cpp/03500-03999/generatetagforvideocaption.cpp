
// 3582. Generate Tag for Video Caption
// https://leetcode.com/problems/generate-tag-for-video-caption/





class Solution {
public:
    string generateTag(string caption) {
        int n = caption.size();

        // it is guaranteed caption consists only of English letters and ' '

        string ans = "#";

        bool very_first_char = true;
        bool prev_space = false;

        for(int i = 0; i < n && ans.size() < 100; ++i) {
            char c = caption[i];
            if( c == ' ' ) {
                prev_space = true;
                continue;
            }

            if( very_first_char ) {
                ans.push_back(tolower(c));
                very_first_char = false;
            } else {
                if( prev_space ) {
                    ans.push_back(toupper(c));
                } else {
                    ans.push_back(tolower(c));
                }
            }
            prev_space = false;
        }

        return ans;
    }
};
