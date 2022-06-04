
// 1521. Find a Value of a Mysterious Function Closest to Target
// https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/



class Solution {
private:
    int f(vector<int>& arr, int l, int r) {
        // 0 <= l, r < arr.length
        if( r < l )
            return -1000000000;

        int ans = arr[l];
        for(int i = l + 1; i <= r; ++i)
           ans = ans & arr[i];

        return ans;
    }

    int * t; // segment tree holding x[l] & x[l+1] ... & x[r]

    void build(int a[], int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int mid = (tl + tr) / 2;
            build(a, v*2, tl, mid);
            build(a, v*2+1, mid+1, tr);
            t[v] = t[v*2] & t[v*2+1];
        }
    }

    int query(int v, int tl, int tr, int l, int r) {
        // cout << "query v " << v << " tl " << tl << " tr " << tr << " l " << l << " r " << r << endl;
        if (l > r)
            return 1048575; // binary 11111111111111111111
        if (l == tl && r == tr)
            return t[v];

        int mid = (tl + tr) / 2;
        // cout << "mid " << mid << endl;

        if( r <= mid)     // query falls in left subtree
            return query(v*2,tl,mid,l,r);
        else if( l > mid) // query falls in right subtree
            return query(v*2+1,mid+1,tr,l,r);

        // query covers the mid point
        // get answer for [l,mid]
        int a = query(v*2,tl,mid,l,mid);
        // get answer for [mid+1,r]
        int b = query(v*2+1,mid+1,tr,mid+1,r);

        return a & b;
    }



public:
    int closestToTarget(vector<int>& arr, int target) {
        // returns minimum possible value of |f(arr,l,r) - target|
        int n = arr.size();

        int ans = 1000000000;

        /*
        // brute force
        for(int i = 0; i < n; ++i)
            for(int j = i; j < n; ++j) {
                int t = f(arr,i,j);
                // cout << "l " << i << " r " << j << " t " << t << endl;
                ans = min(ans,abs(target-t));
            }

        return ans;
        */

        // build a segment tree
        int T[4*n];
        t = T;
        build(arr.data(),1,0,n-1);

        for(int i = 0; i < n; ++i) {
            int s = i;
            int e = n - 1;
            while( s <= e ) {
                int mid = s + ((e - s)/2);
                // cout << "calling query" << endl;
                int t = query(1,0,n-1,i,mid);
                // cout << "l " << i << " r " << mid << " t " << t << endl;
                if( t > target )
                    s = mid + 1;
                else
                    e = mid - 1;

                ans = min(ans,abs(target-t));
            }
        }

        return ans;
    }
};
