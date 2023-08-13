
// 2344. Minimum Deletions to Make Array Divisible
// https://leetcode.com/problems/minimum-deletions-to-make-array-divisible/




class Solution {
private:
    set<int> getFactors(int n, set<int>& divisors) {
        set<int> v;
        for(auto it = divisors.begin(); it != divisors.end(); ++it) {
            int i = *it;
            if( n % i == 0 ) {
                v.insert(i);
                //int q = n / i;
                //if( q != i && divisors.find(q) != divisors.end() )
                //    v.insert(q);
            }
        }

        return v;
    }

public:
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {
        set<int> factors;
        map<int,int> mp; // val, count
        for(int x: nums) {
            ++mp[x];
            factors.insert(x);
        }

        // for each element in numsDivide, get its factors
        // then union-merge those factors
        unordered_set<int> seen;
        for(int i = 0; i < numsDivide.size(); ++i) {
            auto p = seen.insert(numsDivide[i]);
            if( !p.second )
                continue;
            factors = getFactors(numsDivide[i],factors);
            if( factors.empty() )
                return -1;
        }

        // return 99;

        int ans = 0;
        auto itf = factors.begin();
        for(auto it = mp.begin(); it != mp.end(); ++it) {
            while( itf!= factors.end() && *itf < it->first )
                ++itf;
            if( itf == factors.end() )
                break;

            if( it->first == *itf )
                return ans;

            ans += it->second;
        }

        return -1;
    }
};



// alternate solution using a queue for the factors

class Solution {
private:
    queue<int> getFactors(int n, queue<int>& divisors) {
        queue<int> v;
        while( !divisors.empty() ) {
            int i = divisors.front();
            divisors.pop();
            if( n % i == 0 )
                v.push(i);
        }

        return v;
    }

public:
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {
        map<int,int> mp; // val, count
        for(int x: nums)
            ++mp[x];

        queue<int> factors;
        for(auto& p: mp)
            factors.push(p.first);

        // for each element in numsDivide, get its factors
        // then union-merge those factors
        unordered_set<int> seen;
        for(int i = 0; i < numsDivide.size(); ++i) {
            auto p = seen.insert(numsDivide[i]);
            if( !p.second )
                continue;
            factors = getFactors(numsDivide[i],factors);
            if( factors.empty() )
                return -1;
        }

        // return 99;

        int ans = 0;
        for(auto it = mp.begin(); it != mp.end(); ++it) {
            while( !factors.empty() && factors.front() < it->first )
                factors.pop();
            if( factors.empty() )
                break;

            if( it->first == factors.front() )
                return ans;

            ans += it->second;
        }

        return -1;
    }
};
