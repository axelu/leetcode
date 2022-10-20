

// 2179. Count Good Triplets in an Array
// https://leetcode.com/problems/count-good-triplets-in-an-array/





class Solution {
private:
    void print_vector(vector<int>& v) {
        for(auto x: v)
            cout << x << " ";
        cout << endl;
    }

    void print_set(set<int>& v) {
        for(auto x: v)
            cout << x << " ";
        cout << endl;
    }

    int t[400000];

    void update(int v, int tl, int tr, int l, int r, int add) {
        if (l > r)
            return;
        if (l == tl && r == tr) {
            t[v] += add;
        } else {
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), add);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, add);
        }
    }

    int get(int v, int tl, int tr, int pos) {
        if (tl == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            return t[v] + get(v*2, tl, tm, pos);
        else
            return t[v] + get(v*2+1, tm+1, tr, pos);
    }

public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        // n == nums1.length == nums2.length
        // 3 <= n <= 10^5

        int n = nums1.size();

        unordered_map<int,int> nums2_idx;
        for(int i = 0; i < n; ++i)
            nums2_idx[nums2[i]] = i;

        long long ans = 0LL;

        // left to right
        memset(t,0,sizeof t);
        int j = nums2_idx[nums1[0]];
        update(1,0,n-1,j,n-1,1);
        vector<long long> l;
        for(int i = 1; i < n-1; ++i) {
            j = nums2_idx[nums1[i]];
            if( j != 0 && j != n-1 ) {
                l.push_back(get(1,0,n-1,j));
            }
            update(1,0,n-1,j,n-1,1);
        }

        // right to left
        memset(t,0,sizeof t);
        j = nums2_idx[nums1[n-1]];
        update(1,0,n-1,0,j,1);
        int k = l.size()-1;
        for(int i = n-2; i > 0; --i) {
            j = nums2_idx[nums1[i]];
            if( j != 0 && j != n-1 ) {
                ans += l[k] * get(1,0,n-1,j);
                --k;
            }
            update(1,0,n-1,0,j,1);
        }

        return ans;
    }
};
