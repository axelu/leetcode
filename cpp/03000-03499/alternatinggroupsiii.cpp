
// 3245. Alternating Groups III
// https://leetcode.com/problems/alternating-groups-iii/






/* wathing out for the fact it is circular
 * example [0,1,0,1] query count of alternating groups with size 3
 * 0 1 2 3|4 5 6 7 (index 4-7 because circular)
 * 0 1 0 1|0 1 0 1
 * -----
 *   -----
 *     -----
 *       -----
 * answer = 4
 *
 * example [0,1,0,1,1] query count of alternating groups with size 3
 * 0 1 2 3 4|5 6 7 8 9(index 5-9 because circular)
 * 0 1 0 1 1|0 1 0 1 1
 * -----
 *   -----
 *         -----
 * answer = 3
 *
 * if at any given point in time, meaning after any updates,
 * we knew the sum of the length of all alternating groups AND
 * the count, we can answer the the question
 * additinally we must know if there is an alternating group crossing the end/begin
 * so that we can discount our calculation by groups starting beyond the end
 * example [1,0,1,1,0,1,0,0,1,0,1,0,1,0], query count of alternating groups with size 3
 * there are 3 alternating subarrays: [0,2], [3,6], [7,16*] *16 because circular
 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3|4 5 6
 * 1 0 1 1 0 1 0 0 1 0 1 0 1 0|1 0 1
 * ----- ------- ------------------- alternating groups
 * count  3
 * sum   17
 * how many groups of length 3 can be make based on sum? sum-groupsize+1 = 17 - 3 + 1 = 15
 * discount because of group crossings: there count - 1 crossings, hence (groupsize-1) * (count-1) = (3-1)*(3-1) = 4
 * do we have a group crossing the end/begin: yes -> [7,16] -> length after end 16-n+1 = 16-14+1 = 3,
 *    so one group we need to discount
 * answer: 15 - 4 - 1 = 10
 * we could keep track of count and sum in a binary indexed tree (Fenwick tree), where each element represents the size
 * and the value either the count of sum, so we can just sum up for group sizes equal or greater like get_sum(l,r)
 * where l the size of the query
 *
 */
class Solution {
private:
    vector<int> bit_cnt;  // binary indexed tree, 0 indexed, point update, range query (sum)
    vector<int> bit_sum;  // binary indexed tree, 0 indexed, point update, range query (sum)

    int n;
    int n_extended;
    map<int,int> intervals; // key begin, value end
    int cross_i;
    int cross_j;

