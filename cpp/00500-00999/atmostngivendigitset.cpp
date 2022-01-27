
// 902. Numbers At Most N Given Digit Set
// https://leetcode.com/problems/numbers-at-most-n-given-digit-set/
// day 21 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/566/week-3-november-15th-november-21st/3538/



class Solution {
private:
    vector<int> intToVector(int N) {
        vector<int> r;
        int t = N, rem;
        while(t != 0) {
            rem = t % 10;
            r.insert(begin(r),rem);
            t /= 10;
        }
        return r;
    }

    vector<int> vectorStringToVectorInt(vector<string>& digits) {
        vector<int> r;
        for(string s : digits)
            r.push_back(stoi(s));
        // just to be safe
        sort(begin(r),end(r));
        return r;
    }

public:
    int atMostNGivenDigitSet(vector<string>& digits, int N) {
        size_t n = digits.size();
        if( n == 0 || N <= 0 ) return 0;

        vector<int> nums = intToVector(N);
        int K = nums.size();

        vector<int> Digits = vectorStringToVectorInt(digits);

        int r = 0;

        // count number of possible numbers with length of 1, 2,..., K-1
        // number of digits to the power of the current length
        for(int i = 1; i < K; ++i)
            r += pow(n,i);

        // what is left to figure out is the number of possible numbers if length is K
        // our number has to be <= N !!!
        int cntSmaller;
        bool containsEqual;
        for(int i = 0; i < K; ++i) {
            cntSmaller = 0;
            containsEqual = false;
            for(int digit : Digits){
                if( digit < nums[i] ) ++cntSmaller;
                if( digit == nums[i] ) containsEqual = true;
            }

            // just as before we can compute the number of possible numbers
            // whose number of digits is LESS than our current number of digits
            r += cntSmaller * pow(n, K - i - 1) ;

            // if Digits does not contain the digit that is equal to the digit of
            // our current position in N, then we are done, as our number has to be <= N
            if( !containsEqual ) break;

            // if we are at the last position in N and Digits contains that number, than we can
            // make that number
            if( i == K - 1 && containsEqual ) ++r;
        }

        return r;
    }
};
