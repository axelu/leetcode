
// 2935. Maximum Strong Pair XOR II
// https://leetcode.com/problems/maximum-strong-pair-xor-ii/





class Solution {
private:
    int lower_bound(vector<int>& nums, int s, int n, int target) {
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        // int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;

        return s;
    }

    int findRightMostSetBit(unsigned int x) {
        // it is guaranteed that x > 0
        int ret = 0;
        x = x >> 1;
        while( x ) {
            ++ret;
            x = x >> 1;
        }
        return ret;
    }

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

    void add(int x, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 19; i >= 0; --i) {
            int idx = (x>>i) & 1;
            // cout << "add " << x << " depth " << i << " bit set " << idx << endl;
            if (!tn->children[idx]) {
                // cout << " new" << endl;
                tn->children[idx] = init();
            }

            tn = tn->children[idx];
        }

        // last node is end of word
        tn->endOfWord = x;
    }

    int search(int x, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 19; i >= 0; --i) {
            int idx = (x>>i) & 1;
            // if possible we want to go the opposite
            if (tn->children[!idx])
                tn = tn->children[!idx];
            else
                tn = tn->children[idx];
        }

        return tn->endOfWord;
    }

    bool isEmpty(Trie* dic) {
        if( dic->children[0] || dic->children[1] )
            return false;
        return true;
    }

    // Recursive function to delete a key from given Trie
    Trie* remove(Trie* dic, int x, int depth = 0) {
        //cout << "remove " << x << endl;
        //cout << "depth " << depth << endl;

        if( depth == 20 ) {
            delete (dic);
            dic = NULL;

            return dic;
        }

        int idx = (x>>(19-depth)) & 1;
        dic->children[idx] =
              remove(dic->children[idx], x, depth + 1);

        if (isEmpty(dic)) {
            delete (dic);
            dic = NULL;
        }

        return dic;
    }

public:
    int maximumStrongPairXor(vector<int>& nums) {
        // 1 <= nums[i] <= (2^20) - 1

        // smallest number >= nums[i]/2 gives us the greated XOR and is a strong pair

        sort(nums.begin(),nums.end());

        // remove dups
        for(auto it = next(nums.begin()); it != nums.end(); )
            if( *prev(it) == *it )
                it = nums.erase(it);
            else
                ++it;

        int n = nums.size(); // cout << n << endl;
        if( n == 1 )
            return 0;

        int ans = 0;

        int ans_rightmostsetbit = -1;

        // Trie* root = init();
        Trie* root;
        int trie_size = 0;
        int s; // lowest element index in trie

        /*
        add(5, root);add(4, root); //  add(3, root);
        remove(root,5);
        // add(2, root);
        remove(root,4);
        */

        // return 99;

        for(int i = n-1; i >= 0; --i) {
            // cout << "i " << i << " ";
            // early exit
            // if ans most significant bit is not set in nums[i], we cannot get a better answer
            if( ans_rightmostsetbit > findRightMostSetBit(nums[i]) ) {
                break;
            }

            if( trie_size == 0 ) {
                root = init();
                // cout << "adding " << nums[i] << endl;
                add(nums[i], root);
                ++trie_size;
                s = i;
            }


            int target = nums[i]/2;
            if( target * 2 < nums[i] )
                ++target;

            int lb = lower_bound(nums, 0, i+1, target); // cout << "lb " << lb << endl;
            // ideally we had a data structure where we can lookup the max xor pair in range [lb,i] inclusive
            // we can do brute force
            /*
            for(int j = lb; j < i; ++j) {
                // TODO early exit

                int t = nums[j] ^ nums[i];
                if( t > ans ) {
                    ans = t;
                    ans_rightmostsetbit = findRightMostSetBit(ans);
                }
            }
            */
            // what if we maintain a trie
            // on each iteration we remove nums[i] from it
            // our lb may go lower from one iteration to the next, so we need to add the new value(s) to the trie if applicable
            // our search will at each step prefer the oposite bit in nums[i], so we get the best possible value
            // our trie will need to start from most significant bit though
            if( lb < s ) {
                // we need to add nums[i-1], nums[i-2], ..., nums[lb] to our trie
                for(int k = s-1; k >= lb; --k) {
                    // cout << "adding " << nums[k] << endl;
                    add(nums[k], root);
                    ++trie_size;
                }

                s = lb;
            }

            int y = search(nums[i], root);
            int t = y ^ nums[i];
            if( t > ans ) {
                ans = t;
                ans_rightmostsetbit = findRightMostSetBit(ans);
            }



            // remove nums[i] from Trie
            // cout << "removing " << nums[i] << endl;
            remove(root, nums[i]);
            --trie_size;
        }

        return ans;
    }
};
