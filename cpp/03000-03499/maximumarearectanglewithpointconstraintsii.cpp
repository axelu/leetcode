
// 3382. Maximum Area Rectangle With Point Constraints II
// https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-ii/


// see also 2940. Find Building Where Alice and Bob Can Meet https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/

class Solution {
private:
    vector<map<int,vector<int>>::iterator> a;

    vector<vector<int>> t; // segment tree "merge sort tree" with fractional cascading
    vector<vector<int>> aux_l;
    vector<vector<int>> aux_r;
    
    const int INF = 80000001; // based on 0 <= xCoord[i], yCoord[i] <= 8 * 1e7
    
    int upper_bound(int v, int target) {

        int n = t[v].size();

        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= t[v][mid] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && t[v][s] <= target )
            ++s;

        return s;
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl]->second;
        } else {
            int tm = (tl + tr) / 2;
            build(v*2, tl, tm);
            build(v*2+1, tm+1, tr);
            // merge(t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(), back_inserter(t[v]));
            // merge
            int i = 0, j = 0, k = 0;
            t[v].resize(t[v*2].size() + t[v*2+1].size());
            aux_l[v].resize(t[v*2].size() + t[v*2+1].size());
            aux_r[v].resize(t[v*2].size() + t[v*2+1].size());
            while( i < t[v*2].size() && j < t[v*2+1].size() ) {
                if( t[v*2][i] < t[v*2+1][j] ) {
                    t[v][k] = t[v*2][i];
                    aux_l[v][k] = i;
                    aux_r[v][k] = j;
                    ++i;
                } else {
                    t[v][k] = t[v*2+1][j];
                    aux_l[v][k] = i;
                    aux_r[v][k] = j;
                    ++j;
                }
                ++k;
            }
            while( i < t[v*2].size() ) {
                t[v][k] = t[v*2][i];
                aux_l[v][k] = i;
                aux_r[v][k] = j;
                ++i;
                ++k;
            }
            while( j < t[v*2+1].size() ) {
                t[v][k] = t[v*2+1][j];
                aux_l[v][k] = i;
                aux_r[v][k] = j;
                ++j;
                ++k;
            }
        }
    }

    int query(int v, int tl, int tr, int l, int r, int x, int ub) {
        if (l > r || ub == t[v].size() )
            return INF;

        // at root
        if( v == 1 )
            ub = upper_bound(v,x);

        if (l == tl && r == tr) {
            /*
            vector<int>::iterator pos = upper_bound(t[v].begin(), t[v].end(), x);
            if (pos != t[v].end())
                return *pos;
            return INF;
            */
            /*
            int pos = upper_bound(v,x);
            if( pos < t[v].size() )
                return t[v][pos];
            return INF;
            */
            return t[v][ub];
        }
        int tm = (tl + tr) / 2;
        return min(query(v*2, tl, tm, l, min(r, tm), x, aux_l[v][ub]),
                   query(v*2+1, tm+1, tr, max(l, tm+1), r, x, aux_r[v][ub]));
    }
    
    
    
