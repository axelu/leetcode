
// 1891. Cutting Ribbons
// https://leetcode.com/problems/cutting-ribbons/




class Solution {
private:
    bool canCut(vector<int>& ribbons, int k, int l) {
        // returns true if ribbons can be cut into at least k ribbons of length l
        // false otherwise

        int cnt = 0;
        for(int x : ribbons) {
            cnt += x / l;
            if( cnt >= k )
                return true;
        }

        return false;
    }

    // binary search
    int search(vector<int>& ribbons, int s, int e, int k) {
        if( s > e )
            return 0;

        int mid = s + ((e-s)/2);
        bool f = canCut(ribbons,k,mid);
        if( f ) {
            // can we do better?
            int t = search(ribbons,mid+1,e,k);
            return t != 0 ? t : mid;
        } else {
            return search(ribbons,s,mid-1,k);
        }
    }

public:
    int maxLength(vector<int>& ribbons, int k) {
        // goal to get k ribbons of the same length
        // length is to be maximized

        // our answer is between min and max ribbons[i]
        auto mx = max_element(begin(ribbons),end(ribbons));
        return search(ribbons,1,*mx,k);
    }
};
