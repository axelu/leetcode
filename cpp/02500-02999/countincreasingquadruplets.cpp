
// 2552. Count Increasing Quadruplets
// https://leetcode.com/problems/count-increasing-quadruplets/






class Solution {
private:
    vector<int> bit; // binary indexed tree bit, 0 indexed
    int n;

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }

public:
    long long countQuadruplets(vector<int>& nums) {
        int nums_sz = nums.size();

        // we are basically after a 'increasing' zig-zag
        //          X
        //     X   /
        //    /\  /
        //   /  \/
        //  /    X
        // X
        // i  j  k  l
        // idea: fix/iterate over all possible pairs j,k


        n = nums_sz + 1;
        bit.assign(n,0);

        // cout << "right to left to build prefix" << endl;
        bit.assign(n,0);
        for(int i = 1; i < n; ++i)
            add(i, 1);
        add(nums[nums_sz-1],-1);
        add(nums[nums_sz-2],-1);
        int prefix[nums_sz][nums_sz];memset(prefix,0,sizeof prefix);
        map<int,int> ks; // nums[k],k
        ks.insert({nums[nums_sz-2], nums_sz-2});
        for(int j = nums_sz-3; j > 0; --j) {
            int nums_j = nums[j];
            // cout << "j " << j << " nums_j " << nums_j << endl;
            add(nums_j, -1);
            for(auto& p: ks) {
                if( p.first > nums_j )
                    break;
                int k = p.second;
                int nums_k = p.first;
                // cout << "   k " << k << " nums_k " << nums_k << endl;
                prefix[j][k] = sum(nums_k - 1);
            }
            ks.insert({nums_j,j});
        }

        long long ans = 0LL;

        // cout << "left to right suffix" << endl;
        bit.assign(n,0);
        for(int i = 1; i <= n; ++i)
            add(i, 1);
        add(nums[0],-1);
        add(nums[1],-1);
        // int suffix[nums_sz][nums_sz];memset(suffix,0,sizeof suffix);
        map<int,int> js; // nums[j],j
        js.insert({nums[1], 1});
        for(int k = 2; k < nums_sz-1; ++k) {
            int nums_k = nums[k];
            // cout << "k " << k << " nums_k " << nums_k << endl;
            add(nums_k, -1);
            for(auto rit = js.rbegin(); rit != js.rend(); ++rit) {
                if( rit->first < nums_k )
                    break;
                int j = rit->second;
                int nums_j = rit->first;
                // cout << "   j " << j << " nums_j " << nums_j << endl;
                // suffix[j][k] = sum(nums_sz) - sum(nums_j);
                ans += prefix[j][k] * (long long)(sum(nums_sz) - sum(nums_j));
            }
            js.insert({nums_k,k});
        }

        /*
        // cout << "left to right to build ans" << endl;
        js.clear(); // nums[j],j
        js.insert({nums[1], 1});
        for(int k = 2; k < nums_sz-1; ++k) {
            int nums_k = nums[k];
            // cout << "k " << k << " nums_k " << nums_k << endl;
            for(auto rit = js.rbegin(); rit != js.rend(); ++rit) {
                if( rit->first < nums_k )
                    break;
                int j = rit->second;
                int nums_j = rit->first;
                // cout << "   j " << j << " nums_j " << nums_j << endl;
                ans += (long long)prefix[j][k] * (long long)suffix[j][k];
            }
            js.insert({nums_k,k});
        }
        */

        return ans;
    }
};
