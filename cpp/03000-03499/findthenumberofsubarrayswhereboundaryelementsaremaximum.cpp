
// 3113. Find the Number of Subarrays Where Boundary Elements Are Maximum
// https://leetcode.com/problems/find-the-number-of-subarrays-where-boundary-elements-are-maximum/





class Solution {
private:
    int t[200000]; // segment tree memory efficient indexing
    int n;

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    int get_max(int v, int tl, int tr, int l, int r) {
        // cout << "get_max v " << v << " tl " << tl << " tr " << tr << " l " << l << " r " << r << endl;
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(get_max(v+1, tl, tm, l, min(r, tm)),
                   get_max(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    // binary search
    int search(vector<int>& a, int b, int s, int e, int mx) {
        // b is fixed starting index!!!
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( get_max(1,0,n-1,a[b],a[mid]) == mx ) {
            // can we do better?
            int t = search(a,b,mid+1,e,mx);
            return t != -1 ? t : mid;
        }

        return search(a,b,s,mid-1,mx);
    }

public:
    long long numberOfSubarrays(vector<int>& nums) {
        n = nums.size();

        build(nums,1,0,n-1);

        unordered_map<int,vector<int>> um; // val, indicies with that value
        for(int i = 0; i < n; ++i) {
            auto p = um.insert({nums[i],{i}});
            if( !p.second )
                p.first->second.push_back(i);
        }

        long long ans = n;

        for(auto it = um.begin(); it != um.end(); ++it) {
            int val = it->first;
            // cout << "val " << val << endl;
            auto indicies = it->second;
            int indicies_sz = indicies.size();
            /*
            for(int i = 0; i < indicies_sz; ++i)
                cout << i << ":" << indicies[i] << " ";
            cout << endl;
            */

            if( indicies_sz == 1 ) {
                // do nothing

            } else if( indicies_sz == 2 ) {
                int lmx = get_max(1, 0, n-1, indicies[0], indicies[1]);
                if( lmx == val )
                    ++ans;

            } else {
                // we have 2 ore more indicies with value
                // we will find the rightmost one
                // then advance by one till the rightmost one is the last one

                int b = 0;
                int s = 0;
                int e = indicies_sz-1;
                int t = search(indicies, b, s, e, val); // t will be at minimum s
                long long ln = (t-s+1);
                ans += ln * (ln+1LL)/2LL - ln;
                while( t != e ) {
                    b = t+1;
                    s = t+1;
                    t = search(indicies, b, s, e, val); // t will be at minimum s
                    ln = (t-s+1);
                    ans += ln * (ln+1LL)/2LL - ln;
                }
            }
        }

        return ans;
    }
};
