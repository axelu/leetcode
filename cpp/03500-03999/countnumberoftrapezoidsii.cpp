
// 3625. Count Number of Trapezoids II
// https://leetcode.com/problems/count-number-of-trapezoids-ii/









// resources
// https://en.wikipedia.org/wiki/Trapezoid
// https://www.geeksforgeeks.org/maths/what-is-parallel-lines-formula/
// https://leetcode.com/problems/count-number-of-trapezoids-i/
// https://www.geeksforgeeks.org/dsa/count-parallelograms-plane/


class Solution {
private:


    // see 3623. Count Number of Trapezoids I
    // https://leetcode.com/problems/count-number-of-trapezoids-i/
    int count(map<double, int>& h) {

        int h_sz = h.size();
        if( h_sz < 2 )
            return 0;
        // cout << "h_sz " << h_sz << endl;

        vector<long> suffixSum(h_sz);
        suffixSum[h_sz-1] = 0L;
        auto itr = h.rbegin();
        for(int i = h_sz-2; i >= 0; --i) {
            // long pairs = (itr->second * (itr->second - 1)/2L) % mod;
            long pairs = itr->second;
            // suffixSum[i] = (suffixSum[i+1] + pairs) % mod;
            suffixSum[i] = suffixSum[i+1] + pairs;
            ++itr;
        }

        long ans = 0L;
        auto it = h.begin();
        for(int i = 0; i < h_sz-1; ++i) {
            // long pairs = (it->second * (it->second - 1L)/2L) % mod;
            long pairs = it->second;
            // ans = (ans + ((pairs * suffixSum[i]) % mod)) % mod;
            ans = ans + (pairs * suffixSum[i]);

            ++it;
        }

        return ans; // ans will not exceed INT_MAX
    }



    bool is_collinear(int px, int py, int qx, int qy, int rx, int ry) {
        // crossproduct to determine if 3 points are on the same line
        // if the crossproduct is 0, then they are on the same line
        //              --------------------------------------- - ---------------------------------------
        long long res = (long long)(qy-py) * (long long)(rx-qx) - (long long)(qx-px) * (long long)(ry-qy);
        return res == 0LL;
    }

    int countParallelograms(vector<vector<int>>& points) {
        int n = points.size();
        // points are sorted

        /* inspired by https://www.geeksforgeeks.org/dsa/count-parallelograms-plane/
           This delivers wrong result when points are on a line!!!
            example: [[83,-25],[-65,-25],[17,-25],[1,-25]]
            between pair 0 1 -> mid_x = 18 mid_y = -50
            between pair 2 3 -> mid_x = 18 mid_y = -50
            so we get two counts of mid_x = 18 mix_y = -50, but because the
            points are colinear, this is not correct
            hence we are using set on slope
            also consider this example:
            [[0,0],[0,4],[1,1],[1,3],[3,1],[3,3],[4,0],[4,4]]
            correct answer is 4, but the solution from GfG returns 6 as again,
            it counts the two crossing lines that have 4 points on it of which
            2 points pairs have the same midpoint
         */


        vector<vector<int>> point_pairs(n * (n-1)/2,vector<int>(2));
        map<pair<int,int>, vector<int>> midpoints; // list of point pair ids by midpoint

        int point_pair_idx = 0;
        for(int i = 0; i < n-1; ++i) {
            int xi = points[i][0];
            int yi = points[i][1];
            for(int j = i+1; j < n; ++j) {
                point_pairs[point_pair_idx][0] = i;
                point_pairs[point_pair_idx][1] = j;

                int xj = points[j][0];
                int yj = points[j][1];

                int mid_x = xi + xj;
                int mid_y = yi + yj;
                // cout << "i " << i << " j " << j << " mid_x " << mid_x << " mid_y " << mid_y << endl;

                midpoints[make_pair(mid_x,mid_y)].push_back(point_pair_idx);
                ++point_pair_idx;
            }
        }

        int cnt = 0;
        for (auto it = midpoints.begin(); it != midpoints.end(); ++it) {
            int point_pair_sz = it->second.size();
            if( point_pair_sz < 2 )
                continue;

            for(int i = 0; i < point_pair_sz-1; ++i) {
                // it->second[i] is point_pair_idx
                int point_1 = point_pairs[it->second[i]][0];
                int x1 = points[point_1][0];
                int y1 = points[point_1][1];
                int point_2 = point_pairs[it->second[i]][1];
                int x2 = points[point_2][0];
                int y2 = points[point_2][1];

                for(int j = i+1; j < point_pair_sz; ++j) {
                    int point_3 = point_pairs[it->second[j]][0];
                    int x3 = points[point_3][0];
                    int y3 = points[point_3][1];
                    // int point_4 = point_pairs[it->second[j]][1];
                    // int x4 = points[point_4][0];
                    // int y4 = points[point_4][1];

                    // if the 4 points are on the same line, they
                    // do NOT form a parallelogram, even though they
                    // have the same midpoint

                    // we only need to check 3 out of the 4 points
                    if( !is_collinear(x1, y1, x2, y2, x3, y3) )
                        ++cnt;
                }
            }
        }

        // cout << "parallelogram cnt " << cnt << endl;
        return cnt;
    }

public:
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size(); // 4 <= n <= 500;

