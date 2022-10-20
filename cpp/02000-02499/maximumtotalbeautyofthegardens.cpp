
// 2234. Maximum Total Beauty of the Gardens
// https://leetcode.com/problems/maximum-total-beauty-of-the-gardens/





class Solution {
private:
    bool solve(vector<int>& flowers, int n, int t, long long newFlowers, long long prefixSum[]) {
        auto lb = lower_bound(flowers.begin(),flowers.begin()+n,t);
        long long d = distance(flowers.begin(),lb);
        return prefixSum[d] + newFlowers >= d * t;
    }

public:
    long long maximumBeauty(vector<int>& flowers, long long newFlowers, int target, int full, int partial) {
        long long n = flowers.size();

        sort(flowers.begin(),flowers.end());

        long long prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + flowers[i-1];

        // edge case
        if( flowers[0] >= target ) {
            // all gardens have already at least target flowers
            return n * full;
        }

        // total_beauty = full * number of complete gardens  +  partial * (min flowers in any incomplete garden)

        long long ans = 0;

        for(int i = n-1; i >= 0; --i) {

            if( flowers[i] < target ) {

                // binary search
                int s = flowers[0];
                int e = min((long long)target-1,flowers[i]+newFlowers);
                int mid;
                while(s <= e) {
                    mid = s + ((e-s)/2);
                    bool f = solve(flowers,i+1,mid,newFlowers,prefixSum);
                    if( f )
                        s = mid + 1;
                    else
                        e = mid - 1;
                }

                ans = max(ans,full * (n-(i+1)) + (long long)partial * e);

                // top off the current garden up to target if we can
                if( flowers[i] + newFlowers > target ) {
                    newFlowers = newFlowers - (target - flowers[i]);
                } else {
                    newFlowers = -1; // signal down that we ran out of flowers
                    break;
                }
            }
        }
        // finish up
        if( newFlowers >= 0 ) {
            // we were able to plant ALL gardens up to target
            ans = max(ans,(long long)full * n);
        }

        return ans;
    }
};
