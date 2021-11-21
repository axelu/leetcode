
// 2001. Number of Pairs of Interchangeable Rectangles
// https://leetcode.com/problems/number-of-pairs-of-interchangeable-rectangles/







class Solution {
private:
    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    // number of pairs
    long long comb(long long n) {
        if( n == 1 )
            return 0;
        if( n == 2 )
            return 1;

        // n! / ( r! x (n-r)!  )
        // n = number of objects
        // r = sample size, we know r is always 2

        return (n-1)*n/2LL;
    }

public:
    long long interchangeableRectangles(vector<vector<int>>& rectangles) {

        map<array<int,2>,int> pairs;
        pair<map<array<int,2>,int>::iterator,bool> p;
        int height,width,div,a,b;
        for(int i = 0; i < rectangles.size(); ++i) {
            width  = rectangles[i][0];
            height = rectangles[i][1];
            div = gcd(width,height);
            a = width/div;
            b = height/div;
            p = pairs.insert({{a,b},1});
            if( !p.second )
                ++p.first->second;
        }

        long long ans = 0LL;
        for(auto it = pairs.begin(); it != pairs.end(); ++it)
           ans += comb(it->second);

        return ans;
    }
};