        /*
            fix a point A
            take a next point B
            calculate the line A-B
            find all other points AB1, AB2, ... that are on the line A-B
            loop through all points != A and != B and != AB1, AB2, ...
                fix a point C
                take a next point D
                calculate the line C-D
                determine if line C-D is parallel to line A-B
                if not, continue
                if parallel then find all other points CD1, CD2, ... that are on the line C-D
                calc number of trapezoids that can be formed and add to response

            somehow keep track of the point on lines processed, so we don't double count
            https://en.wikipedia.org/wiki/Trapezoid
            we would double count Parallelograms incl. Parallelograms itself, Rhombuses, Squares and Rectangles,
            whereas Rhombuses, Squares and Rectangles are specialized Parallelograms

            lets say we have 250 points on one line an 250 points on a paralel line
            then we can make  (250 * (250-1)/2) * (250 * (250-1)/2) = 968765625 trapezoids

            let [a,b] and [c,d] be two points
            Slope = (b - d) / (a - c)
        */

        // sort points
        sort(points.begin(), points.end());
        /*
        for(auto& point: points)
            cout << point[0] << "," << point[1] << " ";
        cout << endl;
        */

        int parallelograms = countParallelograms(points);

        vector<vector<int>> point_pairs(n * (n-1)/2,vector<int>(2));
        map<double, vector<int>> mp; // key: slope, value: list of point pair ids

        int point_pair_idx = 0;
        for(int i = 0; i < n-1; ++i) {
            int xi = points[i][0];
            int yi = points[i][1];
            for(int j = i+1; j < n; ++j) {
                point_pairs[point_pair_idx][0] = i;
                point_pairs[point_pair_idx][1] = j;

                int xj = points[j][0];
                int yj = points[j][1];

                double slope = (yj - yi) / (double)(xj - xi); // TODO limit the precision
                // cout << "i " << i << " j " << j << " slope " << slope << endl;
                mp[slope].push_back(point_pair_idx);

                ++point_pair_idx;
            }
        }

        int ans = 0;

        // below will doublecount parallelograms !!!
        // hence subtract parallelograms from the result

        for(auto it = mp.begin(); it != mp.end(); ++it) {
            // for there to be two parallel lines, we need at least 2 point pairs
            if( it->second.size() < 2 )
                continue;

            double slope = it->first;

            // horizontal lines slope == 0
            bool is_horizontal = slope == (double)0.0;
            // vertical lines   slope == inf
            bool is_vertical = isinf(slope);
            // cout << "slope " << slope << " is_vertical " << is_vertical << " " << " is_horizontal " << is_horizontal << endl;
            // cout << "slope " << slope << " is_vertical " << is_vertical << endl;

            // we need to figure out how many parallel lines we have and
            // how many points on each line aka collinear (min 2 points aka 1 point pair, and
            // because we are working in point pairs, we know that is guaranteed already)
            // a line can be expressed as y = slope * x + B
            // where B is the intersect with the y axis at x = 0
            // we could use B to index the non-vertical lines
            // Note: for vertical lines, we cannot use B
            // Note: for horizontal lines, B == y

            map<double, int> h; // key: B value: set of points on line with intersect B

            for(auto iti = it->second.begin(); iti != it->second.end(); ++iti) {
                // cout << *iti << " "; // *iti is point_pair_idx
                // cout << point_pairs[*iti][0] << "," << point_pairs[*iti][1] << " ";

                int i = point_pairs[*iti][0];
                int xi = points[i][0];
                int yi = points[i][1];

                int j = point_pairs[*iti][1];
                int xj = points[j][0];
                int yj = points[j][1];

                double B; // TODO restrict precision for floating point compare
                if( is_horizontal ) {
                    B = (double)yi; // == yj
                } else if( is_vertical ) {
                    // we will use x to index
                    B = (double)xi; // ==xj
                } else { // !is_horzontal && !is_vertical
                    // y = (slope * x) + B  transforms to
                    // B = y - (slope * x)
                    // we know slope is not 0, as that would be a horizontal line,
                    // which we handled above, but xi or xj could be 0, but not both,
                    // because if both, that would be a vertical line,
                    // which we already handled
                    B = yi - (slope * (double)xi);
                    // B = yj - (slope * (double)xj);
                }

                // cout << "[" << xi << "," << yi << "],[" << xj << "," << yj << "] B " << B << " ";


                // h[B].insert(i);
                // h[B].insert(j);

                // don't just insert, as precision is to fine and will create different 'line'
                // even though points are on the same line
                // ++h[B];

                // this is slow, maybe better to make our own implementation with binary search
                if( h.empty() ) {
                    ++h[B];
                } else {
                    // floating point compare
                    bool f = false;
                    for(auto& p: h) {
                        if( abs(p.first - B) <= 1e-4 ) { // why 1e-4 ? and not 1e-5 or different: trial and error
                            p.second++;
                            f = true;
                            break;
                        }
                    }
                    if( !f )
                        ++h[B];
                }

            }
            // cout << endl;

            // calculate number of Trapezoids
            int t = count(h);
            // cout << "number of Trapezoids " << t << endl;
            ans = ans + t;
        }

