
// 3509. Maximum Product of Subsequences With an Alternating Sum Equal to K
// https://leetcode.com/problems/maximum-product-of-subsequences-with-an-alternating-sum-equal-to-k/






class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        int n = nums.size();

        // constraints
        // 1 <= nums.length <= 150
        // 0 <= nums[i] <= 12
        // -1e5 <= k <= 1e5
        // 1 <= limit <= 5000

        const int INF = 50001;

        // worst case sum all alternating nums[i] = 12 and 0: 150/2 * 12 = 900 respectively -900
        unordered_map<int,set<int>> negs; // key: sum if taken as negative, values: possible products
        unordered_map<int,set<int>> poss; // key: sum if taken as positive, values: possible products

        // from right to left
        for(int i = n-1; i >= 0; --i) {
            int val = nums[i];
            if( i == n-1 ) {
                // the last one could be taken as a positive or negative addend
                // but there will be nothing yet to work with behind us
                negs[-val].insert(val <= limit ? val : INF);
                poss[val].insert(val <= limit ? val : INF);

            } else {
                // the 1st one could only be taken as a positive addend

                // take as positive
                unordered_map<int,set<int>> parkposs;
                // insert ourselves
                parkposs[val].insert(val <= limit ? val : INF);
                for(auto it = negs.begin(); it != negs.end(); ++it) {
                    int new_sum = val + it->first;
                    if( val == 0 ) {
                        parkposs[new_sum].insert(0);

                    } else {
                        for(auto iti = it->second.begin(); iti != it->second.end(); ++iti) {
                            if( *iti == INF ) {
                                parkposs[new_sum].insert(INF);
                                // break; // last one as we are using set anyway
                            }
                            int new_product = *iti * val;
                            if( new_product > limit )
                                parkposs[new_sum].insert(INF);
                            else
                                parkposs[new_sum].insert(new_product);
                        }
                    }
                }

                // take as negative
                unordered_map<int,set<int>> parknegs;
                parknegs[-val].insert(val <= limit ? val : INF);
                if( i != 0 ) {
                    for(auto it = poss.begin(); it != poss.end(); ++it) {
                        int new_sum = -val + it->first;
                        if( val == 0 ) {
                            parknegs[new_sum].insert(0);

                        } else {
                            for(auto iti = it->second.begin(); iti != it->second.end(); ++iti) {
                                if( *iti == INF ) {
                                    parknegs[new_sum].insert(INF);
                                    // break; // last one as we are using set anyway
                                }
                                int new_product = *iti * val;
                                if( new_product > limit )
                                    parknegs[new_sum].insert(INF);
                                else
                                    parknegs[new_sum].insert(new_product);
                            }
                        }
                    }
                }

                for(auto p: parkposs) {
                    int new_sum = p.first;
                    for(int product: p.second)
                        poss[new_sum].insert(product);
                }
                for(auto p: parknegs) {
                    int new_sum = p.first;
                    for(int product: p.second)
                        negs[new_sum].insert(product);
                }
            }
        }

        if( poss.find(k) == poss.end() || *(poss[k].begin()) > limit )
            return -1;

        auto lb = poss[k].lower_bound(limit);
        if( *lb == limit )
            return limit;
        if( lb == poss[k].begin() )
            return -1;

        return *(prev(lb));
    }
};
