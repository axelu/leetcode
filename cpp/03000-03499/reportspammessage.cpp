
// 3295. Report Spam Message
// https://leetcode.com/problems/report-spam-message/




// initialize once
unsigned long long p_pow[16];
bool initialized = false;


class Solution {
private:
    const int p = 31;
    // const int m = 1e9 + 9;

    set<unsigned long long> banned_words_hashes;

public:
    bool reportSpam(vector<string>& message, vector<string>& bannedWords) {
        if( !initialized ) {
            initialized = true;
            p_pow[0] = 1ULL;
            for(int i = 1; i < 16; ++i)
                p_pow[i] = p_pow[i-1] * p;
        }

        // Rabin-Karp hash for every word in bannedWords
        for(int i = 0; i < bannedWords.size(); ++i) {
            int word_sz = bannedWords[i].size();
            unsigned long long h_s = bannedWords[i][0]-'a'+1;
            for(int j = 1; j < word_sz; ++j)
                h_s = (h_s * p) + (bannedWords[i][j]-'a'+1);
            banned_words_hashes.insert(h_s);
        }

        int cnt = 0;

        for(int i = 0; i < message.size(); ++i) {
            // hash current word in message
            int word_sz = message[i].size();
            unsigned long long h_s = message[i][0]-'a'+1;
            for(int j = 1; j < word_sz; ++j)
                h_s = (h_s * p) + (message[i][j]-'a'+1);

            if( banned_words_hashes.find(h_s) != banned_words_hashes.end() )
                ++cnt;

            if( cnt == 2 )
                return true;
        }

        return false;
    }
};
