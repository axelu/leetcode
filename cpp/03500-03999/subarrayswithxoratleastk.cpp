
// 3632. Subarrays with XOR at Least K
// https://leetcode.com/problems/subarrays-with-xor-at-least-k/


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

        // we will start at most significant bit !!!
        // s max = 1e9 => 30 digits in binary
        for(int i = 29; i >= 0; --i) {
            int idx = (s>>i) & 1;
            if (!tn->children[idx]) {
                tn->children[idx] = init();
            }
            tn = tn->children[idx];
            ++tn->cnt;
        }

        return;
    }

    // walk our Trie
    long long count(int C, Trie* dic, int k) {
        Trie* tn = dic;

        long long ret = 0LL;

        // B ^ C = A
        // A is what we have in our Trie
        // the ask is to keep B >= k

        // k
        // B ^ C = A
        // 1   0   1
        // 1   1   0
        // 0   0   0
        // 0   1   1

        for(int i = 29; i >= 0; --i) {

            int bit_C = (C>>i) & 1;
            int bit_B = (k>>i) & 1;

            if( bit_B ) {
                // in order to keep B >= k 
                // we must continue in A with bit != C bit
                // see table above (first two cases)
                tn = tn->children[!bit_C];

            } else {
                // the bit in B is NOT set
                // see table above (last two cases)
                // as we are moving most significant to least significant
                // we can just count the opposites to C in A
                // and don't need to explore them further (pruning)
                if( tn->children[!bit_C] )
                    ret += tn->children[!bit_C]->cnt;
                tn = tn->children[bit_C];
            }

            if( tn == NULL )
                break;
        }

        // count if last bit (least significant) was set in B aka k
        if( tn )
            ret += tn->cnt;

        return ret;
    }

public:
    long long countXorSubarrays(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= n <= 1e5; 0 <= nums[i] <= 1e9

        // A ^ B = C    => A ^ C = B (and also B ^ C = A)
        // if we are at a given index and know C up to and including that index
        // and we have counted all 'A' along the way, we know all B and can count them
        // if B >= k

        /*
        // correct result, but obviously will not scale
        int prefix_xor[100001];
        prefix_xor[0] = 0;

        unordered_map<int,int> um;
        um[0] = 1;

        long long ans = 0LL;

        for(int i = 1; i <= n; ++i) {
           int C = prefix_xor[i] = prefix_xor[i-1] ^ nums[i-1];
    
            for(auto& p: um) {
                int A = p.first;
                long long cnt = p.second;

                int B = A ^ C;
                if( B >= k )
                    ans += cnt;
            }

            ++um[prefix_xor[i]];
        }
        */

        int prefix_xor = 0;
        
        Trie* root = init();
        add(0, root);

        long long ans = 0LL;

        for(int i = 1; i <= n; ++i) {
            prefix_xor = prefix_xor ^ nums[i-1];
            int C = prefix_xor;
    
            int cnt = count(C, root, k);
            // cout << "i " << i << " cnt " << cnt << " C " << C << endl;
            
            ans += cnt;

            add(prefix_xor, root);
        }


        return ans;
    }
};



// an interim solution to get a an accepted solution
class Solution {
private:
    struct Trie {
        struct Trie* children[2];
        int endOfWord; // count
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = 0;

        tn->children[0] = NULL;
        tn->children[1] = NULL;

        return tn;
    }

    void add(int s, Trie* dic) {
        struct Trie* tn = dic;

        do {
            if( s & 1 ) {
                if (!tn->children[1])
                    tn->children[1] = init();
                tn = tn->children[1];
            } else {
                if (!tn->children[0])
                    tn->children[0] = init();
                tn = tn->children[0];
            }
            s >>= 1;
        } while (s);

        ++tn->endOfWord;

        return;
    }

    // recursive
    long long count(int A, int bit, int C, Trie* tn, int k) {
        // bit is the bit index (0-indexed) starting from least significant bit
        // basically the depth we are at

        long long ret = 0LL;

        // we have two options
        //     go left (if 0 bit was present in at least one prefixXor) OR
        //     go right (if 1 bit was present in at least one prefixXor)

        if( tn->children[0] ) {
            Trie* tn0 = tn->children[0];
            if( tn0->endOfWord ) {
                int B = A ^ C;
                if( B >= k )
                    ret += (long long)(tn0->endOfWord);
            }
            ret += count(A, bit+1, C, tn0, k);
        }

        if( tn->children[1] ) {
            Trie* tn1 = tn->children[1];
            int A_new = A;
            A_new |= (1<<bit);
            if( tn1->endOfWord ) {
                int B = A_new ^ C;
                if( B >= k )
                    ret += (long long)(tn1->endOfWord);
            }
            ret += count(A_new, bit+1, C, tn1, k);

        }

        return ret;
    }

public:
    long long countXorSubarrays(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= n <= 1e5; 0 <= nums[i] <= 1e9

        // A ^ B = C    => A ^ C = B
        // if we are at a given index and know C up to and including that index
        // and we have counted all 'A' along the way, we know all B and can count them
        // if B >= k

        /*
        // correct result, but obviously will not scale
        int prefix_xor[100001];
        prefix_xor[0] = 0;

        unordered_map<int,int> um;
        um[0] = 1;

        long long ans = 0LL;

        for(int i = 1; i <= n; ++i) {
           int C = prefix_xor[i] = prefix_xor[i-1] ^ nums[i-1];
    
            for(auto& p: um) {
                int A = p.first;
                long long cnt = p.second;

                int B = A ^ C;
                if( B >= k )
                    ans += cnt;
            }

            ++um[prefix_xor[i]];
        }
        */

        // using the idea above though, what if we record the
        // prefixXor in a Trie, and at each 'node', we record
        // how many times we have seen it, respectively how
        // many more 'subnodes aka subtrees' exist. Then when
        // we are at a node and calculate the XOR along the way
        // when we reach a node for the XOR B is greater than or
        // equal k, then we know how often it will occur, because
        // it can only get greater from there.

        int prefix_xor[100001];
        prefix_xor[0] = 0;

        // unordered_map<int,int> um;
        // um[0] = 1;
        
        Trie* root = init();
        add(0, root);

        long long ans = 0LL;

        for(int i = 1; i <= n; ++i) {
           int C = prefix_xor[i] = prefix_xor[i-1] ^ nums[i-1];
    
            /*
            int tt1 = 0;
            for(auto& p: um) {
                int A = p.first;
                long long cnt = p.second;

                int B = A ^ C;
                if( B >= k )
                    tt1 += cnt;
            }
            */

            int cnt = count(0, 0, C, root, k);

            // cout << "i " << i << " tt1 " << tt1 << " cnt " << cnt << endl;

            // ans += tt1;
            ans += cnt;

            // ++um[prefix_xor[i]];
            add(prefix_xor[i], root);
        }



        return ans;
    }
};
