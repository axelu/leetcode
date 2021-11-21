
// 1707. Maximum XOR With an Element From Array
// https://leetcode.com/problems/maximum-xor-with-an-element-from-array/






class Solution {
private:
    struct Trie {
        struct Trie* children[2];
        int endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = -1;

        tn->children[0] = NULL;
        tn->children[1] = NULL;

        return tn;
    }

    void add(int s, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 31; i >= 0; --i) {
            if( s & (1 << i) ) {
                if (!tn->children[1])
                    tn->children[1] = init();
                tn = tn->children[1];
            } else {
                if (!tn->children[0])
                    tn->children[0] = init();
                tn = tn->children[0];
            }
        }

        // last node is end of word
        tn->endOfWord = s;
    }

    int search(int s, Trie* dic) {
        struct Trie* tn = dic;

        // at every bit we try to go opposite
        for(int i = 31; i >= 0; --i) {
            if( s & (1 << i) ) {
                if (tn->children[0])
                    tn = tn->children[0];
                else
                    tn = tn->children[1];
            } else {
                if (tn->children[1])
                    tn = tn->children[1];
                else
                    tn = tn->children[0];
            }
        }

        return tn->endOfWord;
    }

public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        sort(nums.begin(),nums.end());

        auto cmp = [](const array<int,3>& a, const array<int,3>& b) {
            return a[1] > b[1];
        };
        priority_queue<array<int,3>,vector<array<int,3>>,decltype(cmp)> pq(cmp);

        int n = queries.size();
        int i;
        for(i = 0; i < n; ++i)
            pq.push({queries[i][0],queries[i][1],i});

        vector<int> ans(n);
        int x,m,j=0;
        int k = nums.size();
        Trie* root = init();
        while( !pq.empty() ) {
            x = pq.top()[0];
            m = pq.top()[1];
            i = pq.top()[2];
            pq.pop();

            // add nums[j] into our trie for nums[j] <= m
            for(; j < k; ++j) {
                if( nums[j] > m ) break;
                add(nums[j],root);
            }
            if( j == 0 ) {
                ans[i] = -1;
                continue;
            }

            ans[i] = x^search(x,root);
        }
        return ans;
    }
};
