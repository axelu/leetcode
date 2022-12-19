
// 1659. Maximize Grid Happiness
// https://leetcode.com/problems/maximize-grid-happiness/



/*   0 1 2 3 4 5
 * 0 t t X X X X
 * 1 X X o o o o
 * 2 o o o o o o
 * 3 o o o o o o
 * 4 o o o o o o
 * lets assume we are in row 1 col 2 (0-indexed)
 * what we need to know is the cells marked with X state
 * because what we put in [1,2] will influence our result
 * we will call the array of Xs prev_row (sliding)
 */
class Solution {
private:
    int m,n;

    void printBinary(int x) {
        for(int i = 2*n-1; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
    }

    unordered_map<int,int> mem;

    int rec(int i, int j, int introverts, int extroverts, long prev_row) {
        // cout << "i " << i << " j " << j;
        // cout << " introverts " << introverts << " extroverts " << extroverts;
        // cout << " prev_row ";printBinary(prev_row);cout << endl;

        if( i == m || (introverts == 0 && extroverts == 0) )
            return 0;

        int key = prev_row & 1023; // right most 10 bits (5 cols max, 2 bits per column => 10 bits)
        key += i<<10;
        key += j<<13;
        key += extroverts<<16;
        key += introverts<<19;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        // at each cell we have a choice
        //     leave empty
        //     place an introvert (if we have one or more left)
        //     place an extrovert (if we have one or more left)

        // we are traversing each row left to right, then the next row
        // the cell above is is prev_row[0], the cell to our right is prev_row[last]

        int prev_row_0    = (prev_row>>((n-1)*2)) & 3;
        int prev_row_last = prev_row & 3;
        long prev_row_new = prev_row << 2;

        int i_new,j_new;
        if( j < n-1 ) {
            i_new = i; j_new = j+1;
        } else {
            i_new = i+1; j_new = 0;
        }

        int ret = rec(i_new,j_new,introverts,extroverts,prev_row_new);

        if( introverts > 0 ) {
            int t = 120;
            if( prev_row_0 != 0 ) { // neighbor on top of us
                // our introvert looses 30 happiness points for the neighbor on top of us
                t -= 30;
                if( prev_row_0 == 1 ) // introvert
                    t -= 30;
                else                  // extrovert
                    t += 20;
            }
            if( j > 0 && prev_row_last != 0 ) { // neighbor to the left of us
                // our introvert looses 30 happiness points for the neighbor to our left
                t -= 30;
                if( prev_row_last == 1 ) // introvert
                    t -= 30;
                else                     // extrovert
                    t += 20;
            }
            ret = max(ret, t + rec(i_new,j_new,introverts-1,extroverts,prev_row_new+1));
        }
        if( extroverts > 0 ) {
            int t = 40;
            if( prev_row_0 != 0 ) { // neighbor on top of us
                // our extrovert gains 20 happiness points for the neighbor on top of us
                t += 20;
                if( prev_row_0 == 1 )   // introvert
                    t -= 30;
                else                    // extrovert
                    t += 20;
            }
            if( j > 0 && prev_row_last != 0 ) { // neighbor to the left of us
                // our extrovert gains 20 happiness points for the neighbor to our left
                t += 20;
                if( prev_row_last == 1 ) // introvert
                    t -= 30;
                else                     // extrovert
                    t += 20;
            }
            ret = max(ret, t + rec(i_new,j_new,introverts,extroverts-1,prev_row_new+2));
        }

        //cout << "i " << i << " j " << j << " introverts " << introverts << " extroverts " << extroverts;
        //cout << " prev_row ";printBinary(prev_row);cout << " ret " << ret << endl;
        return mem[key] = ret;
    }

public:
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
        this->n = n;
        this->m = m;

        // prev_row
        // right most 2 bits are neighbor to the left
        // left most 2 bits are neighbor to the top
        // 0 empty, 1 introvert, 2 extrovert
        return rec(0,0,introvertsCount,extrovertsCount,0);
    }
};
