
// 2073. Time Needed to Buy Tickets
// https://leetcode.com/problems/time-needed-to-buy-tickets/



class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int n = tickets.size();
        
        int i = 0, ans = 0;
        while(true) {
            if( tickets[i] > 0 ) {
                --tickets[i];
                ++ans;
            }
            if( i == k && tickets[i] == 0 )
                break;
            ++i;
            if( i == n )
                i = 0;
        }
        
        return ans;
    }
};
