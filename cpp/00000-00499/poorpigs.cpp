
// 458. Poor Pigs
// https://leetcode.com/problems/poor-pigs/
// day 14 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/565/week-2-november-8th-november-14th/3530/





// 4 buckets
// -> 1 Test
//
// bucket 3 2 1 0
// pig0   -   -
// pig1	  - -
// we need to represent 4 states
// bucket 0 poison = pig1 lives + pig0 lives
// bucket 1 poison = pig1 lives + pig0 dies
// bucket 2 poison = pig1 dies 	+ pig0 lives
// bucket 3 poison = pig1 dies 	+ pig0 dies
// shown differently
// 0 pigx lives / 1 pig died
// bucket/pig 1 0
// 0	      0 0
// 1          0 1
// 2          1 0
// 3          1 1

// 5 buckets
// -> 1 Test
//
// bucket 4 3 2 1 0
// pig0     -   -
// pig1     - -
// pig2   -
// we need to represent 5 states
// 0 pigx lives / 1 pig died
// bucket/pig 2 1 0
// 0	      0 0 0
// 1          0 0 1
// 2          0 1 0
// 3          0 1 1
// 4          1 0 0

// 5 buckets
// -> 2 Tests
//
// e.g.
// Test 0 Test only # buckets = buckets - (remaining tests * 2 buckets)
// bucket 4 3 2 1 0
// pig0   -   -
// pig1	  - -
// Test 1
// bucket 4 3 2 1 0
// pig0
// pig1	        -


class Solution {
private:
    long T;
    int N;

    int search(int s, int e) {
        if( s > e || e < s )
            return 32;
        int x = s + ((e - s)/2);
        return pow((T+1L),x) >= N ? min(x,search(s,x-1)) : search(x+1,e);
    }
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        // 0 <= buckets <= INT_MAX
        if( buckets <= 1 ) return 0;

        // assume minutesToDie > 0 to not have division by 0
        // 0 < minutesToDie <= INT_MAX
        // minutesToTest >= minutesToDie
        // 0 < minutesToDie <= minutesToTest <= INT_MAX

        // number of Tests
        T = minutesToTest / minutesToDie;
        // Tmin = 1
        // Tmax = 2147483647

        N = buckets;

        // find minimum r such that (T+1)^x >= N
        // xmin = 1
        // xmax = 31 (Tmin + 1)^31 = (1+1)^31 = 2147483648

        // binary search
        return search(1,31);
    }
};
