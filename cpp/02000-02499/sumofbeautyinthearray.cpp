

// 2012. Sum of Beauty in the Array
// https://leetcode.com/problems/sum-of-beauty-in-the-array/





class Solution {
private:
    pair<int,int> * t;

    pair<int, int> combine(pair<int,int> a, pair<int,int> b) {
        return make_pair(min(a.first,b.first),max(a.second,b.second));
    }

    void build(int a[], int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = make_pair(a[tl],a[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    pair<int, int> get_min_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return make_pair(INT_MAX,INT_MIN);
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        return combine(get_min_max(v*2, tl, tm, l, min(r, tm)),
            get_min_max(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    int sumOfBeauties(vector<int>& nums) {
        int n = nums.size();

        // segment tree that returns min and max in given interval
        pair<int,int> T[4*n];
        t = T;
        build(nums.data(),1,0,n-1);


        int ans = 0;
        for(int i = 1; i < n-1; ++i) {
            // cout << "i " << i << " nums[i] " << nums[i] << endl;

            // left max
            int lftMx = get_min_max(1,0,n-1,0,i-1).second;
            // cout << "lftMx " << lftMx << endl;
            if( lftMx >= nums[i] ) {
                if( nums[i-1] < nums[i] && nums[i] < nums[i+1] )
                    ++ans;
                continue;
            }

            // right min
            int rgtMn = get_min_max(1,0,n-1,i+1,n-1).first;
            // cout << "rgtMn " << rgtMn << endl;
            if( nums[i] >= rgtMn ) {
                if( nums[i-1] < nums[i] && nums[i] < nums[i+1] )
                    ++ans;
                continue;
            }

            ans += 2;
        }


        return ans;
    }
};
