
// 1889. Minimum Space Wasted From Packaging
// https://leetcode.com/problems/minimum-space-wasted-from-packaging/



class Solution {
private:

    // binary search greatest element less than target or equal target
    int search(vector<int>& nums, int s, int e, int target) {
        // returns n-1 if nums[n-1] < target
        // returns s-1 if nums[s] > target
        int n = e;
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid] > target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && nums[s] > target) || s == n )
            --s;

        return s;
    }

public:
    int minWastedSpace(vector<int>& packages, vector<vector<int>>& boxes) {
        int n = packages.size();

        // we only have a solution if the largest package we have
        // can fit into a box, in other words:
        // at least one supplier must make a box equal or larger
        // than our largest box, we can rule out suppliers

        // max waste:
        //    we have 100000 packages of size 1 and one supplier
        //    making a box of size 100000
        //    max waste = 100000x100000 - 1x100000
        //              = 10000000000 - 100000
        //              = 9999900000

        sort(packages.begin(),packages.end());

        long prefixSum[n+1];prefixSum[0] = 0;
        for(int i = 1; i <=n; ++i)
            prefixSum[i] = prefixSum[i-1] + packages[i-1];

        long ans = 9999900001;

        // for each vendor
        for(auto& v : boxes) {
            sort(v.begin(),v.end());
            if( v.back() >= packages.back() ) {

                long waste = 0; // waste with current vendor
                int s = 0;
                for(int box : v) {

                    int i = search(packages,s,n,box);
                    // we can ship all packages up to and including index i in box

                    // number of packages we are shipping = number of boxes
                    long cnt = i - s + 1;
                    // volume of boxes we are shipping
                    long vol_boxes = cnt * box;
                    // volume of packages we are shipping
                    long vol_packages = prefixSum[i+1] - prefixSum[s];

                    waste += vol_boxes - vol_packages;

                    ++i;
                    if( i == n ) // all packages shipped
                        break;
                    s = i;
                }
                if( waste == 0 )
                    return 0;
                ans = min(ans,waste);
            }
        }

        return ans != 9999900001 ? ans % 1000000007 : -1;
    }
};
