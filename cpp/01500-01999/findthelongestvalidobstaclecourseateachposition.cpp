
// 1964. Find the Longest Valid Obstacle Course at Each Position
// https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/
// both solutions here passed 8/28/2022

class Solution {
private:
    int t[10000001]; // binary indexed tree bit
    int maxIdx = 10000000;

    // binary indexed tree can support range queries for min, max
    // that are in range [0,r] inclusive and updates are always
    // changing it to a smaller respectively larger value only
    // range max query [0,r] inclusive
    int get_max(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = max(ret, t[r]);
        return ret;
    }

    void update(int idx, int val) {
        for (; idx <= maxIdx; idx = idx | (idx + 1))
            t[idx] = max(t[idx], val);
    }

public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        int n = obstacles.size();
        memset(t,0,sizeof t);

        vector<int> ans(n);

        for(int i = 0; i < n; ++i) {
            int mx_length = get_max(obstacles[i]);
            ans[i] = mx_length+1;
            update(obstacles[i],mx_length+1);
        }

        return ans;
    }
};

class Solution {
private:
    // unordered_map<int,int> t; // segment tree
    int t[20000002]; // segment tree memory efficient indexing

    int get_max(int v, int tl, int tr, int l, int r) {
        // cout << "get_max v " << v << " tl " << tl << " tr " << tr << " l " << l << " r " << r << endl;
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(get_max(v+1, tl, tm, l, min(r, tm)),
                   get_max(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            t[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos, new_val);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }


public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        int n = obstacles.size();

        vector<int> ans(n);

        for(int i = 0; i < n; ++i) {
            int mx_length = get_max(1,0,10000000,0,obstacles[i]);
            ans[i] = mx_length+1;
            update(1,0,10000000,obstacles[i],mx_length+1);
        }

        return ans;
    }
};
