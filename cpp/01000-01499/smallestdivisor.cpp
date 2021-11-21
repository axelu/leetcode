
// 1283. Find the Smallest Divisor Given a Threshold
// day 6 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/564/week-1-november-1st-november-7th/3521/
// https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/



class Solution {
private:
    int threshold;
    vector<int>::iterator itb;
    vector<int>::iterator ite;

    bool div(const int& divisor) {
        int sum = 0;
        for(auto it = itb; it != ite; ++it)
            sum += ceil(*it/(float)divisor);

        return sum <= threshold ? true : false;
    }

    int search(int s, int e) {
        if( s > e || e < s ) return INT_MAX;

        int k = s + ((e - s)/2);
        return div(k) ? min(k,search(s,k-1)) : search(k+1,e);
    }


public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int mxe = 0;
        long sum = 0;
        itb = begin(nums);
        ite = end(nums);
        for(auto it = itb; it != ite; ++it) {
            mxe = max(mxe,*it);
            sum += *it;
        }
        if( sum <= threshold ) return 1;

        this->threshold = threshold;
        // solution between 2 and mxe inclusive
        return search(2,mxe);
    }
};
