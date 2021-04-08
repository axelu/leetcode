
// 1772. Sort Features by Popularity
// https://leetcode.com/problems/sort-features-by-popularity/



class Solution {
public:
    vector<string> sortFeatures(vector<string>& features, vector<string>& responses) {
        int n = features.size();
        unordered_map<string,int> um;              // feature,index
        vector<vector<int>> v(n,vector<int>(2,0)); // v[index][0] count, v[index][1] index
        for(int i = 0; i < n; ++i) {
            um.insert({features[i],i}); // features contains no duplicates
            v[i][1] = i;
        }

        unordered_set<string> seen;
        stringstream ss;
        string s;
        for(int i = 0; i < responses.size(); ++i) {
            seen.clear();
            ss = stringstream(responses[i]);
            while( getline(ss,s,' ') ) { // no two consecutive spaces, no leading or trailing spaces
                if( seen.find(s) != seen.end() ) continue;
                seen.insert(s);
                auto f = um.find(s);
                if( f != um.end() )
                    ++v[f->second][0];
            }
        }

        sort(v.begin(),v.end(),[](vector<int>& a, vector<int>& b){
            if( a[0] > b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) return true;
            }
            return false;
        });

        vector<string> ans(n);
        for(int i = 0; i < n; ++i)
            ans[i] = features[v[i][1]];
        return ans;
    }
};
