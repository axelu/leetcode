
// 3279. Maximum Total Area Occupied by Pistons
// https://leetcode.com/problems/maximum-total-area-occupied-by-pistons/



class Solution {
public:
    long long maxArea(int height, vector<int>& positions, string directions) {

        // pistons at [max] height in up queue
        //   we pull them out of up queue and reduce up queue val by height * number of pistons at height
        //                                and reduce up queue number of pistons
        //   we push them into down queue and increase down queue val by (height-1) * number of pistons at height
        //   so our down queue should at any point be height long
        //   and our up queue should at any point be height
        // pistons at 0 in down queue
        //   we pull them out of down queue and reduce up queue number of pistons
        //   we push them into up queue and at position 1 and increase up queue value by number pistons and
        //                              and add that number of pistons

        // at each second the value of the queue changes by the number of pistons in it

        // up queue
        // front -> 1 2 3 ... height   -> back

        // down queue
        // front -> height-1 ... 2 1 0 -> back

        long long up_queue_val = 0LL;
        long long up_queue_nbr_pistons = 0LL;

        long long down_queue_val = 0LL;
        long long down_queue_nbr_pistons = 0LL;

        vector<long long> up(height+1);
        vector<long long> down(height+1);

        int nbr_pistons = positions.size(); // positions.size() == directions.size()
        for(int i = 0; i < nbr_pistons; ++i) {
            if( positions[i] == 0 ) {
                ++down[0];
                ++down_queue_nbr_pistons;

            } else if( positions[i] == height ) {
                ++up[height];
                ++up_queue_nbr_pistons;
                up_queue_val += height;

            } else {
                if( directions[i] == 'U' ) {
                    ++up[positions[i]];
                    ++up_queue_nbr_pistons;
                    up_queue_val += positions[i];

                } else {
                    ++down[positions[i]];
                    ++down_queue_nbr_pistons;
                    down_queue_val += positions[i];
                }
            }
        }

        long long area = up_queue_val + down_queue_val;
        // cout << "initial area at second 0 " << area << endl;

        queue<long long> upq;
        for(int i = height; i > 0; --i)
            upq.push(up[i]);

        queue<long long> downq;
        for(int i = 0; i < height; ++i)
            downq.push(down[i]);


        // run
        for(int i = 0; i <= height*2; ++i) {

            // remove pistons from up queue at height height
            long long nbr_pistons_at_height = upq.front();
            upq.pop();
            up_queue_val -= height * nbr_pistons_at_height;
            up_queue_nbr_pistons -= nbr_pistons_at_height;
            // the remaining pistons all move one up
            up_queue_val += up_queue_nbr_pistons;

            // remove pistons from down queue at height 0
            long long nbr_pistons_at_zero = downq.front();
            downq.pop();
            // down_queue_val -= 0 * nbr_pistons_at_zero;
            down_queue_nbr_pistons -= nbr_pistons_at_zero;
            // the remaining pistons all move one down
            down_queue_val -= down_queue_nbr_pistons;


            // add the pistons we removed from the up queue to down queue at height height-1
            downq.push(nbr_pistons_at_height);
            down_queue_val += (height-1) * nbr_pistons_at_height;
            down_queue_nbr_pistons += nbr_pistons_at_height;

            // add pistons we removed from the down queue to the up queue at height 1
            upq.push(nbr_pistons_at_zero);
            up_queue_val += 1 * nbr_pistons_at_zero;
            up_queue_nbr_pistons += nbr_pistons_at_zero;

            // new area
            area = max(area, up_queue_val + down_queue_val);

            /*
            cout << "end of " << i << " seconds" << endl;
            cout << " up_queue_nbr_pistons " << up_queue_nbr_pistons << " down_queue_nbr_pistons " << down_queue_nbr_pistons << " total pistons " << up_queue_nbr_pistons + down_queue_nbr_pistons << endl;
            cout << " up_queue_val " << up_queue_val << " down_queue_val " << down_queue_val << " total val " << up_queue_val + down_queue_val << endl;
            */
        }

        return area;
    }
};
