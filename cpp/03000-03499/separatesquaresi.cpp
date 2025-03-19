
// 3453. Separate Squares I
// https://leetcode.com/problems/separate-squares-i/





class Solution {
private:
    pair<double,double> solve(vector<vector<int>>& squares, double div) {
        double area_above = 0.0;
        double area_below = 0.0;

        for(auto& v: squares) {
            double y = v[1];
            double h = v[2];

            if( y > div ) {
                // area is entirely above the dividing horizontal line
                area_above += h * h;
            } else if( y + h <= div ) {
                // area is entirely below the dividing horizontal line
                area_below += h * h;
            } else {
                // dividing line cuts the area
                area_above += (y + h - div) * h;
                area_below += (div - y) * h;
            }
        }

        return {area_below, area_above};
    }

    // binary search floating point
    double search(vector<vector<int>>& squares, double s, double e) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1.0;

        double mid = s + ((e-s)/2.0);
        auto [area_below, area_above] = solve(squares, mid);
        // cout << "mid " << mid << " area_below " << area_below << " area_above " << area_above << endl;

        if( area_above <= area_below + 1e-5) { // floating point compare
            double t = search(squares, s, mid - 1e-6);
            return t != -1.0 ? t : mid;
        }

        return search(squares, mid + 1e-6, e);
    }

public:
    double separateSquares(vector<vector<int>>& squares) {
        int n = squares.size();

        /*
        // example [[0,0,2],[1,1,1]]
        auto [area_below, area_above] = solve(squares, 1.16667);
        cout << "area_below " << area_below << " area_above " << area_above << endl;
        return 99.9;
        */

        int y_min = 1000000000;
        int y_max = 1;
        for(auto& v: squares) {
            y_min = min(y_min, v[1]);
            y_max = max(y_max, v[1] + v[2]);
        }

        // our solutions lies between y_min and y_max
        return search(squares, y_min, y_max);
    }
};
