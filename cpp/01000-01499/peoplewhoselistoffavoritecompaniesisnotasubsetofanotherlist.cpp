
// 1452. People Whose List of Favorite Companies Is Not a Subset of Another List
// https://leetcode.com/problems/people-whose-list-of-favorite-companies-is-not-a-subset-of-another-list/



class Solution {
private:
    bool issubset(vector<int>& a, vector<int>& b) {
        // returns true if a is a subset of b
        int a_sz = a.size();
        int b_sz = b.size();

        if( a_sz > b_sz )
            return false;

        // a_sz <= b_sz;
        int a_idx = 0;
        int b_idx = 0;
        while( a_idx < a_sz && b_idx < b_sz ) {
            if( a[a_idx] == b[b_idx] )
                ++a_idx;
            ++b_idx;
        }

        return a_idx == a_sz;
    }

public:
    vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {
        int n = favoriteCompanies.size();

        unordered_map<string,int> um;
        int h = 0;
        vector<vector<int>> vv(n);
        for(int i = 0; i < n; ++i) {
            vector<int> v;
            for(string& s: favoriteCompanies[i]) {
                auto p = um.insert({s,h});
                if( p.second ) {
                    v.push_back(h);
                    ++h;
                } else {
                    v.push_back(p.first->second);
                }
            }
            sort(v.begin(),v.end());
            vv[i] = v;
        }

        /*
        for(auto it = um.begin(); it != um.end(); ++it)
            cout << it->first << " " << it->second << endl;
        for(int i = 0; i < n; ++i) {
            cout << i << ": ";
            for(int x: vv[i])
                cout << x << " ";
            cout << endl;
        }
        */

        vector<int> ans;
        for(int i = 0; i < n; ++i) {
            bool f = false;
            for(int j = 0; j < n && !f; ++j) {
                if( j == i )
                    continue;
                f = issubset(vv[i],vv[j]);
            }
            if( !f )
                ans.push_back(i);
        }

        return ans;
    }
};
