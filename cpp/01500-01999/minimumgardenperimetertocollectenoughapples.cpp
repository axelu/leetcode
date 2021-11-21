
// 1954. Minimum Garden Perimeter to Collect Enough Apples
// https://leetcode.com/problems/minimum-garden-perimeter-to-collect-enough-apples/
// https://leetcode.com/contest/weekly-contest-252/problems/minimum-garden-perimeter-to-collect-enough-apples/




class Solution {
public:
    long long minimumPerimeter(long long neededApples) {
        // the solution is between 1 and something
        // what is something?
        // worst case: neededApples = 10^15 = 1e15 = 1000000000000000

        // neededApples = 1e15 -> ans = 503968
        // so solution is between 1 and 503968
        // that means the side length of a quarter plot is 503968/8 = 62996

        // if we think in quarters, than a quarter of a plot
        // needs to yield at least neededApples/4 apples
        // if neededApples is divisible by 4, else neededApples/4 + 1
        // worst case: a quarter plot needs to yield 250000000000000

        if( neededApples <= 12 )
            return 8;

        int i;

        long long neededQuarterYield = neededApples/4LL;
        if( neededApples % 4LL != 0 )
            ++neededQuarterYield;

        // formula for apples yielded in a quarter
        // based on side length n of said quarter
        // f(n) = f(n-1) + ( n + 2*(n+1 + n+2 + ... 2n-1) + 2n )

        long long prefixSum[2*62996+2];
        prefixSum[0] = 0;
        for(i = 0; i <= 2*62996; ++i)
            prefixSum[i+1] = prefixSum[i] + i;


        long long prev = 3;     // yield of a quarter with side length = 1
        long long quarterYield;
        for(i = 2; i <= 62996; ++i) { // side length of a quarter

            quarterYield = prev + i + 2*( prefixSum[2*i]-prefixSum[i+1] ) + 2*i;
            if( quarterYield >= neededQuarterYield )
                break;
            prev = quarterYield;

        }

        return i*8;
    }
};
