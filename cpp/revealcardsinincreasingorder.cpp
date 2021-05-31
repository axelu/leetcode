
// 950. Reveal Cards In Increasing Order
// https://leetcode.com/problems/reveal-cards-in-increasing-order/



// from the solution approach #1 simulation
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        int n = deck.size();
        queue<int> q; // queue of indexes
        int i;
        for(i = 0; i < n; ++i)
            q.push(i);

        sort(deck.begin(),deck.end());
        vector<int> ans(n);
        int t;
        for(i = 0; i < n; ++i) {
            ans[q.front()] = deck[i];
            q.pop();
            if( !q.empty() ) {
                t = q.front();
                q.pop();
                q.push(t);
            }
        }

        return ans;
    }
};
