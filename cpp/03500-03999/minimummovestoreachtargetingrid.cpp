
// 3609. Minimum Moves to Reach Target in Grid
// https://leetcode.com/problems/minimum-moves-to-reach-target-in-grid/


class Solution {
public:
    int minMoves(int sx, int sy, int tx, int ty) {
        // at any point (x, y), define m = max(x, y).
        // We can either:
        //     Move to (x + m, y), or
        //     Move to (x, y + m).
        // intuition: solve by going backwards from target to source
        //     because only one move to explore
        // example
        // x y             x y    x y
        // 2 5 -> m = 5 -> 7 5 OR 2 10
        // if we would go backward, it means either
        //    if max(x,y) >= 2 x min(x,y), then we can half max(x,y) OTHERWISE
        //    max(x,y) - min(x,y)

        // {steps, x, y}
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            return a[0] > b[0];
        };
        priority_queue<vector<int>,vector<vector<int>>,decltype(cmp)> pq(cmp);
        map<vector<int>, int> A; // key: {x,y} value: steps

        pq.push({0,tx,ty});
        A.insert({{tx,ty},0});
        A.insert({{-1,-1},0});

        while( !pq.empty() ) {
            int steps = pq.top()[0];
            int x = pq.top()[1];
            int y = pq.top()[2];
            pq.pop();

            if( x == sx && y == sy )
                return steps;

            if( x < sx || y < sy )
                continue;

            int x_new = -1;
            int y_new = -1;
            if( x != y ) {
                if( x > y ) {
                    if( x >= 2*y ) {
                        x_new = x % 2 == 0 ? x / 2 : -1;
                        y_new = x_new != -1 ? y : -1;
                    } else {
                        x_new = x - y;
                        y_new = y;
                    }

                } else { // y > x
                    if( y >= 2*x ) {
                        y_new = y % 2 == 0 ? y / 2 : -1;
                        x_new = y_new != -1 ? x : -1;
                    } else {
                        y_new = y - x;
                        x_new = x;
                    }
                }

                auto f = A.find({x_new, y_new});
                if( f != A.end() ) {
                    if( f->second > steps + 1 ) {
                        f->second = steps + 1;
                        pq.push({steps+1, x_new, y_new});
                    }

                } else {
                    A.insert({{x_new, y_new}, steps + 1});
                    pq.push({steps+1, x_new, y_new});
                }

            } else { // x == y
                x_new = 0;
                y_new = y;
                auto f = A.find({x_new, y_new});
                if( f != A.end() ) {
                    if( f->second > steps + 1 ) {
                        f->second = steps + 1;
                        pq.push({steps+1, x_new, y_new});
                    }
                } else {
                    A.insert({{x_new, y_new}, steps + 1});
                    pq.push({steps+1, x_new, y_new});
                }

                x_new = x;
                y_new = 0;
                f = A.find({x_new, y_new});
                if( f != A.end() ) {
                    if( f->second > steps + 1 ) {
                        f->second = steps + 1;
                        pq.push({steps+1, x_new, y_new});
                    }
                } else {
                    A.insert({{x_new, y_new}, steps + 1});
                    pq.push({steps+1, x_new, y_new});
                }
            }

        }

        return -1;
    }
};
