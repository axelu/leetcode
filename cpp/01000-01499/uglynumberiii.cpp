
// 1201. Ugly Number III
// https://leetcode.com/problems/ugly-number-iii/

class Solution {
private:
    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    // function to return Least Common Multiple (LCM) of two numbers
    // LCM definition:
    // LCM of two numbers is the smallest number which can be divided by both numbers
    long long lcm(long a, long b) {
        return (a / gcd(a,b)) * b;
    }

    long countUgly(long a, long b, long c, long target) {
        long ans = 0;

        // for a good graphic see here:
        // https://leetcode.com/problems/ugly-number-iii/discuss/387554/CXX-Inclusion-Exclusion-and-Binary-Search

        // add the number of multiples of a,b,c individually
        ans += (target/a + target/b + target/c);

        // subtract the duplicates of the LCM of pairs ab, ac and bc
        ans -= (target/lcm(a,b) + target/lcm(a,c) + target/lcm(b,c));

        // add the number of multiples of the LCM between (a,b,c) back in
        ans += target/lcm(a,lcm(b,c));

        return ans;
    }

public:
    int nthUglyNumber(int n, int a, int b, int c) {
        // binary Search
        int start = 1;
        int end = INT_MAX;
        int mid;
        while(start + 1 < end) {
            mid = start + (end - start) / 2;
            if( countUgly(a,b,c,mid) >= n )
                end = mid;
            else
                start = mid;
        }
        if( countUgly(a,b,c,start) == n ) return start;
		else return end;
    }
};
