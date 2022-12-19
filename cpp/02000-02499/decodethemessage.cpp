
// 2325. Decode the Message
// https://leetcode.com/problems/decode-the-message/



// 01234567890123456789012345
// abcdefghijklmnopqrstuvwxyz

class Solution {
public:
    string decodeMessage(string key, string message) {
        int key_sz = key.size();
        int t[26];memset(t,-1,sizeof t); // substitution table
        int idx = 0;
        for(int i = 0; i < key_sz; ++i)
            if( key[i] != ' ' ) {
                int c = key[i] - 'a';
                if( t[c] == -1 )
                    t[c] = idx++;
            }

        /*
        for(int i = 0; i < 26; ++i) {
            char a = i+'a';
            char b = t[i]+'a';
            cout << "t[" << i << "] = " << t[i] << " " << a << " => " << b << endl;
        }
        */

        int msg_sz = message.size();
        string ans(msg_sz,' ');
        for(int i = 0; i < msg_sz; ++i)
            if( message[i] != ' ' )
                ans[i] = t[message[i]-'a']+'a';

        return ans;
    }
};
