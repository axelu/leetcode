
// 2122. Recover the Original Array
// https://leetcode.com/problems/recover-the-original-array/





class Solution {
private:
    unordered_map<int,unordered_set<int>> um; // val, indicies in nums with val
    unordered_set<int> k2s;
    int seen[2000];
    int n,n2;

    void print_seen() {
        for(int i = 0; i < n2; ++i)
            cout << i << ":" << seen[i] << " ";
        cout << endl;
    }

    bool rec(vector<int>& nums, int pos, int k2) {
        if( pos == n2 )
            return true;

        if( seen[pos] != -1 )
            return rec(nums,pos+1,k2);

        // we have a choice
        //    nums[pos] is a lower OR
        //    nums[pos] is a higher

        auto me = um.find(nums[pos]);
        me->second.erase(pos);

        auto f = um.find(nums[pos]+k2);
        if( f != um.end() && !f->second.empty() ) {
            seen[pos] = 0;
            int idx = *f->second.begin();
            f->second.erase(idx);
            seen[idx] = 1;
            if( rec(nums,pos+1,k2) )
                return true;
            // back track
            f->second.insert(idx);
            seen[idx] = -1;
            seen[pos] = -1;
        }

        f = um.find(nums[pos]-k2);
        if( f != um.end() && !f->second.empty() ) {
            seen[pos] = 1;
            int idx = *f->second.begin();
            f->second.erase(idx);
            seen[idx] = 0;
            if( rec(nums,pos+1,k2) )
                return true;
            // back track
            f->second.insert(idx);
            seen[idx] = -1;
            seen[pos] = -1;
        }

        // back track
        me->second.insert(pos);
        return false;
    }

public:
    vector<int> recoverArray(vector<int>& nums) {
        n2 = nums.size();   // 2 * n == nums.length
        n = n2 / 2;         // 1 <= n <= 1000

        /*
        // there has to be a k
        // even the 1st element of nums, there must be a k that connects it to some other element
        // let us get all possible k's
        um[nums[0]].insert(0);
        for(int i = 1; i < n2; ++i) {
            um[nums[i]].insert(i);
            int diff = abs(nums[0] - nums[i]);
            if( diff != 0 && diff % 2 == 0 )
                k2s.insert(diff);
        }

        memset(seen,-1,sizeof seen);
        int k; // it is guaranteed that at least one valid array arr exists
        for(int k2: k2s) {
            if( rec(nums,0,k2) ) {
                k = k2 / 2;
                break;
            }
        }

        // cout << "k " << k << endl;
        // print_seen();

        vector<int> ans;
        for(int i = 0; i < n2; ++i)
            if( seen[i] == 0 )
                ans.push_back(nums[i] + k);

        return ans;
        */

        sort(nums.begin(),nums.end());

        int k; // it is guaranteed that at least one valid array arr exists
        int k2_prev = -1;
        for(int d = 1; d <= n; ++d) {
            int k2 = nums[d] - nums[0];
            if( k2 == 0 || k2 % 2 || k2 == k2_prev )
                continue;
            // cout << "k2 " << k2 << endl;
            k2_prev = k2;
            memset(seen,-1,sizeof seen);
            int i = 0, j = -1;
            int numsi_prev = -1;
            for(; i < n2; ++i) { // TODO better (earlier) exit criteria
                if( seen[i] != -1 )
                    continue;
                if( nums[i] != numsi_prev ) {
                    auto lb = lower_bound(nums.begin(),nums.end(),nums[i] + k2);
                    if( lb == nums.end() || *lb != nums[i] + k2 )
                        break;
                    j = distance(nums.begin(),lb);
                    numsi_prev = nums[i];
                } else {
                    ++j;
                }
                // cout << "i " << i << " j " << j << endl;
                if( j >= n2 || nums[j] - nums[i] != k2 )
                    break;
                // cout << "i " << i << " nums[i] " << nums[i] << " j " << j << " nums[j] " << nums[j] << endl;
                seen[i] = 0;
                seen[j] = 1;
            }
            if( i == n2 ) {
                k = k2 / 2;
                break;
            }
        }

        // cout << "k " << k << endl;
        // print_seen();

        vector<int> ans;
        for(int i = 0; i < n2; ++i)
            if( seen[i] == 0 )
                ans.push_back(nums[i] + k);

        return ans;
    }
};
