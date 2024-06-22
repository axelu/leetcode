
// 3104. Find Longest Self-Contained Substring
// https://leetcode.com/problems/find-longest-self-contained-substring/






class Solution {
private:
    vector<int> t; // segment tree memory efficient indexing

    int combine(int a, int b) {
        return a | b;
    }

    void build(string& a, int v, int tl, int tr) {
        if (tl == tr) {
            int i = a[tl] - 'a';
            t[v] = (1<<i);
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    int get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr)
            return t[v];

        int tm = (tl + tr) / 2;
        int lft = get(v+1, tl, tm, l, min(r, tm));
        int rgt = get(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r);
        return combine(lft, rgt);
    }

    // interval merge
    void join_adjacent_intervals(map<int,int>& intervals, int l, int r) {
        /*
        cout << "join_adjacent_intervals l " << l << " r " << r << endl;
        cout << "  begin ";
        for(auto& p: intervals)
            cout << p.first << ":" << p.second << " ";
        cout << endl;
        */
        if( intervals.empty() ) {
            intervals.insert({l, r});

        } else {

            auto ub = intervals.upper_bound(l);
            // are we eclipsing what we have found?
            while( ub != intervals.end() && ub->second < r )
                ub = intervals.erase(ub);

            if( intervals.empty() ) {
                intervals.insert({l, r});

            } else if( ub != intervals.end() ) {

                // Note: we should not have a case where we interweave, hence ommitting

                bool extend_next = r + 1 == ub->first;
                bool extend_prev = ub != intervals.begin() && l - 1 == prev(ub)->second;
                bool eclipsed_by_prev = ub != intervals.begin() && prev(ub)->first <= l && prev(ub)->second >= r;
                if( !eclipsed_by_prev && extend_next && extend_prev ) {
                    prev(ub)->second = ub->second;
                    intervals.erase(ub);

                } else if( !eclipsed_by_prev && extend_next ) {
                    intervals.insert({l, ub->second});
                    intervals.erase(ub);

                } else if( !eclipsed_by_prev && extend_prev ) {
                    prev(ub)->second = r;

                } else if( !eclipsed_by_prev ) {
                    intervals.insert({l, r});
                }

            } else {
                auto last = intervals.rbegin();
                bool eclipsed_by_prev = last->first <= l && last->second >= r;
                if( !eclipsed_by_prev && l - 1 == last->second ) {
                    last->second = r;
                } else if( !eclipsed_by_prev ) {
                    intervals.insert({l, r});
                }
            }

        }
        /*
        cout << "  end ";
        for(auto& p: intervals)
            cout << p.first << ":" << p.second << " ";
        cout << endl;
        */
        return;
    }

public:
    int maxSubstringLength(string s) {
        int n = s.size();
        // cout << "n " << n << endl;

        t.assign(2*n,0);
        build(s, 1, 0, n-1);

        vector<vector<int>> v(26,{-1,-1}); // char, {first index, last index}
        for(int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            if( v[c][0] == -1 ) // first encounter of this char
                v[c] = {i,i};
            else
                v[c][1] = i;
        }
        /*
        for(int c = 0; c < 26; ++c) {
            cout << (char)(c + 'a') << ":" << v[c][0] << ":" << v[c][1] << " ";
        }
        cout << endl;
        */

        int ans = -1;
        map<int,int> intervals; // s,e
        for(int c = 0; c < 26; ++c) {
            if( v[c][0] == -1 )
                continue;

            int l = v[c][0];
            int r = v[c][1];
            if( l == 0 && r == n-1 ) // quick exit
                continue;

            bool seen[26];memset(seen,false,sizeof seen);
            seen[c] = true;
            for(int i = l+1; i <= r; ++i) {
                // cout << "  i " << i << " " << s[i] << " l " << l << " r " << r << endl;
                // cout << "  char first " << v[s[i]-'a'][0] << " char last " << v[s[i]-'a'][1] << endl;
                if( seen[s[i]-'a'] )
                    continue;
                seen[s[i]-'a'] = true;
                r = max(r, v[s[i]-'a'][1]);
                if( v[s[i]-'a'][0] < l ) {
                    l = v[s[i]-'a'][0];
                    i = l; // +1 by loop
                }
            }
            // cout << char(c+'a') << " l " << l << " r " << r << endl;
            if( l == 0 && r == n-1 )
                continue;


            // 0...l-1 | l...r | r+1...n-1
            // -------   -----   ---------
            //    lft     mid       rgt
            int lft = 0;
            int mid = 0;
            int rgt = 0;
            if( l == 0 ) {              // r < n-1, we have a range to the right
                lft = r + 1;
                rgt = n - (r + 1);


            } else if( r == n-1 ) {     // l > 0, we have a range to the left
                lft = l;
                rgt = n - l;

            } else {                    // l > 0 && r < n-1, we have 0...l-1 | l...r | r+1...n-1
                // cout << "middle " << char(c+'a') << " l " << l << " r " << r << endl;
                mid = r - l + 1;
                // the one thing we know is, that mid is self contained, or said differently
                // we know that if a letter is in mid, it is not in rgt and not in lft
                // so we need to determine if rgt and lft are also self contained
                int chars_lft = get(1,0,n-1,0,l-1);
                int chars_rgt = get(1,0,n-1,r+1,n-1);
                if( (chars_lft & chars_rgt) == 0 ) {
                    lft = l;
                    rgt = n - (r + 1);
                }
                join_adjacent_intervals(intervals, l, r);
            }
            ans = max({ans,lft, mid, rgt});
        }
        // process intervals
        for(auto& p: intervals) {
            ans = max(ans, p.second - p.first + 1);
        }


        return ans;
    }
};
