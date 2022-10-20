
// 632. Smallest Range Covering Elements from K Lists
// https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/



/*

[[4,10,15,24,26]]
[[4,10,15,24,26],[5,11]]
[[4,10,15,24,26],[3,11]]
[[4,10,15,24,26],[5,11]]
[[4,10,15,24,26],[5,11],[28,30]]
[[4,10],[4,12],[8,9,10]]
[[4,10],[4,12],[8,9]]
[[4,10],[9,10]]
[[4,10,12],[9,10]]
[[4,9,10,12],[9,10]]

*/


class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int n = nums.size(); // 1 <= n <= 3500
        if( n == 1 )
            return {nums[0][0],nums[0][0]};

        // 1 <= nums[i].length <= 50
        // worst case 3500 * 50 = 175000 distinct integers

        // We define the range [a, b] is smaller than range [c, d]
        // if b - a < d - c or a < c if b - a == d - c

        map<int,vector<int>> dic; // unique ints, rows in which they occur asc
        for(int i = 0; i < n; ++i) {
            auto it = nums[i].begin();
            dic[*it].push_back(i);
            ++it;
            for(; it != nums[i].end(); ++it)
                if( *prev(it) != *it )
                    dic[*it].push_back(i);
        }

        /*
        // debug
        for(auto it = dic.begin(); it != dic.end(); ++it)
            cout << it->first << " ";
        cout << endl;
        */

        // sliding window
        auto i = dic.begin(); // left index
        auto j = dic.begin(); // right index

        int start = i->first;
        int end   = prev(dic.end())->first;

        if( end - start == 0 )
            return {end,start};

        int cnt[n];memset(cnt,0,sizeof cnt);

        int all_rows = 0;
        for(; j != dic.end(); ++j) {
            //for(int k = 0; k < n; ++k) {
            //    cout << k << ":" << cnt[k] << " ";
            //}
            //cout << endl;
            //cout << "num i " << i->first << endl;
            //cout << "num j " << j->first << endl;
            for(int row : j->second) {
                //cout << "row " << row << " ";
                ++cnt[row];
                if( cnt[row] == 1 )
                    ++all_rows;
            }
            //cout << endl;

            if( all_rows == n ) {
                //cout << "window with all rows" << endl;
                int dist = j->first - i->first;
                //cout << "dist " << dist << endl;
                if( dist < end - start ) {
                    start = i->first;
                    end   = j->first;
                    if( dist == 0 )
                        break;
                }

                // shrink the window
                //cout << "shrinking the window" << endl;
                while( all_rows == n ) {
                    for(int row : i->second) {
                        --cnt[row];
                        if( !cnt[row] )
                            --all_rows;
                    }
                    ++i;
                }
                // calc again
                dist = j->first - prev(i)->first;
                //cout << "dist " << dist << endl;
                if( dist < end - start ) {
                    start = prev(i)->first;
                    end   = j->first;
                    if( dist == 0 )
                        break;
                }
            }
        }

        return {start,end};
    }
};
