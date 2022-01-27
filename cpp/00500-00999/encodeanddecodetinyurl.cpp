
// 535. Encode and Decode TinyURL
// https://leetcode.com/problems/encode-and-decode-tinyurl/


class Solution {
private:
    unordered_map<string,string> umByLong;
    // unordered_map<string,string> umByShort;
    // unordered_set<long> seen;
    unordered_map<long,string> umById;
    long ID;

    char b62[62] = {'0','1','2','3','4','5','6','7','8','9',
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',};

    long getRandom() {
        // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<long> distrib(0,3521614606207); // 3521614606207 -> base62 ZZZZZZZ
        return distrib(gen);
    }

    // base62 encoding
    string base62encode(long num) {
        if( num == 0 ) return "0";
        string ans = "";
        long rem;
        while( num > 0 ) {
            rem = num % 62;
            ans = b62[rem] + ans;
            num /= 62;
        }
        return ans;
    }

    // base62 decoding
    long base62decode(string s) {
        int n = s.size();
        long id = 0;
        long t;
        long f = 1;
        for(int i = n-1; i >= 0; --i) {
            if( '0' <= s[i] && s[i] <= '9')
                t = s[i] - '0';
            if( 'a' <= s[i] && s[i] <= 'z' )
                t = s[i] - 'a' + 10;
            if( 'A' <= s[i] && s[i] <= 'Z' )
                t = s[i] - 'A' + 36;

            if( i == n-1 ) {
                id = t;
            } else {
                f *= 62;
                id += f*t;
            }
        }
        return id;
    }

public:
    Solution() {
        ID = 0L;
    }

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        auto f = umByLong.find(longUrl);
        if( f != umByLong.end() )
            return f->second;

        /*
        long rdm;
        do {
            rdm = getRandom();
        } while( seen.find(rdm) != seen.end() );
        string shortUrl = base62encode(rdm);
        umByLong.insert({longUrl,shortUrl});
        umByShort.insert({shortUrl,longUrl});
        seen.insert(rdm);
        return shortUrl;
        */

        string shortUrl = base62encode(ID);
        umByLong.insert({longUrl,shortUrl});
        umById.insert({ID,longUrl});
        ++ID;
        return shortUrl;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        /*
        auto f = umByShort.find(shortUrl);
        if( f != umByShort.end() )
            return f->second;
        else
            return "";
        */

        long id = base62decode(shortUrl);
        auto f = umById.find(id);
        if( f != umById.end() )
            return f->second;
        else
            return "";
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
