
// 3444. Minimum Increments for Target Multiples in an Array
// https://leetcode.com/problems/minimum-increments-for-target-multiples-in-an-array/




class Solution {
private:
    int solve1(vector<int>& nums, int n, int target) {
        // nums is sorted in non-decreasing order
        // returns the smallest difference
        // of an element in nums <= k * target
        // where 1 <= k <= x and k * x is
        // the 1st element greater nums[n-1];

        int nums_mn = nums[0];
        int nums_mx = nums[n-1];
        stack<int> multiples;
        int a = target;
        while( a < nums_mx ) {
            if( a >= nums_mn )
                multiples.push(a);
            a += target;
        }
        multiples.push(a);

        int ret = INT_MAX;
        while( !multiples.empty() ) {
            int _target = multiples.top();
            multiples.pop();

            // binary search greatest element less than target or equal target
            // returns n-1 if nums[n-1] < target
            // returns  -1 if nums[0] > target <= we will not have this
            int s = 0;
            int e = n; // n = nums.size()
            int mid;
            while(s < e) {
                mid = s + ((e-s)/2);
                if( nums[mid] > _target )
                    e = mid;
                else
                    s = mid+1;
            }
            if( (s < n && nums[s] > _target) || s == n )
                --s;

            ret = min(ret, _target - nums[s]);
            if( ret == 0 )
                break;
        }

        return ret;
    }

    int nums_cnt[10001]; // val in nums, count

    vector<array<int,2>> get_best(vector<int>& nums, int n, int target, int m) {
        // n = nums.size();
        // m = target.size();

        int nums_mn = nums[0];
        int nums_mx = nums[n-1]; // TODO this should really be the LCM of nums?
        stack<int> multiples;
        int a = target;
        while( a < nums_mx ) {
            if( a >= nums_mn )
                multiples.push(a);
            a += target;
        }
        multiples.push(a);

        auto cmp = [](const array<int,2>& a, const array<int,2>& b) {
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] > b[1] ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);

        unordered_set<int> seen;
        while( !multiples.empty() ) {
            int _target = multiples.top();
            multiples.pop();
            // binary search greatest element less than target or equal target
            // returns n-1 if nums[n-1] < target
            // returns  -1 if nums[0] > target <= we will not have this
            int s = 0;
            int e = n; // n = nums.size()
            int mid;
            while(s < e) {
                mid = s + ((e-s)/2);
                if( nums[mid] > _target )
                    e = mid;
                else
                    s = mid+1;
            }
            if( (s < n && nums[s] > _target) || s == n )
                --s;

            // TODO push if empty or if distance is less or if less than m in pq
            // TODO don't push dups !!!
            // int key = (s<<14) + (_target - nums[s]);
            int key = (nums[s]<<14) + (_target - nums[s]);
            auto p = seen.insert(key);
            if( p.second ) {
                // pq.push({_target - nums[s], s});
                pq.push({_target - nums[s], nums[s]});
            }
            // if( pq.size() > m )
            //     pq.pop();
            // we could also have pq.size() < m, when target = nums_mx
            //while( pq.size() < m ) {
            //    --s;
            //    pq.push({_target - nums[s], s});
            //}

            int pushed = 1;
            while( s-1 >= 0 && pushed < m ) {
                --s;
                // key = (s<<14) + (_target - nums[s]);
                key = (nums[s]<<14) + (_target - nums[s]);
                p = seen.insert(key);
                if( p.second ) {
                    // pq.push({_target - nums[s], s});
                    pq.push({_target - nums[s], nums[s]});
                    ++pushed;
                }
            }
        }
        while( pq.size() > m )
            pq.pop();

        vector<array<int,2>> ret;
        while( !pq.empty() ) {
            ret.push_back(pq.top());
            pq.pop();
        }

