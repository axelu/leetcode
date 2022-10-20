
// 2251. Number of Flowers in Full Bloom
// https://leetcode.com/problems/number-of-flowers-in-full-bloom/


class Solution {
private:
    int t[600000]; // segment tree

    // range addition
    void update(int v, int tl, int tr, int l, int r, int add) {
        if (l > r)
            return;
        if (l == tl && r == tr) {
            t[v] += add;
        } else {
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), add);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, add);
        }
    }

    int get(int v, int tl, int tr, int pos) {
        if (tl == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            return t[v] + get(v*2, tl, tm, pos);
        else
            return t[v] + get(v*2+1, tm+1, tr, pos);
    }

public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& persons) {
        // 1 <= flowers.length <= 5 * 10^4
        // flowers[i] = {starti,endi};
        // 1 <= starti <= endi <= 10^9
        // worst case we have 100,000 distinct start and end values

        set<int> idxs;
        for(auto& v: flowers) {
            idxs.insert(v[0]);
            idxs.insert(v[1]);
        }
        for(auto& i: persons)
            idxs.insert(i);

        int idx = 0;
        unordered_map<int,int> dic;
        for(auto it = idxs.begin(); it != idxs.end(); ++it)
            dic[*it] = idx++;

        memset(t,0,sizeof t);
        for(auto& v: flowers)
            update(1,0,idx,dic[v[0]],dic[v[1]],1);

        int k = persons.size();
        vector<int> ans(k);

        for(int i = 0; i < k; ++i)
            ans[i] = get(1,0,idx,dic[persons[i]]);

        return ans;
    }
};