public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int n = xCoord.size(); // 1 <= xCoord.length == yCoord.length <= 2 * 1e5

        // given the large constraint
        // worst case is we have 200000 distinct x and 200000 distinct y
        // if we index our points by x and y coordinates, we could
        // reasonble fast iterate through them and find candidate rectangles
        // then we would have to answer the question if there are points inside
        // we would know that we don't have any on the edges already, so only inside
        //     using a 2D prefixSum to see if points are inside
        //     is not possible, because of large constraint, even with coordinate compression
        //     we would have 200,000 x 200,000
        //     using a 2D segment tree not possible because of large constraint
        //     using a 2D binary indexed tree not possible because of large contraint
        // what if we maintain a 1D segment tree while we go through the rectangles?
        
        
        vector<vector<int>> points(n, vector<int>(2));
        for(int i = 0; i < n; ++i)
            points[i] = {xCoord[i], yCoord[i]};
        
        // sort by y, then x asc
        sort(begin(points), end(points), [](const vector<int>& a, const vector<int>& b){
            if( a[1] < b[1] ) {
                return true;
            } else if( a[1] == b[1] ) {
                if( a[0] < b[0] ) {
                    return true;
                }
            }
            return false;
        });
        map<int,vector<int>> byY; // key: y, value: sorted x's
        for(int i = 0; i < n; ++i)
            byY[points[i][1]].push_back(points[i][0]);
        
        
        // build a segment tree that can answer the question
        //   given y0 and y1, where y0 <= y1
        //   given the segment [y0,y1], give me the next greater element (upper bound) of a given x
        // we need to use coordinate compression, because 0 <= yCoord[i] <= 8 * 1e7
        
        int y_sz = byY.size(); // cout << "y_sz " << y_sz << endl;
        unordered_map<int,int> dictY; // key: y value: index
        a.resize(y_sz);
        int i = 0;
        for(auto it = byY.begin(); it != byY.end(); ++it) {
            dictY[it->first] = i;
            a[i++] = it;
        }
        
        t.resize(4*y_sz);
        aux_l.resize(4*y_sz);
        aux_r.resize(4*y_sz);

        build(1, 0, y_sz-1);
        
        
        // sort by x, then y asc; to process points by x
        sort(begin(points), end(points));
        
        long long ans = -1LL;
        
        int max_x = points.back()[0];
        for(i = 0; points[i][0] < max_x; ++i) { // we don't need to explore largest x as we are looking to the right
            if( points[i][0] != points[i+1][0] )
                continue;
            
            int x0 = points[i][0];
            int y0 = points[i][1];
            //  x1 = x0
            int y1 = points[i+1][1];
            
            int y0_idx = dictY[y0];
            int y1_idx = dictY[y1];
            
            // cout << "x0 " << x0 << " y0 " << y0 << " y1 " << y1 << endl;
            int x2 = query(1, 0, y_sz-1, y0_idx, y1_idx, x0, -1);
            // cout << "x2 " << x2 << endl;
            // x2 will be INF if there is no x > x0 in segment [y0,y1]
            if( x2 == INF )
                continue;
            
            long long area = (long long)(x2-x0) * (long long)(y1-y0);
            if( area <= ans )
                continue;
            
            // find the point x2,y0 in points, if it does not exist, we are done
            // returns 'n' if target greater than greatest element
            // returns  0  if target less or equal than smallest element, s in our case
            // binary search lower bound while loop
            // lower bound -> equal or greater than target
            int s = i;
            int e = n;
            int mid;
            while(s < e) {
                mid = s + ((e-s)/2);
                if( x2 < points[mid][0] || (x2 == points[mid][0] && y0 <= points[mid][1]) )
                    e = mid;
                else
                    s = mid+1;
            }
            if( s < n && (points[s][0] < x2 || (points[s][0] == x2 && points[s][1] < y0)) )
                ++s;
            
            // cout << "s " << s << endl;
            
            if( s == n || points[s][0] != x2 || points[s][1] != y0 )
                continue;
            
            // if it does exist, then the next point must be x2,y1, only then we have a rectangle
            if( s > n-1 || points[s+1][0] != x2 || points[s+1][1] != y1 )
                continue;
                
                
            // if we are still here, then we have found a rectangle 
            // with a greater area and no point inside
            ans = area;
        }
        
        return ans;
    }
};




// passes 590/594 tests as of 12/12/2024, then TLE

class Solution {
public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int n = xCoord.size(); // 1 <= xCoord.length == yCoord.length <= 2 * 1e5

        // given the large constraint
        // worst case is we have 200000 distinct x and 200000 distinct y
        // if we index our points by x and y coordinates, we could
        // reasonble fast iterate through them and find candidate rectangles
        // then we would have to answer the question if there are points inside
        // we would know that we don't have any on the edges already, so only inside
        //     using a 2D prefixSum to see if points are inside
        //     is not possible, because of large constraint, even with coordinate compression
        //     we would have 200,000 x 200,000
        //     using a 2D segment tree not possible because of large constraint
        //     using a 2D binary indexed tree not possible because of large contraint
        // what if we maintain a 1D segment tree while we go through the rectangles?
        // lets start with just upper_bound searches

