
// 3638. Maximum Balanced Shipments
// https://leetcode.com/problems/maximum-balanced-shipments/




class Solution {
public:
    int maxBalancedShipments(vector<int>& weight) {
        int n = weight.size();

        // TODO
        // to make this faster, we could get away w/o collecting
        // the strictly decreasing subarrays in d, instead
        // we could do the calculation on the fly when one ends

        vector<array<int,2>> d; // strictly decreasing subarrays {{start0,end0}, {start1,end1}, ...}
        int start = -1;
        for(int i = 0; i < n-1; ++i) {

            if( weight[i] <= weight[i+1] ) {
                // if we are in a strictly decreasing run
                // then i marks the end
                if( start != -1 ) {
                    d.push_back({start, i});
                }
                start = -1;

            } else {
                if( start == -1 )
                    start = i;
            }
        }
        // finish up
        if( start != -1 )
            d.push_back({start, n-1});

        int ans = 0;
        for(auto& arr: d) {
            int lft = arr[0];
            int rgt = arr[1];
            int l = rgt - lft + 1;
            int balanced_shipments = l / 2; // floor on purpose
            ans += balanced_shipments;
        }

        return ans;
    }
};
