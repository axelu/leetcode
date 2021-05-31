
// 1387. Sort Integers by The Power Value
// https://leetcode.com/problems/sort-integers-by-the-power-value/



class Solution {
private:
    unordered_map<int,int> seen;

    int getPower(int x) {
        if( x == 1 ) return 1;
        auto f = seen.find(x);
        if( f != seen.end() ) return f->second;
        int ans = x % 2 == 0 ? 1 + getPower(x/2) : 1 + getPower(3*x+1);
        seen.insert({x,ans});
        return ans;
    }
public:
    int getKth(int lo, int hi, int k) {
        // 1 <= lo <= hi <= 1000
        // 1 <= k <= hi - lo + 1
        if( lo == hi ) return lo;

        int n = hi-lo+1;
        array<int,2> v[n];
        for(int i = lo; i <= hi; ++i)
            v[i-lo] = {getPower(i),i};

        sort(v,v+n,[](const array<int,2>& a, const array<int,2>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) return true;
            }
            return false;
        });
        return v[k-1][1];
    }
};
