
// 1999. Smallest Greater Multiple Made of Two Digits
// https://leetcode.com/problems/smallest-greater-multiple-made-of-two-digits/



class Solution {
public:
    int findInteger(int k, int digit1, int digit2) {

        priority_queue<long,vector<long>,greater<long>> pq;

        if( digit1 > 0 )
            pq.push(digit1);
        if( digit2 > 0 && digit2 != digit1 )
            pq.push(digit2);

        while( !pq.empty() ) {
            long t = pq.top();
            pq.pop();

            if( t > k && t % k == 0 )
                return t;

            t *= 10;
            if( t + digit1 < INT_MAX )
                pq.push(t + digit1);
            if( digit2 != digit1 && t + digit2 < INT_MAX )
                pq.push(t + digit2);
        }

        return -1;
    }
};
