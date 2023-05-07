
// 2198. Number of Single Divisor Triplets
// https://leetcode.com/problems/number-of-single-divisor-triplets/




class Solution {
public:
    long long singleDivisorTriplet(vector<int>& nums) {

        unordered_map<int,long long> um; // val,count
        for(int x: nums)
            ++um[x];

        long long ans = 0;

        // taking 3 of one integer cannot be a solution
        // because the sum would be divisible by said integer
        // which would occur on all indexes chosen and
        // with that it would not be single divisor

        // take 2 of one integer (if we have 2 or more) and 1 of another
        // if the sum is divisible by only the integer we are chosing 1 of
        // then we have a valid single divisor triplet
        for(auto i = um.begin(); i != um.end(); ++i) {
            if( i->second >= 2 ) {
                int nums_i = i->first;
                for(auto k = um.begin(); k != um.end(); ++k) {
                    if( k == i )
                        continue;

                    int nums_k = k->first;

                    int sum = nums_i + nums_i + nums_k;
                    if( sum % nums_k == 0 && sum % nums_i != 0 ) {
                        // we found a valid triplet
                        //               number of pairs of nums_i    * k->second * 6
                        long long t = (i->second * (i->second - 1)/2) * k->second * 6LL;
                        // cout << "found a triplet " << nums_i << " " <<  nums_i << " " << nums_k << " o:" << t << endl;

                        ans += t;
                    }
                }
            }
        }

        // take 1 of each integer
        for(auto i = um.begin(); i != um.end(); ++i) {
            int nums_i = i->first;

            for(auto j = next(i); j != um.end(); ++j) {
                int nums_j = j->first;

                for(auto k = next(j); k != um.end(); ++k) {
                    int nums_k = k->first;

                    int sum = nums_i + nums_j + nums_k;
                    int t = 0;
                    t += sum % nums_i == 0;
                    t += sum % nums_j == 0;
                    t += sum % nums_k == 0;
                    if( t == 1 ) {
                        // we found a valid triplet
                        long long t = i->second * j->second * k->second * 6LL;
                        // cout << "found a triplet " << nums_i << " " <<  nums_j << " " << nums_k << " o:" << t << endl;

                        ans += t;
                    }
                }
            }
        }

        return ans;
    }
};
