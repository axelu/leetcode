
// 313. Super Ugly Number
// https://leetcode.com/problems/super-ugly-number/



class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {

        // pair: ugly number, index of prime which we used to create ugly number
        auto cmp = [](pair<long,int>& a, pair<long,int>& b) {
            return a.first > b.first;
        };
        priority_queue<pair<long,int>,vector<pair<long,int>>,decltype(cmp)> pq(cmp); // min heap

        for(int i = 0; i < primes.size(); ++i)
            pq.push({primes[i],i}); // each of our primes is an ugly number, prime * 1


        vector<long> nums; // ugly numbers in ascending order
        nums.push_back(1); // our 1st ugly number is 1

        vector<int> idx(primes.size(),0);

        long currUgly,newUgly;
        int primeIdx;
        while(nums.size() < n )            {
            currUgly = pq.top().first;
            primeIdx = pq.top().second;
            pq.pop();

            if( currUgly != nums.back() )
                nums.push_back(currUgly);

            // the prime that generated the current ugly number
            // should move forward to multiply new ugly number
            ++idx[primeIdx];

            newUgly = nums[idx[primeIdx]] * primes[primeIdx];
            pq.push({newUgly,primeIdx});
        }

        return nums.back();
    }
};
