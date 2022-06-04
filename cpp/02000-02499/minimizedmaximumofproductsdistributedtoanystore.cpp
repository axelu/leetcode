
// 2064. Minimized Maximum of Products Distributed to Any Store
// https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/




class Solution {
private:
    bool can_distribute(int n, vector<int>& quantities, int k) {
        for(int x : quantities) {
            n -= x/k;
            if( x%k )
                --n;
            if( n < 0 )
                return false;
        }
        return true;
    }

    // binary search
    int search(int n, vector<int>& quantities, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = can_distribute(n,quantities,mid);
        if( f ) {
            // can we do better?
            int t = search(n,quantities,s,mid-1);
            return t != -1 ? t : mid;
        } else {
            return search(n,quantities,mid+1,e);
        }
    }

public:
    int minimizedMaximum(int n, vector<int>& quantities) {
        return search(n,quantities,1,*max_element(quantities.begin(),quantities.end()));
    }
};
