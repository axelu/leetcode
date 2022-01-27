
// 765. Couples Holding Hands
// https://leetcode.com/problems/couples-holding-hands/

class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int n2 = row.size(); // n couples in 2xn seats
        int n  = n2/2;

        unordered_map<int,int> um; // ID,seat
        for(int i = 0; i < n2; ++i)
            um.insert({row[i],i});


        int ans = 0;

        // good row
        // 0 1 2 3 4 5 6 7 ...
        // also good
        // 1 0 3 2 5 4 7 6

        // we will root the person in every other seat
        int partner,seat;
        for(int i = 0; i < n2; i += 2) {
            // who is my partner?
            // if nums[i] is even, my partner is nums[i]+1
            // if nums[i] is odd, my parter is nums[i]-1
            partner = row[i] % 2 == 0 ? row[i]+1 : row[i]-1;

            // is my partner in the seat next to me?
            if( row[i+1] == partner )
                continue;

            // what seat is my partner in?
            // seat = um.find(partner)->second;
            seat = um[partner];

            // swap
            // put the person next to me where my partner currently sits
            row[seat] = row[i+1];
            um[row[i+1]] = seat;

            // optional
            // put my partner next to me
            // row[i+1] = partner;
            // um[partner] = i+1;

            ++ans;
        }

        return ans;
    }
};
