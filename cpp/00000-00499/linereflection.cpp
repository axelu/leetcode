
// 356. Line Reflection
// https://leetcode.com/problems/line-reflection/


class Solution {
private:
    // remove duplicates
    void removeDuplicates(vector<int>& arr) {
        // input is non-empty sorted vector<int>
        int n = arr.size();
        if( n == 1 )
            return;

        for(auto it = next(arr.begin()); it != arr.end(); )
            if( *prev(it) == *it )
                it = arr.erase(it);
            else
                ++it;
    }

    pair<bool,double> isSymmetric(vector<int>& arr) {
        // input is non-empty de-dup'ed sorted vector<int>
        int n = arr.size();
        if( n == 1 )
            return {true,arr[0]};

        int s = arr[0];
        int e = arr[n-1];

        int l = 0;
        int r = n-1;
        while( l < r ) {
            if( arr[l]-s != e-arr[r] )
                return {false,-1e9};
            ++l;
            --r;
        }

        double mid = s + ((e-s)/2.0);
        if( l == r && mid != (double)arr[l] )
            return {false,-1e9};

        return {true,mid};
    }

public:
    bool isReflected(vector<vector<int>>& points) {

        // if we have one point only at a given y,
        // the x of that point determines the result

        // mid = s + ((e-s)/2) -> e = 2*(mid-s) + s
        unordered_map<int,vector<int>> um;
        for(int i = 0; i < points.size(); ++i) {
            int x = points[i][0];
            int y = points[i][1];
            auto p = um.insert({y,{x}});
            if( !p.second )
                p.first->second.push_back(x);
        }

        // take whatever happens to be the 1st set of points
        // at a given y and determine the pivot x if there is one
        auto it = um.begin();
        sort(it->second.begin(),it->second.end());
        // example [[1,1],[-1,1],[1,1]] is considered symmetric,
        // hence we remove duplicates
        removeDuplicates(it->second);
        auto p = isSymmetric(it->second);
        if( !p.first )
            return false;
        double pivot = p.second;

        for(++it; it != um.end(); ++it) {
            sort(it->second.begin(),it->second.end());
            removeDuplicates(it->second);
            p = isSymmetric(it->second);
            if( !p.first || p.second != pivot )
                return false;
        }

        return true;
    }
};
