
// 3703. Remove K-Balanced Substrings
// https://leetcode.com/problems/remove-k-balanced-substrings/



class Solution {
public:
    string removeSubstring(string s, int k) {
        int n = s.size();

        stack<pair<int,int>> o; // open parenthesis: pos, consecutive count
        stack<pair<int,int>> c; // close parenthesis: pos, consecutive count

        for(int i = 0; i < n; ++i) {

            if( s[i] == ')' ) {
                if( o.empty() && c.empty() ) {
                    c.push({i,1});

                } else if( o.empty() && !c.empty() ) {
                    c.push({i, c.top().second + 1});

                } else if( !o.empty() && c.empty() ) {
                    if( k == 1 ) {
                        o.pop();
                    } else {
                        c.push({i, 1});
                    }

                } else { // !o.empty() && !c.empty()
                    if( o.top().first > c.top().first ) {
                        if( k == 1 ) {
                            o.pop();
                        } else {
                            c.push({i, 1});
                        }

                    } else { // o.top().first < c.top().first
                        if( c.top().second + 1 == k && o.top().second >= k ) {
                            for(int j = 0; j < k-1; ++j)
                                c.pop();
                            for(int j = 0; j < k; ++j)
                                o.pop();

                        } else {
                            c.push({i, c.top().second + 1});
                        }
                    }
                }

            } else { // s[i] == '('
                if( o.empty() && c.empty() ) {
                    o.push({i,1});

                } else if( o.empty() && !c.empty() ) {
                    o.push({i,1});

                } else if( !o.empty() && c.empty() ) {
                    o.push({i, o.top().second + 1});

                } else { // !o.empty() && !c.empty()
                    if( o.top().first > c.top().first ) {
                        o.push({i, o.top().second + 1});

                    } else { // o.top().first < c.top().first
                        o.push({i,1});
                    }
                }
            }
        }

        string ans = "";
        while( !o.empty() || !c.empty() ) {
            if( !o.empty() && !c.empty() ) {
                if( o.top().first > c.top().first ) {
                    ans.push_back('(');
                    o.pop();
                } else {
                    ans.push_back(')');
                    c.pop();
                }
            } else if( !o.empty() ) {
                ans.push_back('(');
                o.pop();
            } else { // !c.empty()
                ans.push_back(')');
                c.pop();
            }
        }
        reverse(ans.begin(), ans.end());

        return ans;
    }
};