        // cout << "parallelograms " << parallelograms << endl;
        // cout << "ans before subtracting parallelograms " << ans << endl;

        return ans - parallelograms;
    }
};





/* test cases


[[-3,2],[3,0],[2,3],[3,2],[2,-3]]
[[0,0],[1,0],[0,1],[2,1]]
[[0,1],[0,2],[0,3],[2,2],[2,3],[2,4]]
[[83,-25],[74,11],[-65,-25],[33,-25],[17,-25],[1,30],[-84,-25],[1,-25],[1,-92],[-87,13]]
[[92,100],[-4,55],[92,-87],[92,-91],[92,-30],[27,45],[66,82],[92,79],[92,-89],[-4,95],[92,-70],[-10,-18]]
[[209,-385],[-35,319],[379,-93],[452,10],[179,163],[-118,196],[430,-365],[179,-365],[-299,465],[209,-410],[-375,-403],[-163,-227],[77,-365],[268,441],[460,465],[-163,465],[-412,-267],[-412,53],[-46,-280],[61,-209],[-234,32],[-35,296],[-276,-93],[-412,-475],[-470,-181],[-412,-283],[367,175],[-371,218],[209,-79],[-226,-74],[-435,-410],[-80,10],[-433,-365],[-35,-93],[-470,-67],[-378,0],[-82,-331],[144,268],[449,-106],[-470,-28],[452,-370],[449,-204],[-96,-245],[195,465],[-353,422],[-265,-2],[-178,219],[-35,222],[-375,-411],[-118,-93],[-199,71],[49,-209],[-301,-276],[79,219],[-46,32],[-35,181],[435,402],[449,465],[321,-209],[-412,148],[187,465],[367,496],[16,101],[179,244],[-346,151],[-353,319],[-251,-106],[-35,119],[-118,-370],[-102,465],[-35,311],[452,-62],[-118,441],[-412,-259],[375,441],[483,-182],[-35,-471],[462,289],[179,465],[-412,344],[206,302],[449,417],[-25,500],[-118,43],[372,-93],[180,167],[-118,473],[106,144],[151,-370],[-375,-245],[77,-399],[-478,465],[-405,-478],[-25,-291],[359,-347],[-371,-410],[179,250],[-353,206],[414,-494],[-118,-245],[-199,465],[28,-127],[435,175],[187,-436],[209,-250],[-35,-28],[-35,219],[-257,-93],[-25,-24],[-35,-236]]

[[-118,-93],[-199,71],[49,-209],[-301,-276],[79,219],[-46,32],[-35,181],[435,402],[449,465],[321,-209],[-412,148],[187,465],[367,496],[16,101],[179,244],[-346,151],[-353,319],[-251,-106],[-35,119],[-118,-370],[-102,465],[-35,311],[452,-62],[-118,441],[-412,-259],[375,441],[483,-182],[-35,-471],[462,289],[179,465],[-412,344],[206,302],[449,417],[-25,500],[-118,43],[372,-93],[180,167],[-118,473],[106,144],[151,-370],[-375,-245],[77,-399],[-478,465],[-405,-478],[-25,-291],[359,-347],[-371,-410],[179,250],[-353,206],[414,-494],[-118,-245],[-199,465],[28,-127],[435,175],[187,-436],[209,-250],[-35,-28],[-35,219],[-257,-93],[-25,-24],[-35,-236]]


[[49,-209],[-46,32],[-35,181],[435,402],[449,465],[321,-209],[-412,148],[187,465],[367,496],[16,101],[179,244],[-346,151],[-353,319],[-251,-106],[-35,119],[-118,-370],[-102,465],[-35,311],[452,-62],[-118,441],[-412,-259],[375,441],[483,-182],[-35,-471],[462,289],[179,465],[-412,344],[206,302],[449,417],[-25,500],[-118,43],[372,-93],[180,167],[-118,473],[106,144],[151,-370],[-375,-245],[77,-399],[-478,465],[-405,-478],[-25,-291],[28,-127]]

[[49,-209],[-46,32],[-35,181],[435,402],[449,465],[321,-209],[-412,148],[187,465],[367,496],[16,101],[179,244],[-346,151],[-353,319],[-251,-106],[-35,119],[-118,-370],[-102,465],[-35,311],[452,-62],[-118,441],[-412,-259],[375,441],[483,-182],[-35,-471],[462,289],[179,465],[28,-127]]


[[49,-209],[-46,32],[-35,181],[435,402],[449,465],[321,-209],[-412,148],[187,465],[367,496],[16,101],[179,244],[-346,151],[-353,319],[-251,-106],[-35,119],[-118,-370],[-102,465],[-35,311],[452,-62],[28,-127]]

[[49,-209],[-46,32],[-35,181],[435,402],[449,465],[321,-209],[-35,119],[28,-127]]
[[49,-209],[-35,181],[435,402],[449,465],[321,-209],[-35,119],[28,-127]]
[[49,-209],[435,402],[449,465],[321,-209],[-35,119],[28,-127]]
[[49,-209],[449,465],[321,-209],[-35,119],[28,-127]]
[[49,-209],[321,-209],[-35,119],[28,-127]]

[[125,-174],[-196,-434],[-149,-231],[102,-222],[-192,-473],[-458,-120],[-397,262],[243,46],[84,-222],[-261,-226],[199,-104],[-192,-444],[-144,499],[-171,262],[-425,-457],[-458,-271],[164,-496],[-449,-46],[-459,-102],[259,-222],[326,-260],[416,-495],[-404,98],[342,-469],[-165,499],[-317,112],[-459,446],[271,273],[460,426],[-395,-473],[-227,-50],[-358,284],[386,284],[-449,-133],[-495,361],[301,408],[-202,-222],[-122,-367],[199,-223],[301,499],[46,-243],[-251,196],[-449,406],[445,-174],[-458,-164],[-458,446],[-423,-222],[332,498],[24,446],[-409,262],[-309,-371],[-497,213],[445,475],[-75,262],[-488,499],[421,337],[69,-112],[120,-457],[45,-222],[221,196],[84,337],[386,-457],[-41,446],[14,-457],[410,446],[443,361],[-43,-317],[164,134],[-43,-308],[-290,-457],[-103,46],[-497,446],[423,-137],[155,445],[271,-18],[-175,152],[-458,-112],[34,45],[-122,499],[-497,-119],[-48,-119],[24,-222],[189,-457],[14,-7],[-289,-371],[-349,-50],[-335,-222],[-149,499],[-397,-112],[61,-457],[89,407],[199,352],[-189,319],[416,-135],[199,-222],[-132,499],[-380,-371],[-115,-260],[-337,475],[81,-285],[388,-222],[-37,-457],[34,-168],[98,-495],[84,-393],[148,-174],[-449,446],[-425,419],[61,-270],[-458,-469],[-413,-98],[326,49],[-158,-318],[46,446],[-380,152],[3,475],[-458,-442],[433,-469],[-192,89],[-272,227],[470,446]]

[[125,-174],[-196,-434],[-149,-231],[102,-222],[-192,-473],[-458,-120],[-397,262],[243,46],[84,-222],[-261,-226],[199,-104],[-192,-444],[-202,-222],[-122,-367],[388,-222],[61,-270]]

[[125,-174],[102,-222],[84,-222],[-202,-222],[388,-222],[61,-270]]
[[-202,-222],[61,-270],[84,-222],[102,-222],[125,-174],[388,-222]]




Case with 2 parallelograms where 4 points are on a line however
[[-202,-222],[61,-270],[84,-222],[102,-222],[125,-174],[388,-222]]
Here with one of the 2 parallelograms only
[[-202,-222],[61,-270],[125,-174],[388,-222]]
And here with the only the other one of the 2 parallelograms
[[61,-270],[84,-222],[102,-222],[125,-174]]

Case with 4 points on a line where mid point delivers same result for pairs 0 1 and 1 3
But because they are on one line, they cannot be counted as delivering a parallelogram
[[83,-25],[-65,-25],[17,-25],[1,-25]]
            between pair 0 1 -> mid_x = 18 mid_y = -50
            between pair 2 3 -> mid_x = 18 mid_y = -50
            so we get two counts of mid_x = 18 mix_y = -50

[[0,0],[0,4],[1,1],[1,3],[3,1],[3,3],[4,0],[4,4]]







*/
