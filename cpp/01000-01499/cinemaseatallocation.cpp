
// 1386. Cinema Seat Allocation
// https://leetcode.com/problems/cinema-seat-allocation/





class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        // empty rows yield max 2

        unordered_map<int,int> um; // row,mask
        for(int i = 0; i < reservedSeats.size(); ++i) {
            int row = reservedSeats[i][0];
            int col = reservedSeats[i][1];

            int mask = 0;
            mask |= 1 << (col-1);
            auto p = um.insert({row,mask});
            if( !p.second )
                p.first->second |= 1 << (col-1);

        }

        int ans = (n - um.size())*2; // empty rows

        // 1 <= mask <= 1023 ( = 2^10 - 1 )
        // pre-calcuate the yield for mask
        int yield[1024];
        for(int i = 1; i < 1024; ++i) {
            // seat 1 2 3 4 (0-indexed)
            int a = 0;
            if( !((i >> 1) & 1U) &&
                !((i >> 2) & 1U) &&
                !((i >> 3) & 1U) &&
                !((i >> 4) & 1U) )
                a = 1;

            // seat 5 6 7 8 (0-indexed)
            int b = 0;
            if( !((i >> 5) & 1U) &&
                !((i >> 6) & 1U) &&
                !((i >> 7) & 1U) &&
                !((i >> 8) & 1U) )
                b = 1;

            if( a && b ) {
                yield[i] = 2;
            } else {
                // seat 3 4 5 6 (0-indexed)
                int c = 0;
                if( !((i >> 3) & 1U) &&
                    !((i >> 4) & 1U) &&
                    !((i >> 5) & 1U) &&
                    !((i >> 6) & 1U) )
                    c = 1;

                yield[i] = max({a,b,c});
            }
        }

        for(auto it = um.begin(); it != um.end(); ++it)
            ans += yield[it->second];


        return ans;
    }
};
