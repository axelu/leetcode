
// 1803. Count Pairs With XOR in a Range
// https://leetcode.com/problems/count-pairs-with-xor-in-a-range/





class Solution {
private:
    struct Trie {
        struct Trie* children[2];
        int cnt;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->cnt = 0;

        tn->children[0] = NULL;
        tn->children[1] = NULL;

        return tn;
    }

    void add(int s, Trie* dic) {
        struct Trie* tn = dic;
        ++tn->cnt;

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
            ++tn->cnt;
        }

    }

    int count(int limit, int number, Trie* dic) {
        struct Trie* tn = dic;
        int ret = 0;

        // limit  number    continue
        //   bit     bit
        //     0       1    subtree 1, nbrs in subtree 0 don't make pairs below limt
        //     1       0    subtree 1, nbrs in subtree 0 make pairs below limit
        //     0       0    subtree 0, nbrs in subtree 1 don't make pairs below limt
        //     1       1    subtree 0, nbrs in subtree 1 make pairs below limit

        int limitBit,numberBit;
        for(int i = 31; i >= 0; --i) {
            limitBit  = limit  & (1 << i) ? 1 : 0;
            numberBit = number & (1 << i) ? 1 : 0;

            if( !limitBit && numberBit ) {
                if( !tn->children[1] ) break;
                tn = tn->children[1];
            } else if( limitBit && !numberBit ) {
                if( tn->children[0] ) ret += tn->children[0]->cnt;
                if( !tn->children[1] ) break;
                tn = tn->children[1];
            } else if( !limitBit && !numberBit ) {
                if( !tn->children[0] ) break;
                tn = tn->children[0];
            } else {
                // limitBit && numberBit
                if( tn->children[1] ) ret += tn->children[1]->cnt;
                if( !tn->children[0] ) break;
                tn = tn->children[0];
            }

        }

        return ret;
    }

public:
    int countPairs(vector<int>& nums, int low, int high) {
        Trie* root = init();

        int ans = 0, nh, nl;
        add(nums[0],root);
        for(int i = 1; i < nums.size(); ++i) {
            nh = count(high+1,nums[i],root); // count strictly less than high+1
            nl = count(low,nums[i],root);    // count strictly less than low
            ans += nh -nl;
            add(nums[i],root);
        }
        return ans;
    }
};
