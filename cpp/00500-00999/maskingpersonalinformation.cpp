
// 831. Masking Personal Information
// https://leetcode.com/problems/masking-personal-information/




class Solution {
private:
    bool is_email(string s) {
        return isalpha(s[0]);
    }

    string str_tolower(string s) {
        transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return tolower(c); }
                  );
        return s;
    }

public:
    string maskPII(string s) {
        if( is_email(s) ) {
            int at = s.find('@');

            char lps = (char)tolower(s[0]);
            char lpe = (char)tolower(s[at-1]);

            string ans = "";
            ans += lps;
            ans += "*****";
            ans += lpe;
            ans += str_tolower(s.substr(at));
            return ans;

        } else {
            int n = s.size();

            string ans = "";
            int cnt = 0;
            for(int i = n-1; i >= 0; --i) {

                if( isdigit(s[i]) ) {
                    if( cnt < 4 ) {
                        ans = s[i] + ans;
                    } else if( cnt < 10 ) {
                        ans = '*' + ans;
                    } else if( cnt == 10 ) {
                        ans = '-' + ans;
                        ans = '*' + ans;
                    } else {
                        ans = '*' + ans;
                    }
                    ++cnt;
                    if( cnt == 4 || cnt == 7 ) {
                        ans = '-' + ans;
                    }
                }
            }

            if( ans.size() > 12 )
                ans = '+' + ans;

            return ans;
        }
    }
};
