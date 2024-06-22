
// 3081. Replace Question Marks in String to Minimize Its Value
// https://leetcode.com/problems/replace-question-marks-in-string-to-minimize-its-value/




class Solution {
private:
    pair<int, char> t[4*26]; // segment tree

    pair<int, char> combine(pair<int, char> a, pair<int, char> b) {
        if( a.first < b.first ) {
            return a;
        } else if( a.first == b.first ) {
            if( a.second < b.second ) {
                return a;
            }
        }
        return b;
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = make_pair(a[tl], tl + 'a');
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    void update(int v, int tl, int tr, int pos) {
        if (tl == tr) {
            ++t[v].first;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v*2, tl, tm, pos);
            else
                update(v*2+1, tm+1, tr, pos);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

public:
    string minimizeStringValue(string s) {
        int n = s.size();

        vector<int> freq(26, 0);
        for(char c: s)
            if( c != '?' )
                ++freq[c-'a'];

        build(freq, 1, 0, 25);

        priority_queue<char,vector<char>,greater<char>> pq;
        for(int i = 0; i < n; ++i) {
            if( s[i] != '?' ) {
                /*
                while( !pq.empty() ) {
                    s[i - pq.size()] = pq.top();
                    pq.pop();
                }
                */
                // update(1, 0, 25, s[i] - 'a');
            } else {
                pair<int, char> p = t[1];
                pq.push(p.second);
                update(1, 0, 25, p.second - 'a');
            }
        }
        for(int i = 0; i < n; ++i) {
            if( s[i] == '?' ) {
                s[i] = pq.top();
                pq.pop();
            }
        }


        return s;
    }
};
