
// 2949. Count Beautiful Substrings II
// https://leetcode.com/problems/count-beautiful-substrings-ii/






/* see explanation at
 * https://youtu.be/4uuLN6EWT88
 *
 * we will view vowels as +1 and consonants as -1
 * via a prefixSum we can with that determine, between which indicies
 * the number of vowels and consonants are the same, as the prefixSum at those
 * indicies has to be the same
 * example: s = "baeyh", k = 2
 *              0  1  2  3  4  5
 *              b  a  e  y  h
 *             -1 +1 +1 -1 -1
 * prefixSum    0 -1  0  1  0 -1
 *                --------------   aeyh
 *             --------------     baey
 *             --------           ba
 *                   --------       ey
 *
 * which leads us to the next condition: (vowels * consonants) % k == 0
 * lets look at the above
 * aeyh -> (2 * 2) % k == 0 -> yes
 * baey -> (2 * 2) % k == 0 -> yes
 * ba   -> (1 * 1) % k == 0 -> NO
 * ey   -> (1 * 1) % k == 0 -> NO
 * so we need another vehicle to determin if an index with a given prefix sum is applicable
 * let the left index be i and the right index be j of where a given prefix sum is the same
 * the we get
 * ( (j-i)/2 * (j-i)/2 ) % k == 0
 * skipping divison by 4 for a moment, (j-i) * (j-i) expands to i*i - 2*i*j + j*j
 * we will not be able to separate i and j to get either on one side of the equation because of the 2*i*y
 * so we need to get rid of the squaring
 * let l be the length of our substring l = j - i
 * ( l/2 * l/2 ) % k == 0
 * ( (l*l)/4   ) % k == 0
 * so in order for our l*l to be divisible by k, l needs to bring
 * at least ceiling half of each prime factor of k to the table !!!
 * so we come up with a new k, that if l is divisible by this new k will ensure
 * that the condition of ((l*l)/4) % k == 0 is met
 * back to the 4 that we skipped -> primefactored 2 * 2
 * (l*l) % (4 * k) == 0
 * so additionally to ceiling half of each prime factor, l also needs to bring
 * at least one 2 to the table
 * lets take our example k = 2 -> primefactorization 2
 * so we have one 2 as a primefactor -> ceiling(1/2) -> 1, so our new new k so far is 2
 * we need to multiply with another 2 -> 2 * 2 = 4, our new k is 4
 * so we have our second condition to determine if an index qualifies:
 * the index must have the same remainder to our new k as the current index
 * back to our example with k_new = 4
 *              0  1  2  3  4  5
 *              b  a  e  y  h
 *             -1 +1 +1 -1 -1
 * prefixSum    0 -1  0  1  0 -1
 * idx % k_new  0  1  2  3  0  1
 *                --------------   aeyh
 *             --------------     baey
 *             --------           ba    <- same prefixSum, but different remainder, so l % k_new != 0
 *                   --------       ey  <- same prefixSum, but different remainder, so l % k_new != 0
 *
 */
class Solution {
private:
    bool is_vowel(char c) {
        // c is lower case
        return c == 'a' || c == 'e' || c == 'i' || c ==  'o' || c == 'u';
    }

    unordered_map<int,int> primeFactors(int n) {
        unordered_map<int,int> um; // prime factor, count

        // the number of 2s that divide n
        while(n % 2 == 0) {
            // cout << 2 << " ";
            ++um[2];
            n = n/2;
        }

        // n must be odd at this point.
        // skip one element (Note i = i +2)
        for(int i = 3; i <= sqrt(n); i = i + 2) {
            while(n % i == 0) {
                // cout << i << " ";
                ++um[i];
                n = n/i;
            }
        }

        // n is a prime number greater than 2
        if( n > 2 ) {
            // cout << n << " ";
            ++um[n];
        }

        return um;
    }

public:
    long long beautifulSubstrings(string& s, int k) {

        // calculate our new k
        auto um = primeFactors(k);
        int k_new = 1;
        for(auto& p: um) {
            int prime = p.first;
            int freq = ceil(p.second/2.0);
            k_new *= pow(prime,freq);
        }
        k_new *= 2; // cout << "k_new " << k_new << endl;

        long long ans = 0;
        int prefixSum = 0;
        unordered_map<int,unordered_map<int,int>> cnt;
        cnt[0][0] = 1;
        int n = s.size();
        for(int j = 1; j <= n; ++j) { // right index
            char c = s[j-1];
            prefixSum += is_vowel(c) ? 1 : -1;

            // cout << "prefixSum " << prefixSum << " j % k_new " << j % k_new << endl;
            // all indicies seen so far that have the same combination of prefixSum and j % k_new
            // form a substring to the current index with vowels == consonants and the length^2
            // to that index will be divisible by k, hence we count those
            ans += cnt[prefixSum][j % k_new];

            ++cnt[prefixSum][j % k_new]; // increase count with same combination of prefixSum and j % k_new
        }

        return ans;
    }
};
