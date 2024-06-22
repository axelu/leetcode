
// 3164. Find the Number of Good Pairs II
// https://leetcode.com/problems/find-the-number-of-good-pairs-ii/





class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        int m = nums2.size();

        // pre-process nums1
        unordered_map<int,long long> um1;
        for(int i = 0; i < n; ++i)
            ++um1[nums1[i]];

        // pre-process nums2
        unordered_map<int,long long> um2;
        for(int i = 0; i < m; ++i)
            ++um2[nums2[i] * k];

        long long ans = 0LL;
        for(auto it = um1.begin(); it != um1.end(); ++it) {
            int v = it->first;

            unordered_map<int,long long>::iterator f;
            if( v > 1 ) {
                f = um2.find(v);
                if( f != um2.end() )
                    ans += it->second * f->second;
            }

            for(int i = 1; i * i <= v; ++i) {
                if( v % i )
                    continue;

                f = um2.find(i);
                if( f != um2.end() )
                    ans += it->second * f->second;
                int vi = v/i;
                if( vi != i && vi != v ) {
                    f = um2.find(vi);
                    if( f != um2.end() )
                        ans += it->second * f->second;
                }
            }
        }

        return ans;
    }
};