    int sum(vector<int>& bit, int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(vector<int>& bit, int l, int r) {
        return sum(bit, r) - sum(bit, l - 1);
    }

    void add(vector<int>& bit, int n, int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

    map<int,int>::iterator delete_interval(map<int,int>::iterator it) {

        int s = it->first;
        int e = it->second;
        // cout << "delete_interval s " << s << " e " << e << endl;
        if( s < n ) {
            int l = e-s+1;
            add(bit_cnt, n_extended+1, l, -1);
            add(bit_sum, n_extended+1, l, -l);
        }
        if( s < n && e >= n ) {
            cross_i = -1;
            cross_j = -1;
        }

        return intervals.erase(it);
    }

    map<int,int>::iterator add_interval(int s, int e) {
        // we guarantee that an entry with key s does not exist
        // cout << "add_interval s " << s << " e " << e << endl;

        if( s < n ) {
            int l = e-s+1;
            add(bit_cnt, n_extended+1, l, 1);
            add(bit_sum, n_extended+1, l, l);
        }
        if( s < n && e >= n ) {
            cross_i = s;
            cross_j = e;
        }

        return intervals.insert({s,e}).first;
    }

    void change_interval(map<int,int>::iterator it, int e) {

        int s = it->first;
        int cur_e = it->second;
        // cout << "change_interval s " << s << " cur_e " << cur_e << " [new] e " << e << endl;
        if( s < n ) {
            int l = cur_e-s+1;
            add(bit_cnt, n_extended+1, l, -1);
            add(bit_sum, n_extended+1, l, -l);
        }
        if( s < n && cur_e >= n ) {
            cross_i = -1;
            cross_j = -1;
        }

        it->second = e;

        if( s < n ) {
            int l = e-s+1;
            add(bit_cnt, n_extended+1, l, 1);
            add(bit_sum, n_extended+1, l, l);
        }
        if( s < n && e >= n ) {
            cross_i = s;
            cross_j = e;
        }

        return;
    }

    void process_update(int idx) {
        // cout << "process_update idx " << idx << endl;

        auto it = prev(intervals.upper_bound(idx));
        // CASE a idx is begin and end of interval, then combine left,middle(us),right
        // CASE b idx is begin, then shrink right extend left
        // CASE c idx is end, then shrink left, extend right
        // CASE d idx is neither, then existing begin [begin=as-is, end=idx-1]; new(idx,idx); new(idx+1,as-is end)

        // a
        if( it->first == idx && it->second == idx ) {
            // our length is 1

            if( it == intervals.begin() ) { // if idx == 0, it must be intervals.begin()
                auto it_next = next(it);
                int re = it_next->second;
                delete_interval(it_next);
                change_interval(it, re);
            } else if( next(it) == intervals.end() ) {
                auto it_prev = prev(it);
                delete_interval(it);
                change_interval(it_prev, idx);
            } else {
                auto it_prev = prev(it);
                it = delete_interval(it); // it now points to the interval that was to our right
                int re = it->second;
                delete_interval(it);
                change_interval(it_prev, re);
            }

        // b
        } else if(  it->first == idx ) {

            if( it == intervals.begin() ) {
                int e = it->second;
                // remove current interval
                delete_interval(it);
                // add a new interval [idx+1,e];
                add_interval(idx+1,e);
                // add a new interval [idx,idx];
                 add_interval(idx,idx);

            } else {
                auto it_prev = prev(it);
                // remove current interval
                int e = it->second;
                delete_interval(it);
                // add a new interval [idx+1,e];
                add_interval(idx+1,e);
                // extend the prior interval
                change_interval(it_prev, idx);
            }

        // c
        } else if( it->second == idx ) {

            if( next(it) == intervals.end() ) {
                 // add a new interval [idx,idx];
                add_interval(idx,idx);
                 // shrink the current interval
                change_interval(it, idx-1);

            } else {
                auto it_next = next(it);
                // remove next interval
                int e = it_next->second;
                delete_interval(it_next);
                 // add a new interval [idx,e];
                add_interval(idx,e);
                // shrink the current interval
                change_interval(it, idx-1);
            }

        // d
        } else {
            int e = it->second;
            change_interval(it,idx-1);
            add_interval(idx,idx);
            add_interval(idx+1,e);
        }


        return;
    }

public:
    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        n = colors.size();
        n_extended = n + (n-2); // because max group size in query is n-1

        vector<int> colors_extended(n_extended);
        for(int i = 0; i < n_extended; ++i) {
            colors_extended[i] = colors[i%n];
            // cout << colors_extended[i] << " ";
        }
        // cout << endl;

        bit_cnt.assign(n_extended+1, 0); // +1, because we could have an all wrap around like in [0,1,0,1,0,1]
        bit_sum.assign(n_extended+1, 0);

        cross_i = -1;
        cross_j = -1;

        int i = 0, j = 1;
        for(; j < n_extended; ++j) {
            if( colors_extended[j-1] == colors_extended[j] ) {
                // a group ends that begins at i and ends at j-1
                add_interval(i,j-1);
                i = j;
            }
        }
        // finish up
        add_interval(i,j-1);

        vector<int> ans;
        for(int q = 0; q < queries.size(); ++q) {
            // question
            if( queries[q][0] == 1 ) {
                int group_sz = queries[q][1];

                int cnt = sum(bit_cnt, group_sz, n_extended);
                if( cnt > 0 ) {
                    int tot = sum(bit_sum, group_sz, n_extended);

                    int res = tot - group_sz + 1;
                    // don't count group crossings
                    res -= (group_sz-1) * (cnt-1);
                    // don't count groups starting at n and beyond
                    if( cross_i != -1 ) {
                        // length of crossing group after n respectively starting at n
                        int l_after_n = cross_j - n + 1;
                        if( l_after_n >= group_sz )
                            res -= l_after_n - group_sz + 1;
                    }
                    ans.push_back(res);

                } else {
                    ans.push_back(0);
                }

            // update
            } else {
                int idx = queries[q][1];
                int color = queries[q][2];

                if( colors_extended[idx] == color )
                    continue;

                colors_extended[idx] = color;
                if( idx + n < n_extended )
                    colors_extended[idx+n] = color;

                // debug
                /*
                for(int k = 0; k < n_extended; ++k)
                    cout << colors_extended[k] << " ";
                cout << endl;
                */

                // CASES
                // A create a new group          111111    -> 110111
                //                                 x           ---
                // B combine two adjacent groups 1011101   -> 1010101
                //                               ---x---      -------
                // C extend a group              111110101 -> 111010101
                //                                  x-----      -------
                // and the oposite of A, B and C

                // special consideration if idx == 0 or idx == n_extended-1
                // special consideration if idx + n < n_extended (wraps around, so we need to change in two places)

                process_update(idx);
                if( idx + n < n_extended )
                    process_update(idx + n);

            }
        }

        return ans;
    }
};
