
// 3670. Maximum Product of Two Integers With No Common Bits
// https://leetcode.com/problems/maximum-product-of-two-integers-with-no-common-bits/

class Solution {
private:
    struct Trie {
        struct Trie* children[2];
        int cnt;
        long long endOfWord; // our number
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->cnt = 0;
        tn->endOfWord = 0LL;

        tn->children[0] = NULL;
        tn->children[1] = NULL;

        return tn;
    }

    void add(int s, Trie* dic) {
        int org_s = s;

        struct Trie* tn = dic;

        do {
            if( s & 1 ) {
                if (!tn->children[1])
                    tn->children[1] = init();
                tn = tn->children[1];
                ++tn->cnt;
            } else {
                if (!tn->children[0])
                    tn->children[0] = init();
                tn = tn->children[0];
                ++tn->cnt;
            }
            s >>= 1;
        } while (s);

        // set endOfWord to our original integer
        tn->endOfWord = org_s;

        return;
    }

    void remove(int s, Trie* dic) {

        struct Trie* tn = dic;

        // stack<Trie*> tobedeleted;

        do {
            if( s & 1 ) {
                --tn->children[1]->cnt;
                if( tn->children[1]->cnt == 0 ) {
                    // tobedeleted.push(tn->children[1]);
                    Trie* p = tn;
                    tn = tn->children[1];
                    p->children[1] = NULL;
                } else {
                    tn = tn->children[1];
                }
                
            } else {
                --tn->children[0]->cnt;
                if( tn->children[0]->cnt == 0 ) {
                    // tobedeleted.push(tn->children[0]);
                    Trie* p = tn;
                    tn = tn->children[0];
                    p->children[0] = NULL;
                } else {
                    tn = tn->children[0];
                }               
            }
            s >>= 1;
        } while (s);

        /*
        // delete nodes in tobedeleted
        while( !tobedeleted.empty() ) {
            Trie* p = tobedeleted.top();
            tobedeleted.pop();
            delete (p);
        }
        */

        return;
    }

    // recursive
    long long search(int s, Trie* dic) {
        long long ret = 0LL;

        struct Trie* tn = dic;

        do {
            if( s & 1 ) {
                // bit in s is set, so we only have one choice
                // to proceed with non-set bit
                if( tn->children[0] )
                    tn = tn->children[0];
                else
                    break;
                // as we go from least significant to most significant
                // bit, no need to check for endOfWord on a non-set bit
            } else {
                // bit in s is NOT set, so we have two choices
                // to proceed: set bit OR unset bit
                if( tn->children[1] ) { // recurse
                    ret = max(ret, tn->children[1]->endOfWord);
                    ret = max(ret, search(s>>1, tn->children[1]));
                }
                if( tn->children[0] )   // continue
                    tn = tn->children[0];
                else
                    break;
            }
            s >>= 1;
        } while (s);

        return ret;
    }

public:
    long long maxProduct(vector<int>& nums) {
        int n = nums.size(); // 2 <= n <- 1e5

        // 1 <= nums[i] <= 1e6
        // decimal 1e6 -> binary 11110100001001000000 20digits

        // what if we create a binary Trie
        // we add every distinct integer in nums into our Trie
        // then we go from largest to smaller through distinct integers
        // in our Trie we navigate always to opposite, and if endOfWord
        // we multiply and keep track of max

        set<int> st;
        for(int i: nums)
            st.insert(i);

        Trie* root = init();
        for(int i: st)
            add(i, root);

        long long ans = 0;
        for(auto itr = st.rbegin(); itr != st.rend(); ++itr) {
            long long f = search(*itr, root); // cout << f << endl;
            ans = max(ans, f * (long long)(*itr));
            remove(*itr, root);
        }

        return ans;
    }
};






// passes 755 / 758 test cases as of 8/31/2025, then TLE
// test case 756 runs in about ~2760ms returning correct result, but obviously too slow


class Solution {
private:
    struct Trie {
        struct Trie* children[2];
        long long endOfWord; // our number
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = 0LL;

        tn->children[0] = NULL;
        tn->children[1] = NULL;

        return tn;
    }

    void add(int s, Trie* dic) {
        int org_s = s;

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

        // set endOfWord to our original integer
        tn->endOfWord = org_s;

        return;
    }

    // recursive
    long long search(const int org_s, int s, Trie* dic) {
        long long ret = 0LL;

        struct Trie* tn = dic;

        do {
            if( s & 1 ) {
                // bit in s is set, so we only have one choice
                // to proceed with non-set bit
                if( tn->children[0] )
                    tn = tn->children[0];
                else
                    break;
                // as we go from least significant to most significant
                // bit, no need to check for endOfWord on a non-set bit
            } else {
                // bit in s is NOT set, so we have two choices
                // to proceed: set bit OR unset bit
                if( tn->children[1] ) { // recurse
                    ret = max(ret, (long long)org_s * tn->children[1]->endOfWord);
                    ret = max(ret, search(org_s, s>>1, tn->children[1]));
                }
                if( tn->children[0] )   // continue
                    tn = tn->children[0];
                else
                    break;
            }
            s >>= 1;
        } while (s);

        return ret;
    }

public:
    long long maxProduct(vector<int>& nums) {
        int n = nums.size(); // 2 <= n <- 1e5

        // 1 <= nums[i] <= 1e6
        // decimal 1e6 -> binary 11110100001001000000 20digits

        // what if we create a binary Trie
        // we add every distinct integer in nums into our Trie
        // then we go from largest to smaller through distinct integers
        // in our Trie we navigate always to opposite, and if endOfWord
        // we multiply and keep track of max

        set<int> st;
        for(int i: nums)
            st.insert(i);

        Trie* root = init();
        for(int i: st)
            add(i, root);

        long long ans = 0;
        for(auto itr = st.rbegin(); itr != st.rend(); ++itr)
            ans = max(ans, search(*itr, *itr, root));

        return ans;
    }
};
