
// 3406. Find the Lexicographically Largest String From the Box II
// https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-ii/






// see 3403. Find the Lexicographically Largest String From the Box I
// https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-i/

// initialize once
long long p_pow[2000001];
bool init = false;

class Solution {
private:
    const int p = 31;
    const int m = 1e9 + 9;

    long long h_s[200001];

    bool cmp(string& s, int a_s, int a_e, int b_s, int b_e) {
        // returns true if string a is lexicographically smaller than string b
        // it is guaranteed that a and b are non-empty

        int a_sz = a_e - a_s + 1;
        int b_sz = b_e - b_s + 1;

        int e = min(a_sz, b_sz);
        int t = search(a_s, b_s, 1, e);
        // up to a length of t, string a and b are identical

        if( a_sz > t && b_sz > t )
            return s[a_s + t] < s[b_s + t];

        return a_sz < b_sz;
    }

    // binary search
    int search(int a_s, int b_s, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        // hash of substring starting at a_s of length mid
        long long a_h = (h_s[a_s+mid] + m - h_s[a_s]) % m;
        // hash of substring starting at b_s of length mid
        long long b_h = (h_s[b_s+mid] + m - h_s[b_s]) % m;
        if( b_h == a_h * p_pow[b_s - a_s] % m ) {
            // can we do better?
            int t = search(a_s, b_s, mid+1, e);
            return t != -1 ? t : mid;
        }

        return search(a_s, b_s, s, mid-1);
    }

public:
    string answerString(string word, int numFriends) {
        if( !init ) {
            init = true;
            p_pow[0] = 1;
            for (int i = 1; i < 2000001; i++)
                p_pow[i] = (p_pow[i-1] * p) % m;
        }


        if( numFriends == 1 )
            return word;

        int n = word.size();

        if( numFriends == n ) {
            char mx_chr = word[0];
            for(char chr : word )
                mx_chr = max(mx_chr, chr);
            return string(1,(char)mx_chr);
        }

        // find all occurences of the largest letter in word
        // if only 1, than the longest length possible substring
        // starting at that char is our ans
        // longest length possible substring
        // n - (numFriends-1) but watch out for it going beyond the end
        // based on the pos of char

        // to compare the strings, idea:
        // create a rolling hash, then we can use binary search to find
        // the 1st index where the differ to speed the compare up

        int mxl = n - (numFriends-1);

        vector<int> positions[26];
        h_s[0] = 0LL;
        for(int i = 0; i < n; ++i) {
            positions[word[i]-'a'].push_back(i);
            h_s[i+1] = (h_s[i] + (word[i] + 1) * p_pow[i]) % m;
        }

        int a_s, a_e, a_sz;
        for(int i = 25; i >= 0; --i) {
            if( !positions[i].empty() ) {
                a_s = positions[i][0];
                a_e = min(a_s + mxl - 1, n-1);

                for(int j = 1; j < positions[i].size(); ++j) {
                    int b_s = positions[i][j];
                    int b_e = min(b_s + mxl - 1, n-1);
                    if( cmp(word, a_s, a_e, b_s, b_e) ) {
                        a_s = b_s;
                        a_e = b_e;
                    }
                }
                break;
            }
        }

        return word.substr(a_s, a_e - a_s + 1);
    }
};
