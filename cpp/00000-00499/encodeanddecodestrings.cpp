
// 271. Encode and Decode Strings
// https://leetcode.com/problems/encode-and-decode-strings/


class Codec {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        int n = strs.size();
        // we will encode as follows:
        // n:strs[0].size():strs[1].size():...:strs[n-1].size():strs[0]strs[1]...strs[n-1]
        string a = to_string(n) + ":";
        string b = "";
        for(int i = 0; i < n; ++i) {
            a += to_string(strs[i].size()) + ":";
            b += strs[i];
        }
        return a+b;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        // get n
        int t = s.find(':');
        int n = stoi(s.substr(0,t));
        // get size of each string
        string sz = "";
        int cnt = 0;
        vector<int> szs(n);
        for(t = t+1; cnt < n; ++t) {
            if( s[t] != ':' ) {
                sz += s[t];
            } else {
                szs[cnt] = stoi(sz);
                sz = "";
                ++cnt;
            }
        }

        vector<string> ans(n);
        for(int i = 0; i < n; ++i) {
            string tmp = "";
            for(int j = 0; j < szs[i]; ++j) {
                tmp += s[t];
                ++t;
            }
            ans[i] = tmp;
        }

        return ans;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));
