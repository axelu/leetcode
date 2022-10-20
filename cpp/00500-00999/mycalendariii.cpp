
// 732. My Calendar III
// https://leetcode.com/problems/my-calendar-iii/



class MyCalendarThree {
private:
    int ans;
    unordered_map<int,int> t;   // segment tree
    unordered_map<int,int> tmx; // segment tree

    // range update
    int update(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;

        if( tl == tr ) {
            ++t[v];
            return t[v];
        }

        if (l == tl && r == tr) {
            ++t[v];
        } else {
            int tm = (tl + tr) / 2;
            int a = update(v*2, tl, tm, l, min(r, tm));
            int b = update(v*2+1, tm+1, tr, max(l, tm+1), r);
            tmx[v] = max({tmx[v],a,b});
        }
        return t[v]+tmx[v];
    }

public:
    MyCalendarThree() {
        ans = 0;
    }

    int book(int start, int end) {
        return ans = max(ans,update(1,0,1000000000,start,end-1));
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(start,end);
 */
