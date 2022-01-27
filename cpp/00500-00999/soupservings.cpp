
// 808. Soup Servings
// https://leetcode.com/problems/soup-servings/





class Solution {
private:
    unordered_map<long,double> mem;

    double rec(int A, int B) {
        if( A <= 0 && B > 0 )
            return 1.0;
        if( A <= 0 && B <= 0 )
            return 0.5;
        if( A > 0 && B <= 0 )
            return 0.0;

        long memKey = (unsigned long)A<<32;memKey += B;
        auto f = mem.find(memKey);
        if( f != mem.end() )
            return f->second;

        double a = 0.25 * rec(A-100,B);
        double b = 0.25 * rec(A-75,B-25);
        double c = 0.25 * rec(A-50,B-50);
        double d = 0.25 * rec(A-25,B-75);

        double ret = a+b+c+d;
        mem.insert({memKey,ret});
        return ret;
    }


public:
    double soupServings(int n) {
        if( n >= 10000 )
            return 1.0;
        return rec(n,n);
    }
};