        // brute force

        map<int,set<int>> byX;
        map<int,set<int>> byY;

        for(int i = 0; i < n; ++i) {
            // byX
            byX[xCoord[i]].insert(yCoord[i]);
            // byY
            byY[yCoord[i]].insert(xCoord[i]);
        }

        /*
         *    P1     P3
         *
         *    P0     P2
         *
         */

        long long ans = -1LL;

        // we are walking from left to right
        for(auto it_byX = byX.begin(); it_byX != byX.end(); ++it_byX)  {
            // p0 bottom left
            int x0 = it_byX->first;
            for(auto it_byXY = it_byX->second.begin(); it_byXY != it_byX->second.end(); ++it_byXY) {
                int y0 =  *it_byXY;
                // cout << endl;
                // cout << "P0 " << x0 << " " << y0 << " ";

                // do we have a point straight above us, P1?
                if( next(it_byXY) != it_byX->second.end() ) {
                    int x1 = x0;
                    int y1 = *next(it_byXY);
                    // cout << "P1 " << x1 << " " << y1 << " ";

                    // do we have a point P2?
                    int y2 = y0;
                    auto it_byYp2 = byY.find(y2); // we will have a hit
                    // find the next x greater than x0 respectively x1 (x0 == x1)
                    auto it_x2 = it_byYp2->second.upper_bound(x0);
                    if( it_x2 != it_byYp2->second.end() ) {
                        int x2 = *it_x2;
                        // cout << "P2 " << x2 << " " << y2 << " ";

                        // do we have a point P3?
                        auto it_byYp3 = byY.find(y1); // we will have a hit
                        // find the next x greater than x0 respectively x1 (x0 == x1)
                        auto it_x1 = it_byYp3->second.find(x1); // we will have a hit
                        if( it_x1 != it_byYp3->second.end() && *next(it_x1) == x2 ) {

                            // we know that P3 is the next point to the right of P1
                            // but we don't know, if P3 is the next point up from P2
                            auto it_byXp2 = byX.find(x2); // we will have a hit
                            if( *(it_byXp2->second.upper_bound(y2)) < y1 )
                                break;

                            int y3 = y1;
                            int x3 = x2;
                            // cout << "P3 " << x3 << " " << y3 << " ";

                            // if we are here the question becomes, if there is a point inside?
                            // more formally:
                            // is there a point p_inside where
                            // x0 < x_inside < x2 && y0 < y_inside < y1
                            // if area of candidate is smaller than current answer,
                            // no need to do the search
                            long long area = (long long)(x2-x1) * (long long)(y1-y0);
                            if( area <= ans )
                                continue;

                            //cout << "P0 " << x0 << " " << y0 << " P1 " << x1 << " " << y1 << " P2 " << x2 << " " << y2 << " P3 " << x3 << " " << y3 << " ";
                            //cout << "area candidate " << area << " ";
                            //cout << endl;

                            // if x2-x1 == 1 || y1-y0 == 1, there can be nothing inside
                            if( x2-x1 == 1 || y1-y0 == 1 ) {
                                ans = area;
                                continue;
                            }

                            auto it_bYinside = byY.upper_bound(y0); // will have a hit, at least y1
                            bool inside = false;
                            while( it_bYinside->first < y1 ) {

                                auto it_xinside = it_bYinside->second.upper_bound(x0);
                                if( it_xinside != it_bYinside->second.end() && *it_xinside < x2 ) {
                                    //cout << "inside " << *it_xinside << " " << it_bYinside->first << endl;
                                    inside = true;
                                    break;
                                }
                                ++it_bYinside;
                            }
                            if( !inside )
                                ans = area;
                        }
                    }
                }
            }
        }

        return ans;
    }
};
