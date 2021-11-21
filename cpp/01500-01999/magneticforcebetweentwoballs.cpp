
// 1552. Magnetic Force Between Two Balls
// https://leetcode.com/problems/magnetic-force-between-two-balls/




class Solution {
private:
    int n;

    // binary search equal or greater target
    int search2(vector<int>& position, int s, int e, int target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( position[mid] == target ) {
            return mid;
        } else if( position[mid] > target ) {
            // can we do better?
            int t = search2(position,s,mid-1,target);
            return t == -1 ? mid : t;
        } else {
            // position[mid] < target
            return search2(position,mid+1,e,target);
        }
    }

    bool solve(vector<int>& position, int m, int d) {
        // greedily distribute m balls at least d positions apart
        // start at position[0]
        int idx = 0;
        for(int i = 1; i < m; ++i) {
            idx = search2(position,idx+1,n-1,position[idx]+d);
            if( idx == -1 )
                return false;
        }
        return true;
    }

    // binary search
    int search(vector<int>& position, int m, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        // solve for mid
        if( solve(position,m,mid) ) {
            // can we do better?
            int t = search(position,m,mid+1,e);
            return t == -1 ? mid : t;
        } else {
            return search(position,m,s,mid-1);
        }
    }
public:
    int maxDistance(vector<int>& position, int m) {
        n = position.size();
        sort(begin(position),end(position));

        // pass 1
        int mn = INT_MAX;
        for(int i = 1; i < n; ++i)
            mn = min(mn,position[i]-position[i-1]);

        int mx = (position[n-1]-position[0])/(m-1);

        // base cases
        if( n == m )
            return mn;
        if( m == 2 )
            return mx;

        return search(position,m,mn,mx);
    }
};
