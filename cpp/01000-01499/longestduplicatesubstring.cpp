
// 1044. Longest Duplicate Substring
// https://leetcode.com/problems/longest-duplicate-substring/





// Rabin-Karp Algorithm
// rolling hash

class Solution {
private:
    int p;                              // base
    vector<unsigned long long> p_pow;   // power


    int find(string& text, int l){

        unsigned long long cur_h = 0;
        int i = 0;
        for(; i < l; ++i)
            cur_h = (cur_h * p) + (text[i]-'a'+1);


        unsigned long long power = p_pow[l-1];

        unordered_set<unsigned long long> us;
        us.insert(cur_h);

        for(int s = 0; i < text.size(); ++i) {
            // rolling hash
            cur_h = ( cur_h - (power*(text[s]-'a'+1)) ) * p + (text[i]-'a'+1);
            ++s;

            if( us.find(cur_h) != us.end() )
                return s;

            us.insert(cur_h);
        }
        return -1;
    }



    // binary search
    string search(string& text, int s, int e) {
        if( s > e )
            return "";

        int mid = s + ((e-s)/2);
        int idx = find(text,mid+1);
        if( idx != -1 ) {
            // can we do better?
            string t = search(text,mid+1,e);
            return !t.empty() ? t : text.substr(idx,mid+1);
        } else {
            return search(text,s,mid-1);
        }
    }


public:
    string longestDupSubstring(string s) {
        int n = s.size();


        p = 31;
        p_pow.resize(n);
        p_pow[0] = 1;
        for(int i = 1; i < n; ++i)
            p_pow[i] = p_pow[i-1] * p;

        return search(s,0,n-1);
    }
};
