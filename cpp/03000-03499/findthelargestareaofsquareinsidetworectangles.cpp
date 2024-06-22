
// 3047. Find the Largest Area of Square Inside Two Rectangles
// https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/







class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        int n = bottomLeft.size(); // n == bottomLeft.length == topRight.length

        unordered_map<int,vector<pair<int,int>>> x_starts;  // x, {{short side, index}, ...}
        unordered_map<int,vector<int>> x_ends;              // x, {index, ...}
        set<int> xs;
        for(int i = 0; i < n; ++i) {
            int x_lo = bottomLeft[i][0];
            int y_lo = bottomLeft[i][1];

            int x_hi = topRight[i][0];
            int y_hi = topRight[i][1];

            int short_side = min(x_hi - x_lo, y_hi - y_lo);

            xs.insert(x_lo);
            x_starts[x_lo].push_back({short_side, i});

            xs.insert(x_hi);
            x_ends[x_hi].push_back(i);
        }

        int l_mx = 0;

        unordered_set<int> in_play;
        for(int x: xs) {
            // cout << "current x " << x << endl;

            // remove all rectangles from in_play that end at current x
            auto f_ends = x_ends.find(x);
            if( f_ends != x_ends.end() ) {
                for(int i: f_ends->second) {
                    // cout << "  removing from in_play " << i << endl;
                    in_play.erase(i);
                }
            }

            // remove all rectangles from in_play that can no longer beat the best result
            for(auto it = in_play.begin(); it != in_play.end(); ) {
                int i = *it;
                int x_lo = bottomLeft[i][0];
                int y_lo = bottomLeft[i][1];

                int x_hi = topRight[i][0];
                int y_hi = topRight[i][1];

                int short_side = min(x_hi - x_lo, y_hi - y_lo);

                if( short_side <= l_mx ) {
                    it = in_play.erase(it);
                    continue;
                }

                ++it;
            }

            auto f = x_starts.find(x);

            // sort everything that starts by largest short side
            if( f != x_starts.end() && f->second.size() > 1 ) {
                sort(f->second.begin(), f->second.end(), [](const pair<int,int>& a, pair<int,int> b){
                   return a.first > b.first;
                });
            }

            // process everything in play against everything that starts
            if( !in_play.empty() && f != x_starts.end() ) {

                for(auto in_play_it = in_play.begin(); in_play_it != in_play.end(); ) {

                    int in_play_idx = *in_play_it;
                    // cout << "  processing in_pay " << in_play_idx << endl;

                    int a_x_hi = topRight[in_play_idx][0];
                    if( a_x_hi - x <= l_mx ) {
                        in_play_it = in_play.erase(in_play_it);
                        continue;
                    }

                    int a_y_lo = bottomLeft[in_play_idx][1];
                    int a_y_hi = topRight[in_play_idx][1];
                    if( a_y_hi - a_y_lo <= l_mx ) {
                        in_play_it = in_play.erase(in_play_it);
                        continue;
                    }

                    for(auto& p: f->second) {

                        int short_side = p.first;
                        if( short_side <= l_mx )
                            continue;

                        int start_idx = p.second;

                        int b_x_hi = topRight[start_idx][0];
                        int x_hi = min(a_x_hi, b_x_hi);
                        if( x_hi - x <= l_mx )
                            continue;

                        int b_y_lo = bottomLeft[start_idx][1];
                        int b_y_hi = topRight[start_idx][1];
                        if( a_y_hi <= b_y_lo || b_y_hi <= a_y_lo )
                            continue;

                        int y_lo = max(a_y_lo, b_y_lo);
                        int y_hi = min(a_y_hi, b_y_hi);

                        if( y_hi - y_lo <= l_mx )
                            continue;

                        l_mx = min(x_hi - x, y_hi - y_lo);
                    }

                    ++in_play_it;
                }
            }

            // process everything that starts against everything that starts
            if( f != x_starts.end() && f->second.size() > 1 ) {
                for(auto ito = f->second.begin(); next(ito) != f->second.end(); ++ito) {

                    int short_side = ito->first;
                    if( short_side <= l_mx )
                        continue;

                    int a_idx = ito->second;
                    int a_x_hi = topRight[a_idx][0];
                    if( a_x_hi - x <= l_mx )
                        continue;

                    int a_y_lo = bottomLeft[a_idx][1];
                    int a_y_hi = topRight[a_idx][1];


                    for(auto iti = next(ito); iti != f->second.end(); ++iti) {

                        short_side = iti->first;
                        if( short_side <= l_mx )
                            continue;

                        int b_idx = iti->second;
                        int b_x_hi = topRight[b_idx][0];
                        int x_hi = min(a_x_hi, b_x_hi);
                        if( x_hi - x <= l_mx )
                            continue;

                        int b_y_lo = bottomLeft[b_idx][1];
                        int b_y_hi = topRight[b_idx][1];
                        if( a_y_hi <= b_y_lo || b_y_hi <= a_y_lo )
                            continue;

                        int y_lo = max(a_y_lo, b_y_lo);
                        int y_hi = min(a_y_hi, b_y_hi);

                        if( y_hi - y_lo <= l_mx )
                            continue;

                        l_mx = min(x_hi - x, y_hi - y_lo);
                    }
                }
            }

            // add all the start at x to in_play
            if( f != x_starts.end() ) {
                for(auto& p: f->second) {
                        int short_side = p.first;
                        if( short_side <= l_mx )
                            continue;

                        int start_idx = p.second;
                        in_play.insert(start_idx);
                }
            }
        }

        return (long long)l_mx * (long long)l_mx;
    }
};
