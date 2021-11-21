
// 1739. Building Boxes
// https://leetcode.com/problems/building-boxes/




class Solution {
public:
    int minimumBoxes(int n) {
        // 1 <= n <= 10^9
        if( n <= 3 )
            return n;

        // 1816 full levels -> 1649836 boxes on floor -> store  999800616 boxes total
        // 1817 full levels -> 1651653 boxes on floor -> store 1001452269 boxes total
        // full level number == number of boxes on side of floor
        int k = 1817;
        int floorcount = 0;
        int prefloorcount = 0, pretotal = 0;
        int total = 0;
        int i = 1;
        for(; i <= k; ++i) {
            floorcount += i;
            total += floorcount;
            // cout << i << " " << floorcount << " " << total << endl;
            // cout << total - pretotal << endl;
            if( total >= n )
                break;
            prefloorcount = floorcount;
            pretotal = total;
        }
        if( total == n )
            return floorcount;

        // prefloorcount < answer <= floorcount
        // cout << "flourcount "<< prefloorcount << " " << floorcount << endl;
        // cout << "total      "<< pretotal << " " << total << endl;
        // cout << 1001452269-999800616 << endl;
        // cout << 1000000000-999800616 << endl;

        // max diff total-pretotal at n = 1000000000 -> 1651653
        for(int j = 0; j < 1651654; ++j) {
            ++prefloorcount;
            pretotal += 1 + j;
            if( pretotal >= n )
                break;
        }

        return prefloorcount;
    }
};
