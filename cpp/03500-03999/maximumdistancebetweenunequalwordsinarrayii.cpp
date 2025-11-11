
// 3706. Maximum Distance Between Unequal Words in Array II
// https://leetcode.com/problems/maximum-distance-between-unequal-words-in-array-ii/


class Solution {
public:
    int maxDistance(vector<string>& words) {
        map<string,int> mp; // key: word; value: last idx

        // vector with words sorted by their index of first appearance
        vector<pair<string,int>> firstidx; // {{worda,first idx}, ...}

        for(int i = 0; i < words.size(); ++i) {
            auto p = mp.insert({words[i],i});
            if( p.second )
                firstidx.push_back({words[i],i});
            else
                p.first->second = i;
        }

        vector<pair<string,int>> lastidx; // {{worda,last idx}, ...}
        for(auto& p: mp)
            lastidx.push_back({p.first, p.second});
        sort(begin(lastidx), end(lastidx), [](const pair<string,int>& a, const pair<string,int>& b){
            return a.second < b.second;
        });

        int n = firstidx.size();
        if( n == 1 )
            return 0;

        int ans = 0;
        for(int i = 0; i < n; ++i) {
            if( firstidx[i].first != lastidx[n-1].first )
                ans = max(ans, lastidx[n-1].second - firstidx[i].second + 1 );
            else
                ans = max(ans, lastidx[n-2].second - firstidx[i].second + 1 );
        }

        return ans;
    }
};
