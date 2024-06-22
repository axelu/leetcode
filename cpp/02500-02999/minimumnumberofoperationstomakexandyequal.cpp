
// 2998. Minimum Number of Operations to Make X and Y Equal
// https://leetcode.com/problems/minimum-number-of-operations-to-make-x-and-y-equal/





class Solution {
public:
    int minimumOperationsToMakeEqual(int x, int y) {
        if( x <= y ) // only operation to make x bigger it to increment x by 1
            return y - x;

        auto cmp = [](const array<int,2>& a, const array<int,2>& b){
            return a[1] > b[1];
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);
        pq.push({x,0});
        bool seen[20000];memset(seen,false,sizeof seen);
        seen[x] = true;
        while(true) {
            int curr_x = pq.top()[0];
            int steps = pq.top()[1];
            pq.pop();
            // cout << "curr_x " << curr_x << " steps " << steps << endl;

            if( curr_x == y )
                return steps;

            if( curr_x % 5 == 0 && !seen[curr_x / 5] ) {
                pq.push({curr_x / 5, steps + 1});
                seen[curr_x / 5] = true;
            }
            if( curr_x % 11 == 0 && !seen[curr_x / 11] ) {
                pq.push({curr_x / 11, steps + 1});
                seen[curr_x / 11] = true;
            }

            if( curr_x - 1 > 0 && !seen[curr_x - 1]) {
                pq.push({curr_x - 1, steps + 1});
                seen[curr_x - 1] = true;
            }
            if( steps + 1 < 10000 && !seen[curr_x + 1] ) {
                pq.push({curr_x + 1, steps + 1});
                seen[curr_x + 1] = true;
            }
        }

        return -1;
    }
};
