
// 2260. Minimum Consecutive Cards to Pick Up
// https://leetcode.com/problems/minimum-consecutive-cards-to-pick-up/



class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        unordered_map<int,int> last_seen;

        int n = cards.size();
        int ans = 100001;

        for(int i = 0; i < n; ++i) {
            int card = cards[i];

            auto p = last_seen.insert({card,i});
            if( !p.second ) {
                ans = min(ans, i - p.first->second + 1);
                p.first->second = i;
            }
        }

        return ans != 100001 ? ans : -1;
    }
};
