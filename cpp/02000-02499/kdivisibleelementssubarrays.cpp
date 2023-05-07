
// 2261. K Divisible Elements Subarrays
// https://leetcode.com/problems/k-divisible-elements-subarrays/




class Solution {
private:

    struct Trie{
        unordered_map<int,Trie*> children;
    };

    Trie * init() {
        Trie * tn = new Trie();

        return tn;
    }

    int add(vector<int>& nums, int s, int k, int p, Trie* dic) {
        struct Trie* tn = dic;

        int ret = 0;

        int cnt = 0;
        bool f = false;

        for(int i = s; i < nums.size(); ++i) {
            int idx = nums[i];
            if( idx % p == 0 )
                ++cnt;
            if( cnt > k )
                break;
            if( !tn->children[idx] ) {
                f = true;
                tn->children[idx] = init();
            }
            if( f )
                ++ret;
            tn = tn->children[idx];
        }

        return ret;
    }

public:
    int countDistinct(vector<int>& nums, int k, int p) {
        Trie * root = init();

        int ans = 0;
        for(int i = nums.size()-1; i >= 0; --i) {
            int t = add(nums,i,k,p,root);
            // cout << "i " << i << " t " << t << endl;
            ans += t;
        }

        return ans;
    }
};
