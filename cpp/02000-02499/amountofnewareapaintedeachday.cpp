





// 2158. Amount of New Area Painted Each Day
// https://leetcode.com/problems/amount-of-new-area-painted-each-day/


class Solution {
private:
    int t[400000]; // segment tree

    int update(int v, int tl, int tr, int l, int r) {
        // cout << "v " << v << " tl " << tl << " tr " << tr << " l " << l << " r " << r << endl;
        if (l > r)
            return 0;

        int n = tr-tl+1;    // number of nodes in our segment
        if( t[v] == n )     // all nodes in this segment are painted, no need to go further
            return 0;

        if (l == tl && r == tr) {
            // we have a matching segment
            int ret = n - t[v]; // number of unpainted nodes in this segment
            t[v] = n;           // paint all nodes in this segment
            return ret;
        } else {
            int tm = (tl + tr) / 2;
            int a = update(v*2, tl, tm, l, min(r, tm));
            int b = update(v*2+1, tm+1, tr, max(l, tm+1), r);

            t[v] = t[v*2] + t[v*2+1] ;

            return a+b;
        }
    }


public:
    vector<int> amountPainted(vector<vector<int>>& paint) {
        memset(t,0,sizeof t); // build a segment tree, all segments are unpainted aka 0

        int n = paint.size();

        vector<int> ans(n);

        for(int i = 0; i < n; ++i)
            ans[i] = update(1,0,100000,paint[i][0],paint[i][1]-1);

        return ans;



        /*
        int tsz = 100000;

        // build(1,0,tsz);
        memset(t,0,sizeof t);
        int x;
        x = update(1,0,tsz,2,5-1);
        cout << x << endl;
        for(int i = 0; i < 32; ++i)
            cout << i << ":" << t[i] << " ";
        cout << endl;
        x = update(1,0,tsz,7,10-1);
        cout << x << endl;
        for(int i = 0; i < 32; ++i)
            cout << i << ":" << t[i] << " ";
        cout << endl;
        x = update(1,0,tsz,3,9-1);
        cout << x << endl;
        for(int i = 0; i < 32; ++i)
            cout << i << ":" << t[i] << " ";
        cout << endl;



        return {};
        */
    }
};
