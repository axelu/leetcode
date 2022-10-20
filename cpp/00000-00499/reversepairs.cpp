
// 493. Reverse Pairs
// https://leetcode.com/problems/reverse-pairs/



class Solution {
private:
    struct T {
        int a;
        vector<long> org;
        vector<long> dbl;
    };

    T t[200000];

    // binary search lower bound
    int search(vector<long>& nums, int s, int n, int target) {
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        // int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;

        return s;
    }

    vector<long> mergesort(vector<long>& a, vector<long>& b) {
        int i = 0, j = 0, k = 0;
        vector<long> res(a.size()+b.size());
        while( i < a.size() && j < b.size() ) {
            if( a[i] < b[j] ) {
                res[k] = a[i];
                ++i;
            } else {
                res[k] = b[j];
                ++j;
            }
            ++k;
        }
        while( i < a.size() ) {
            res[k] = a[i];
            ++i;
            ++k;
        }
        while( j < b.size() ) {
            res[k] = b[j];
            ++j;
            ++k;
        }

        return res;
    }

    T combine(T& left, T& right) {
        T tn;
        int n = 0;

        int s = 0;
        int e = right.dbl.size();
        int left_org_sz = left.org.size();
        for(int i = 0; i < left_org_sz; ++i) {
            int idx = search(right.dbl,s,e,left.org[i]);
            if( idx == 0 )
                continue;
            n += (idx - s) * (left_org_sz - i);
            s = idx;
        }
        tn.org = mergesort(left.org,right.org);
        tn.dbl = mergesort(left.dbl,right.dbl);
        tn.a = left.a + right.a + n;
        return tn;
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = {0,{a[tl]},{2L*a[tl]}};
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

public:
    int reversePairs(vector<int>& nums) {
        build(nums,1,0,nums.size()-1);
        return t[1].a;
    }
};
