
// 1099. Two Sum Less Than K
// https://leetcode.com/problems/two-sum-less-than-k/



// segment tree -> "Merge Sort Tree".
// find the largest number smaller to a specified number. no modification queries.
// query in the form of:
//     for three given numbers (l,r,x) we have to find the maximal number in the segment a[l…r],
//         which is less than  x
// see https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-9
class Solution {
private:
    // binary search
    int search(vector<int>& v, int s, int e, int x) {
        if( s > e ) return -1;

        int mid = s + ((e - s)/2);
        if( v[mid] >= x ) {
            // go to the left
            return search(v,s,mid-1,x);
        } else {
            return max(v[mid],search(v,mid+1,e,x));
        }
    }

    vector<int> t[400]; // 1 <= nums.length <= 100 -> t[4*MAXN]

    void build(int a[], int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = vector<int>(1, a[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            merge(t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(),
                back_inserter(t[v]));
        }
    }

    int query(int v, int tl, int tr, int l, int r, int x) {
        if( l > r )
            return -1;
        if( l == tl && r == tr ) {
            return search(t[v],0,t[v].size()-1,x);
        }
        int tm = (tl + tr) / 2;
        return max(query(v*2, tl, tm, l, min(r, tm), x),
                query(v*2+1, tm+1, tr, max(l, tm+1), r, x));
    }

public:
    int twoSumLessThanK(vector<int>& nums, int k) {
        int n = nums.size();
        if( n == 1 ) return -1;

        build(nums.data(),1,0,n-1);
        int ans = -1;
        int x,res;
        for(int i = 1; i < n; ++i) {
            if( nums[i-1] >= k ) continue;
            x = k-nums[i-1];
            res = query(1,0,n-1,i,n-1,x);
            if( res > 0 ) ans = max(ans,nums[i-1]+res);
        }

        return ans;
    }
};
