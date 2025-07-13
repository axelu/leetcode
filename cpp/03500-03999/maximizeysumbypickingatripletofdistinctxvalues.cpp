
// 3572. Maximize Y‑Sum by Picking a Triplet of Distinct X‑Values
// https://leetcode.com/problems/maximize-ysum-by-picking-a-triplet-of-distinct-xvalues/





class Solution {
public:
    int maxSumDistinctTriplet(vector<int>& x, vector<int>& y) {
        int n = x.size(); // x.size() == y.size()

        unordered_map<int,int> um;
        for(int i = 0; i < n; ++i) {
            int x_i = x[i];
            if( um.find(x_i) == um.end() ) {
                um[x_i] = y[i];
            } else {
                um[x_i] = max(um[x_i], y[i]);
            }
        }

        if( um.size() < 3 )
            return -1;

        vector<int> v;
        for(auto& p: um)
            v.push_back(p.second);

        sort(v.begin(),v.end(),greater<int>());
        return v[0] + v[1] + v[2];
    }
};
