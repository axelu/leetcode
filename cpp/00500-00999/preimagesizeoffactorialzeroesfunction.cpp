
// 793. Preimage Size of Factorial Zeroes Function
// https://leetcode.com/problems/preimage-size-of-factorial-zeroes-function/





// see https://www.purplemath.com/modules/factzero.htm

class Solution {
private:
    long f(long x) {
        // returns the number of zeroes in x!

        long cnt = 0;
        long five = 5;
        long t = x / five;
        while( t > 0L ) {
            cnt += t;
            five *= 5L;
            t = x / five;
        }

        return cnt;
    }

    // binary search
    long search(long s, long e, long target) {
        if( s > e )
            return -1;

        long mid = s + ((e-s)/2);
        long t = f(mid);
        if( t == target )
            return t;
        else if( t < target )
            return search(mid+1,e,target);
        else
            return search(s,mid-1,target);
    }

public:
    int preimageSizeFZF(int k) {
        // case k = 0
        // answer: 5 -> 0!, 1!, 2!, 3!, and 4! end with k = 0 zeroes
        // case k == 1
        // answer: 5 -> 5!, 6!, 7!, 8! and 9! end with k = 1 zeroes

        // powers of 5
        // 5^1    =       5
        // 5^2    =      25
        // 5^3    =     125
        // 5^4    =     625
        // 5^5    =    3125
        // 5^6    =   15625

        // the answer is either 0 or 5
        // example k = 30 -> answer = 0
        // 125 /   5 = 25
        // 125 /  25 =  5
        // 125 / 125 =  1
        // it is never possible to get a sum of 30
        // example k = 155 -> answer = 0
        // 625 /   5 = 125
        // 625 /  25 =  25
        // 625 / 125 =   5
        // 625 / 625 =   1
        // it is never possible to get a sum of 155

        // so the problem becomes: is there an x for which f(x) = k?
        // if yes -> answer = 5 else answer = 0

        /*
        // min x is 0
        // what is the the power of 5, whos factorial has 10^9 or more zeros? that is our max
        long i;
        long x;
        for(i = 0; i <= INT_MAX; ++i) {
            x = pow(5,i);
            long t = f(x);
            if( t >= 1000000000 )
                break;
        }
        cout << "i " << i << " x " << x << endl; // output i 14 x 6103515625
        // 5^14 = 6103515625
        */

        long t = search(0,6103515625,k);
        return t != -1 ? 5 : 0;
    }
};