        return ret;
    }

    const int INF = 1000000;

    int rec(vector<int>& nums, vector<int>& target,
            vector<vector<array<int,2>>>& best, int n, int pos, vector<array<int,2>>& taken) {

        // n = target.size()

        if( pos == n )
            return 0;

        int ret = INF;

        // has someone before us maybe already used a multiple of us?
        int target_idx = (n-1) - pos;
        int target_val = target[target_idx];
        // cout << "rec pos " << pos << " target_idx " << target_idx << " target_val " << target_val << endl;

        bool skip = false;
        for(auto arr: taken) {
            int d   = arr[0];
            // int idx = arr[1]; // idx in nums
            int val = arr[1]; // val in nums
            // if( ((nums[idx] + d) % target_val) == 0 ) {
            if( ((val + d) % target_val) == 0 ) {
                ret = min(ret, rec(nums, target, best, n, pos+1, taken));
                skip = true;
                break;
            }
        }

        // we can skip this completely if we did above

        if( !skip ) {
            // try all combinations (worst case 16 = 4 * 4)
            // for(int i = 0; i < n; ++i) {   // n = target_sz; 1 <= n <= 4
            for(int i = 0; i < best[pos].size(); ++i) {
                int d   = best[pos][i][0]; // distance
                // int idx = best[pos][i][1]; // idx in nums
                int val = best[pos][i][1]; // val in nums

                // we cannot use it, if someone in target before us use it,
                // unless the distance is the same as we would use it
                bool take = true;
                bool can_use = true;
                for(auto arr: taken) {
                    // if( arr[1] == idx ) {
                        // someone before us used the same idx in nums
                    if( arr[1] == val ) {
                        // // someone before us used the same val in nums
                        if( arr[0] == d ) {
                            // ... but used it with the same distance
                            d = 0;        // don't double count
                            take = false; // its already in taken
                        } else {
                            // we may still use the same value with a different distance
                            // if we have multiple and still at least one remaining
                            if( nums_cnt[val] == 0 )
                                can_use = false;
                        }
                        break;
                    }
                }
                if( !can_use )
                    continue;

                if( take ) {
                    taken.push_back(best[pos][i]);
                    --nums_cnt[best[pos][i][1]];
                    // cout << "    rec pos " << pos << " target_idx " << target_idx << " target_val " << target_val << " ";
                    // cout << "taking d " << best[pos][i][0] << " idx " << best[pos][i][1] << " adjusted d " << d << endl;
                }
                ret = min(ret, d + rec(nums, target, best, n, pos+1, taken));
                // backtrack
                if( take ) {
                    taken.pop_back();
                    ++nums_cnt[best[pos][i][1]];
                }
            }
        } // end skip

        return ret;
    }

public:
    int minimumIncrements(vector<int>& nums, vector<int>& target) {
        // 1 <= nums[i], target[i] <= 1e4

        // start with the largest element in target,
        // because smaller elements in target maybe a divisor of them,
        // so be satisfying the larger element, we satisfied the smaller one

        // check if a multiple in nums already exists, if so we are done
        // we need to find the largest nums[i] that has the smallest distance
        // to a multiple of target under investigation (we can only increase nums)
        // example: target 8; nums 15, 22 => increase 15 by 1 => ans 1

        // watch out for a case where we would increase an element in nums,
        // however that element is a multiple of another element in target
        // example: target 3, 8; nums: 9, 1001
        // so 9 is already a multiple of 3, but 9 + 7 = 16, which would satisfy 8
        // but there could also be multiple of the same value in nums

        sort(begin(nums),end(nums));

        sort(begin(target),end(target));
        // de-dup target
        for(auto it = target.begin(); it != target.end(); ) {
            if( next(it) != target.end() && *it == *(next(it)) )
                it = target.erase(it);
            else
                ++it;
        }
        int nums_sz = nums.size(); // 1 <= nums.length <= 50000
        int target_sz = target.size(); // 1 <= target.length <= 4; target.length <= nums.length

        // edge case target_sz = 1
        if( target_sz == 1 )
            return solve1(nums, nums_sz, target[0]);

        // is there a solution with no adjustments?
        bool nums_contains_all = true;
        for(int i = 0; i < target_sz; ++i) {
            int d = solve1(nums, nums_sz, target[i]);
            if( d != 0 ) {
                nums_contains_all = false;
                break;
            }
        }
        if( nums_contains_all )
            return 0;

        /*
        auto a = get_best(nums, nums_sz, target[0], target_sz);
        cout << target[0] << ": ";
        for(auto& arr: a) {
            cout << arr[0] << "," << arr[1] << "," << nums[arr[1]] << " ";
        }
        cout << endl;
        */

        // count each val in nums
        memset(nums_cnt,0,sizeof nums_cnt);
        for(int i: nums)
            ++nums_cnt[i];

        vector<vector<array<int,2>>> best(target_sz);
        for(int i = target_sz-1; i >= 0; --i) { // largest to smallest
            auto t = get_best(nums, nums_sz, target[i], target_sz);
            /*
            cout << "target_i " << i << " target " << target[i] << endl;
            for(auto& arr: t) {
                // cout << "d " << arr[0] << " nums idx " << arr[1] << " nums val " << nums[arr[1]] << " ";
                cout << "d " << arr[0] << " nums val " << arr[1] << " ";
            }
            cout << endl;
            */
            best[target_sz-1-i] = t;
        }

        vector<array<int,2>> taken;
        return rec(nums, target, best, target_sz, 0, taken);
    }
};
