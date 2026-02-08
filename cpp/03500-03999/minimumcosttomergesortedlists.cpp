
// 3801. Minimum Cost to Merge Sorted Lists
// https://leetcode.com/problems/minimum-cost-to-merge-sorted-lists/


class Solution {
private:
    int countSetBits(int i) {
        int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

public:
    long long minMergeCost(vector<vector<int>>& lists) {
        int n = lists.size(); // 2 <= n <= 12

        // we can use a bit mask with n bits to keep track of state
        // if a list is part of that state, the bit is set
        // for any given state, no matter how we get there,
        // the state's median and state's length is the same
        // each state also represents a number of lists merged (nbr of set bits)
        // merging two lists, the order does not matter
        // we can build the answer bottom up
        // the state with one list is trivial
        // nbr list in state    merge
        // 2                    1 + 1 (one with any other one)
        // 3                    2 + 1 (2 with any one not part of it (mask2 & mask1 = 0))
        // 4                    3 + 1
        //                      2 + 2
        // 5                    4 + 1
        //                      3 + 2
        // 6                    5 + 1
        //                      4 + 2
        //                      3 + 3
        // ...
        // 12                   11 + 1
        //                      10 + 2
        //                       9 + 3
        //                       8 + 4
        //                       7 + 5
        //                       6 + 6

        // precompute length, nbr set bits, median and length for all states 1 <= i <= n-1
        // index by nbr set bits and state [13][4096]

        int end_state = pow(2, n) - 1; // cout << "end_state " << end_state << endl;
        // vector<vector<int>> setbits_state(n+1); // index: nbr setbits value: list of states with nbr setbits
        vector<int> setbits_state[13];
        for(int i = 1; i <= end_state; ++i) {
            int _setbits = countSetBits(i);
            setbits_state[_setbits].push_back(i);
        }

        // vector<bool> seen(end_state+1, false);
        bool seen[4096];memset(seen, false, sizeof seen);
        // vector<long long> cost(end_state+1, LLONG_MAX);
        long long cost[4096];
        for(int i = 0; i < 4096; ++i) cost[i] = LLONG_MAX;

        // 1 setbit = 1 list
        // vector<pair<int,int>> state_ml(end_state+1); // index: state value: {median, length}
        pair<int,int> state_ml[4096];
        for(int i = 0; i < n; ++i) {
            int state = (1 << i);
            int len = lists[i].size();
            int median_idx = len/2;
            if( len % 2 == 0 )
                --median_idx;
            int median_val = lists[i][median_idx];
            state_ml[state] = {median_val, len};
            seen[state] = true;
            cost[state] = 0LL;
        }

        for(int t = 2; t <= n; ++t) {       // total set bits
            int hi = t-1;
            int lo = t/2;
            if( t % 2 )
                ++lo;
            for(int i = hi; i >= lo; --i) {
                int j = t-i;
                // cout << t << ": " << i << " " << j << endl;
                for(int state_i: setbits_state[i]) {
                    for(int state_j: setbits_state[j]) {
                        if( (state_i & state_j) != 0 )
                            continue;

                        int state_new = state_i | state_j;
                        if( !seen[state_new] ) {
                            seen[state_new] = true;

                            vector<int> nums;
                            for(int k = 0; k < n; ++k) {
                                if( (state_new>>k) & 1 )
                                    nums.insert(nums.end(), lists[k].begin(), lists[k].end());
                            }
                            sort(nums.begin(), nums.end());
                            int len = nums.size();
                            int median_idx = len/2;
                            if( len % 2 == 0 )
                                --median_idx;
                            int median_val = nums[median_idx];
                            state_ml[state_new] = {median_val, len};
                        }

                        long long cost_i = cost[state_i];
                        long long len_i  = state_ml[state_i].second;
                        long long median_i = state_ml[state_i].first;

                        long long cost_j = cost[state_j];
                        long long len_j  = state_ml[state_j].second;
                        long long median_j = state_ml[state_j].first;

                        long long cost_new = cost_i + cost_j + len_i + len_j + abs(median_i - median_j);
                        cost[state_new] = min(cost[state_new], cost_new);
                    }
                }
            }
        }

        return cost[end_state];
    }
};
