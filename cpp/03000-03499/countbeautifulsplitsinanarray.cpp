
// 3388. Count Beautiful Splits in an Array
// https://leetcode.com/problems/count-beautiful-splits-in-an-array/





// initialize once
unsigned long long p_pow[5001];
bool initialized = false;

class Solution {
private:
    const int p = 37; // prime 31 (w/ and w/o modulus) gave collision, hence using 37 as prime
    //const int m = 1e9 + 9;

public:
    int beautifulSplits(vector<int>& nums) {
        if( !initialized ) {
            initialized = true;
            p_pow[0] = 1ULL;
            for(int i = 1; i < 5001; ++i)
                p_pow[i] = (p_pow[i-1] * p);
        }

        int n = nums.size(); // 1 <= nums.length <= 5000
        // edge case
        if( n < 3 )
            return 0;
        if( n == 3 )
            return nums[0] == nums[1] || nums[1] == nums[2] ? 1 : 0;

        // we need to get three non-empty subarrays
        // we need to find every position in nums,
        // where nums[il,jl] == nums[ir,jr]
        // with jl + 1 = ir and 1 <= jl-il+1 == jr-ir+1 and 0 <= il,jl < ir,jr < n
        // let l be jl-il+1 and l*2 < n;

        // worst case n = 5000 -> we have 6249999 checks (1 <= l < 2500)

        // so we have 2 possibilities
        // A num1 is a prefix of nums2
        // nums1|nums2|nums3
        // 12345|12345|xxxxx
        // 12345|12345x|xxxx
        // 12345|12345xx|xxx
        // ...
        // 12345|12345xxxx|x
        // B nums2 is a prefix of nums3
        // x|12345|12345xxxx
        // xx|12345|12345xxx
        // ...

        // rolling hash
        vector<unsigned long long> h(n+1,0ULL);
        for(int i = 0; i < n; ++i)
            h[i+1] = (h[i] + (nums[i]+1) * p_pow[i]);


        int ans = 0;

        for(int l = 1; l * 2 < n; ++l) {
            //cout << "l " << l << endl;
            for(int jl = l-1; jl < n-l; ++jl) {
                int il = jl - l + 1;
                int ir = jl + 1;
                int jr = jl + l;

                //cout << "il " << il << " jl " << jl << " ir " << ir << " jr " << jr << endl;

                long long h1 = (h[il+l] - h[il]);
                long long h2 = (h[ir+l] - h[ir]);

                if( h2 == h1 * p_pow[l] ) {
                    // nums[il,jl] == nums[ir,jr]

                    /*
                    cout << "hit l " << l << " il " << il << " jl " << jl << " ir " << ir << " jr " << jr << endl;
                    for(int i = il; i <= jl; ++i)
                        cout << nums[i] << " ";
                    cout << ":";
                    for(int i = ir; i <= jr; ++i)
                        cout << nums[i] << " ";
                    cout << endl;
                    */

                    /*
                    // test for collision
                    bool collision = false;
                    for(int i = il, j = ir; i <= jl; ++i,++j) {
                        if( nums[i] != nums[j] ) {
                            collision = true;
                            break;
                        }
                    }
                    if( collision )
                        continue;
                    */

                    if( il == 0 ) {
                        // nums1 is prefix of nums2
                        ans += (n-1) - jr;

                    } else {
                        // nums2 is prefix of nums3

                        // don't double count
                        // example
                        // 3 3 3 1 3
                        // we have a hit 3|3|313 for both il = 0 and il = 1
                        // example
                        // 1 1 0 1 0
                        // we have a hit 1|1|010 for il = 0, that gives us 3 options:  1|1|010, 1|10|10, 1|101|0
                        // but we will also have a hit for il = 1 , l = 2 -> 1|10|10
                        /*
                        if( il == l ) {
                            // long long h0 = (h[l] + m) % m;
                            long long h0 = h[l];
                            if( h1 != h0 * p_pow[l] % m )
                                ans += 1;
                        */

                        if( il <= l ) {
                            // 0..il-1
                            int lgt = il;
                            long long h_0_lgt  = h[lgt];
                            long long h_il_lgt = (h[il+lgt] - h[il]);

                            if( h_il_lgt != h_0_lgt * p_pow[lgt] )
                                ans += 1;

                        } else {
                            ans += 1;
                        }
                    }
                }
            }
        }

        return ans;
    }
};
