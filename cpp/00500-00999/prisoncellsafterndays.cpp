
// 957. Prison Cells After N Days
// https://leetcode.com/problems/prison-cells-after-n-days/





/* eventually the pattern will repeat
 * we have 256 possibilities
 * if the initial pattern has a 1 at position 0 and/or 7 (0-indexed)
 * then the initial pattern will NOT repeat, but pattern day 1 will repeat
 *
 */
class Solution {
private:
    void printBinary(int x) {
        for(int i = 7; i >= 0; --i) {
            if( x & (1 << i) )
                cout << 1 << " ";
            else
                cout << 0 << " ";
        }
        cout << endl;
    }

    int vector2int(vector<int>& cells) {
        int ret = 0;
        for(int i = 0; i < 8; ++i)
            if( cells[i] == 1 )
                ret |= 1 << (7-i);

        return ret;
    }

    vector<int> int2vector(int cells) {
        vector<int> ret(8,0);
        for(int i = 1; i < 7; ++i)
            if( (cells >> i) & 1 )
                ret[7-i] = 1;
        return ret;
    }

public:
    vector<int> prisonAfterNDays(vector<int>& cells, int n) {
        // cells.size() == 8

        // cells to int
        int cells_int_org = vector2int(cells);
        // debug
        // cout << "Day 0: ";printBinary(cells_int_org);

        int cells_int = cells_int_org;

        // deal with end cells
        int offset = 0;
        if( cells[0] == 1 || cells[7] == 1 ) {
            offset = 1;
            // do the 1st day
            int cells_int_new = 0;
            for(int k = 1; k < 7; ++k) {
                int pre = (cells_int >> (8-k)) & 1;
                int nxt = (cells_int >> (6-k)) & 1;
                if( pre == nxt )
                    cells_int_new |= 1 << (7-k);
            }
            cells_int = cells_int_new;
            // debug
            // cout << "Day 1: ";printBinary(cells_int);
            cells_int_org = cells_int;

            if( n == 1 )
                return int2vector(cells_int);
        }

        int prison[256];
        prison[0] = cells_int_org;

        int i = 1;
        for(; i < 256; ++i) {
            int cells_int_new = 0;
            for(int k = 1; k < 7; ++k) {
                int pre = (cells_int >> (8-k)) & 1;
                int nxt = (cells_int >> (6-k)) & 1;
                // cout << "k " << k << " pre " << pre << " nxt " << nxt << endl;
                if( pre == nxt )
                    cells_int_new |= 1 << (7-k);
            }
            cells_int = cells_int_new;
            // debug
            // cout << "Day " << i + offset << ": ";printBinary(cells_int);

            if( i + offset == n )
                return int2vector(cells_int);

            if( cells_int == cells_int_org )
                break;
            prison[i] = cells_int;
        }

        // on ith day the original pattern is back
        // -> hence divisor is i;

        int day = (n % i) - offset;
        if( day == -1 )
            day = i-1;
        return int2vector(prison[day]);
    }
};
