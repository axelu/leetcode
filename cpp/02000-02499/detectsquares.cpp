
// 2013. Detect Squares
// https://leetcode.com/problems/detect-squares/





class DetectSquares {
private:
    //  indexed by y, then by x
    //             y                 x  cnt
    unordered_map<int,unordered_map<int,int>> um;

public:
    DetectSquares() {
    }

    void add(vector<int> point) {
        int x = point[0];
        int y = point[1];

        auto f1 = um.find(y);
        if( f1 == um.end() ) {
            um.insert({y,{{x,1}}});
            return;
        }

        auto f2 = f1->second.find(x);
        if( f2 == f1->second.end() )
            f1->second.insert({x,1});
        else
            ++f2->second;
    }

    int count(vector<int> point) {
        int x = point[0];
        int y = point[1];

        int ans = 0;

        auto f1 = um.find(y);
        if( f1 == um.end() )
            return ans;

        for(auto it = f1->second.begin(); it != f1->second.end(); ++it) {
            // going through every point at the same y
            int tx = it->first; // x coordinate
            int tc = it->second;// count
            if( tx == x ) // looking for squares with positive area
                continue;

            // distance == length of side of square
            int d = tx - x;

            // we are looking for 2 more coordinates
            // original point y+d
            auto it_yplusd = um.find(y+d);
            if( it_yplusd != um.end() ) {
                auto f1 = it_yplusd->second.find(x);
                auto f2 = it_yplusd->second.find(tx);
                if( f1 != it_yplusd->second.end() && f2 != it_yplusd->second.end() )
                    ans += tc*f1->second*f2->second;
            }

            // repeat for oposite direction original point y-d
            auto it_yminusd = um.find(y-d);
            if( it_yminusd != um.end() ) {
                auto f1 = it_yminusd->second.find(x);
                auto f2 = it_yminusd->second.find(tx);
                if( f1 != it_yminusd->second.end() && f2 != it_yminusd->second.end() )
                    ans += tc*f1->second*f2->second;
            }


        }


        return ans;
    }
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */
