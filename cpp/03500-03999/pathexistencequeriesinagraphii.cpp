
// 3534. Path Existence Queries in a Graph II
// https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        int q_sz = queries.size();
        if( n == 1 )
            return vector<int>(q_sz,0);

        vector<vector<int>> _queries(q_sz); // {{u_val, v_val, query_idx}, ...} u_val <= v_val 
        for(int i = 0; i < q_sz; ++i) {
            int u = queries[i][0];
            int u_val = nums[u];

            int v = queries[i][1];
            int v_val = nums[v];

            if( v_val < u_val )
                swap(u_val, v_val);

            _queries[i] = {u_val, v_val, i};
        }    
        sort(_queries.begin(), _queries.end(), [](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] > b[1] ) {
                    return true;
                }
            }
            return false;
        });

        // for each value we have, record the max value we can jump to
        // if we cannot reach another value greater, then record -1
        // value line
        sort(nums.begin(), nums.end());
        
        // remove duplicates
        for(auto it = next(nums.begin()); it != nums.end(); ) {
            if( *prev(it) == *it )
                it = nums.erase(it);
            else
                ++it;
        }

        n = nums.size();

        vector<int> value_line(n,-1);
        queue<vector<int>> q; // {nums[i], i}
        q.push({nums[n-1], n-1});
        for(int i = n-2; i >= 0; --i) {
            int curr_val = nums[i];

            while( !q.empty() && q.front()[0] > curr_val + maxDiff )
                q.pop();

            if( !q.empty() )
                value_line[i] = q.front()[1];

            q.push({curr_val,i});
        }

        /*
        for(int i = 0; i < n; ++i)
            cout << nums[i] << " ";
        cout << endl;
        for(int i = 0; i < n; ++i)
            cout << value_line[i] << " ";
        cout << endl;
        */  

        vector<int> ans(q_sz, -1);

        unordered_map<long,int> mem;
        long key;

        int value_line_idx = n-1;
        for(int j = q_sz-1; j >= 0; ) {   // index in _queries
            int u_val = _queries[j][0];

            // sync our index on the value line
            while( nums[value_line_idx] != u_val )
                --value_line_idx;
            // position us at the greatest index we could jump to
            // if possible
            int nums_idx = value_line[value_line_idx];

            // process all queries at the same u_val
            int jumps = 1;
            while( j >= 0 && _queries[j][0] == nums[value_line_idx] ) {
                u_val = _queries[j][0];
                int v_val = _queries[j][1];
                int q_idx = _queries[j][2];
                // cout << "q " << q_idx << " u_val " << u_val << " v_val " << v_val << endl;

                if( u_val == v_val ) {
                    ans[q_idx] = queries[q_idx][0] == queries[q_idx][1] ? 0 : 1;
                    --j;
                    continue;
                }
                if( nums_idx == -1 ) {
                    --j;
                    continue;
                }

                bool answered = false;
                while( nums_idx != -1 && nums[nums_idx] < v_val ) {
                    // at the value we are at nums[nums_idx], have we asked already for v_val?
                    key = ((long)(nums[nums_idx])<<17) + v_val;
                    auto f = mem.find(key);
                    if( f != mem.end() ) {
                        key = ((long)(u_val)<<17) + v_val;
                        mem[key] = jumps + f->second;
                        ans[q_idx] = jumps + f->second;
                        answered = true;
                        break;
                    }

                    nums_idx = value_line[nums_idx];
                    ++jumps;
                }

                if( answered ) {
                    --j;
                    continue;
                }

                if( nums_idx == -1 ) {
                    --j;
                    continue;
                }

                key = ((long)(u_val)<<17) + v_val;
                mem[key] = jumps;
                ans[q_idx] = jumps;
                --j;
            }
        }

        return ans;
    }
};




