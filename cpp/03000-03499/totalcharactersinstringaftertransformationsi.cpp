
// 3335. Total Characters in String After Transformations I
// https://leetcode.com/problems/total-characters-in-string-after-transformations-i/





class Solution {
private:
    const long mod = 1000000007;
public:
    int lengthAfterTransformations(string s, int t) {
        int n = s.size();

        long cnt[26];memset(cnt,0,sizeof cnt);
        for(char c: s)
            ++cnt[c-'a'];

        struct ListNode {
            long val;
            ListNode* prev;
            ListNode* next;
            ListNode(long val) : val(val), prev(nullptr), next(nullptr) {}
        };

        // circular list a ... z

        ListNode * a_node;
        ListNode * prev = nullptr;
        for(int i = 0; i < 26; ++i) {
            ListNode * nd = new ListNode(cnt[i]);
            nd->prev = prev;

            if( prev != nullptr )
                prev->next = nd;

            if( i == 0 )
                a_node = nd;

            prev = nd;
        }
        // prev is ListNode for char z
        prev->next = a_node;
        a_node->prev = prev;


        for(int i = 0; i < t; ++i) {
            a_node = a_node->prev;
            a_node->next->val = (a_node->next->val + a_node->val) % mod;
        }

        long ans = 0L;

        for(int i = 0; i < 26; ++i) {
            ans = (ans + a_node->val) % mod;
            a_node = a_node->next;
        }

        return ans;
    }
};
