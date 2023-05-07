
// 2521. Distinct Prime Factors of Product of Array
// https://leetcode.com/problems/distinct-prime-factors-of-product-of-array/



class Solution {
public:
    int distinctPrimeFactors(vector<int>& nums) {
        // return the number of distinct prime factors in the product of the elements of nums
        // based on the property of a product, it the element in nums is a prime number it is part of the answer
        // so we just need to get the prime factors of each element
        // 2 <= nums[i] <= 1000

        set<int> primes1000 = {2,3,5,7,11,13,17,19,23,
                                  29,31,37,41,43,47,53,59,61,67,
                                  71,73,79,83,89,97,101,103,107,109,
                                  113,127,131,137,139,149,151,157,163,167,
                                  173,179,181,191,193,197,199,211,223,227,
                                  229,233,239,241,251,257,263,269,271,277,
                                  281,283,293,307,311,313,317,331,337,347,
                                  349,353,359,367,373,379,383,389,397,401,
                                  409,419,421,431,433,439,443,449,457,461,
                                  463,467,479,487,491,499,503,509,521,523,
                                  541,547,557,563,569,571,577,587,593,599,
                                  601,607,613,617,619,631,641,643,647,653,
                                  659,661,673,677,683,691,701,709,719,727,
                                  733,739,743,751,757,761,769,773,787,797,
                                  809,811,821,823,827,829,839,853,857,859,
                                  863,877,881,883,887,907,911,919,929,937,
                                  941,947,953,967,971,977,983,991,997};

        // prime factorization
        vector<vector<int>> t(1001);
        for(int x = 2; x <= 1000; ++x) {
            if( primes1000.find(x) != primes1000.end() ) {
                t[x].push_back(x);
                continue;
            }
            for(auto p = primes1000.begin(); p != primes1000.end() && *p * 2 <= x; ++p) {
                if( x % *p == 0 )
                    t[x].push_back(*p);
            }
        }

        unordered_set<int> primeFactors;
        for(int x: nums)
            for(int p: t[x])
                primeFactors.insert(p);

        return primeFactors.size();
    }
};
