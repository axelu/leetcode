
// 683. K Empty Slots
// https://leetcode.com/problems/k-empty-slots/



class Solution {
private:
    pair<int,int> t[80008]; // segment tree leftmost and rightmost turned on lightbulb
    int n;
    bool f;
    int K;

    pair<int,int> combine(pair<int,int>& a, pair<int,int>& b) {
        int left_rightmost = a.second;
        if( left_rightmost == -1 )
            left_rightmost = a.first;

        int right_leftmost = b.first;
        if( right_leftmost == -1 )
            right_leftmost = b.second;

        if( left_rightmost != -1 && right_leftmost != -1 )
            if( right_leftmost - left_rightmost - 1 == K )
                f = true;

        // we need to communicate up
        // the leftmost and rightmost turned on lightbulbs if any
        int left_most = a.first;
        if( left_most == -1 )
            left_most = a.second;
        if( left_most == -1 )
            left_most = b.first;
        if( left_most == -1 )
            left_most = b.second;

        int right_most = b.second;
        if( right_most == -1 )
            right_most = b.first;
        if( right_most == -1 )
            right_most = a.second;
        if( right_most == -1 )
            right_most = a.first;

        return {left_most,right_most};
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            // sentinel at 0 and n+1
            if( tl == 0 )
                t[v] = make_pair(-100000,-100000);
            else if( tl == n+1 )
                t[v] = make_pair(100000,100000);
            else
                t[v] = make_pair(-1,-1); // off
        } else {
            int tm = (tl + tr) / 2;
            build(v*2, tl, tm);
            build(v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    void update(int v, int tl, int tr, int pos) {
        if (tl == tr) {
            t[v] = make_pair(pos,pos);
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
    int kEmptySlots(vector<int>& bulbs, int k) {
        n = bulbs.size();
        if( k > n-2 )
            return -1;

        f = false;
        K = k;
        build(1,0,n+1);

        // TODO we can exit if the mox window of not turned on lightbulbs is less than k
        //      we can skip turning on any lightbulbs in windows less than k

        for(int i = 0; i < n; ++i) {
            update(1,0,n+1,bulbs[i]);
            if( f )
                return i+1;
        }

        return -1;
    }
};
