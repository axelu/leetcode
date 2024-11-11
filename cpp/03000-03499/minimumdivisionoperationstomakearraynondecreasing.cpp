
// 3326. Minimum Division Operations to Make Array Non Decreasing
// https://leetcode.com/problems/minimum-division-operations-to-make-array-non-decreasing/



vector<int> divisors[1000001]; // sorted set of divisors, lazy population
int is_prime[1000001]; // lazy population
bool init = false;

class Solution {
private:
    bool isPrime(int n) {
        if( is_prime[n] != -1 )
            return is_prime[n];

        if( n == 2 || n == 3 )
            return is_prime[n] = true;

        if( n <= 1 || n % 2 == 0 || n % 3 == 0  )
            return is_prime[n] = false;

        for(int i = 5; i * i <= n; i += 6 ) {
            if( n % i == 0 || n % (i + 2) == 0 )
                return is_prime[n] = false;
        }

        return is_prime[n] = true;
    }

    void calc_divisors(int a) {
        // will exclude 1 as a divisor
        // will exclude a as a divisor
        if( !divisors[a].empty() )
            return;

        int square_root = (int) sqrt(a) + 1;
        for(int i = 2; i < square_root; ++i) {
            if( a % i == 0 && i*i!= a ) {
                divisors[a].push_back(i);
                divisors[a].push_back(a/i);
            }
            if( a % i == 0 && i*i== a )
                divisors[a].push_back(i);
        }
        // divisors[a].push_back(a);
        sort(divisors[a].begin(),divisors[a].end());
    }

    // binary search
    int search(int a, int target) {
        int n = divisors[a].size();

        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            // if( target <= (a / divisors[a][mid]) )
            if( target >= (a / divisors[a][mid]) )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && (a / divisors[a][s]) > target )
            ++s;

        return s;
    }

public:
    int minOperations(vector<int>& nums) {
        if( !init ) {
            init = true;
            memset(is_prime,-1,sizeof is_prime);
        }

        int n = nums.size();

        int ans = 0;
        int last = nums[n-1];
        for(int i = n-2; i >= 0; --i) {
            // cout << "i " << i << " last " << last << endl;
            if( nums[i] <= last ) {
                last = nums[i];
                continue;
            }

            // if nums[i] is a prime, we are done
            // TODO store answer
            if( isPrime(nums[i]) )
                return -1;

            // let div be a divisor of nums[i] where 1 < div < nums[i]
            // we need to find the smalest div for which nums[i] / div <= last;
            calc_divisors(nums[i]);
            /*
            cout << "divisors " << nums[i] << ": ";
            for(int div: divisors[nums[i]])
                cout << div << " ";
            cout << endl;
            */
            int t = search(nums[i], last);
            // cout << "t " << t << endl;
            if( t == divisors[nums[i]].size() )
                return -1;

            ++ans;
            last = nums[i] / divisors[nums[i]][t];
        }

        return ans;
    }
};
