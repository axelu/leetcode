
// 746. Shortest Completing Word
// https://leetcode.com/problems/shortest-completing-word/


class Solution {
private:
    bool isSubset(string& a, int& na, string& b, int& nb) {
        // are the letters in b a subset of the letters in a?
        // assumes a and b are sorted !!!
        // assumes a.size() >= b.size()
        if( na == nb ) return a == b;

        char cb;
        int j = 0;                    // idx in a
        for(int i = 0; i < nb; ++i) { // idx in b
            cb = b[i];
            // advance index in a to the same letter as we have in b
            while( a[j] != cb && j < na )
                ++j;
            if( j == na ) return false;
            ++j;
        }
        return true;
    }

public:
    string shortestCompletingWord(string licensePlate, vector<string>& words) {
        int nb = licensePlate.size();
        string b = "";
        for(int i = 0; i < nb; ++i)
            if( isalpha(licensePlate[i]) ) b += tolower(licensePlate[i]);
        nb = b.size();
        sort(b.begin(),b.end());
        // cout << b << endl;

        string ans = "aaaaaaaaaaaaaaaaa",a;
        int na;
        for(int i = 0; i < words.size(); ++i) {
            na = words[i].size();
            if( na < nb ) continue;
            a = words[i];
            sort(a.begin(),a.end());
            if( isSubset(a,na,b,nb) ) {
                if( na < ans.size() )
                    ans = words[i];
                if( nb == na )
                    break;
            }
        }
        return ans;
    }
};
