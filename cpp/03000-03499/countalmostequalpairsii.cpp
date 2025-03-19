
// 3267. Count Almost Equal Pairs II
// https://leetcode.com/problems/count-almost-equal-pairs-ii/





class Solution {
    vector<int> int2vector(int num) {
        vector<int> ret;
        while( num > 0 ) {
            ret.push_back(num % 10);
            num /= 10;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    bool is_almost_equal(int a, int b) {
        if( a == b )
            return true;

        vector<int> va = int2vector(a);
        vector<int> vb = int2vector(b);

        while( va.size() < vb.size() )
            va.insert(va.begin(), 0);
        while( vb.size() < va.size() )
            vb.insert(vb.begin(), 0);

        vector<int> vd;
        for(int i = 0; i < va.size(); ++i) { // va.size() == vb.size()
            if( va[i] != vb[i] )
                vd.push_back(i);
        }

        if( vd.size() == 1 )
            return false;

        if( vd.size() == 2 )
            return va[vd[0]] == vb[vd[1]] && va[vd[1]] == vb[vd[0]];

        if( vd.size() == 3 ) {
            // digits in a respectively b at positions where a and b differ
            vector<int> vad, vbd;
            for(int i: vd) {
                vad.push_back(va[i]);
                vbd.push_back(vb[i]);
            }
            sort(begin(vad),end(vad));
            sort(begin(vbd),end(vbd));
            return vad == vbd;
        }

        if( vd.size() == 4 ) {
            /*
                x-----x
                0 1 2 3
                3 2 1 0
                  x-x

                  x---x
                0 1 2 3
                2 3 0 1
                x---x

                x-x
                0 1 2 3
                1 0 3 2
                    x-x

                not solvable in two swaps
                0 1 2 3
                3 0 1 2
            */
            if( (va[vd[0]] == vb[vd[3]] && va[vd[3]] == vb[vd[0]] && va[vd[1]] == vb[vd[2]] && va[vd[2]] == vb[vd[1]]) ||
                (va[vd[1]] == vb[vd[3]] && va[vd[3]] == vb[vd[1]] && va[vd[0]] == vb[vd[2]] && va[vd[2]] == vb[vd[0]]) ||
                (va[vd[0]] == vb[vd[1]] && va[vd[1]] == vb[vd[0]] && va[vd[2]] == vb[vd[3]] && va[vd[3]] == vb[vd[2]]) )
                return true;
        }

        return false;
    }

    unordered_map<string,int> um;

public:
    int countPairs(vector<int>& nums) {
        int n = nums.size(); // 2 <= nums.length <= 5000

        // number of pairs formula n * (n-1)/2
        // worst case n = 5000 -> 12497500 pairs

        int ans = 0;
        // brute force, but will take too long
        /*
        for(int i = 0; i < n-1; ++i) {
            for(int j = i+1; j < n; ++j) {
                if( is_almost_equal(nums[i], nums[j]) ) {
                    cout << nums[i] << " " << nums[j] << endl;
                    ++ans;
                }
            }
        }
        return ans;
        */

        // idea
        // collect all unique numbers and their count (at most 5000 unique)
        // collect them in a map
        // uniqe by unique
        //     store unique and count in local variable
        //     remove from map
        //     we know the pairs they make amongst themself if greater 1 count
        //     create every possible new one with one swap
        //         (28 possibilities, minus where the swapped digits are equal or
        //          new number gets greater 1e7, so ~ 5000*28 = 140000)
        //         and look in [remaining] numbers how many,
        //         our count * their count = pairs we can make
        //    create every possible new one with two swaps
        //         (28 * 15 = 420 possibilities, minus where the swapped
        //          digits are equal or new number gets greater 1e7, so ~ 5000*420 = 2100000)
        //

        for(int x: nums) {
            string sx = to_string(x);
            while( sx.size() < 8 ) // x max 10000000
                sx.insert(sx.begin(), '0');
            ++um[sx];
        }

        auto it = um.begin();
        while( it != um.end() ) {
            string sx = it->first;
            int cnt = it->second;
            it = um.erase(it);

            // cout << "sx " << sx << endl;

            ans += cnt * (cnt-1)/2;

            unordered_set<string> seen;
            // one swap
            for(int a = 0; a < 7; ++a) {
                char chra = sx[a];

                for(int b = a+1; b < 8; ++b) {
                    // one swap
                    char chrb = sx[b];

                    sx[a] = chrb;
                    sx[b] = chra;

                    // cout << "  one swap a " << a << " b " << b << " " << sx << endl;

                    if( sx[0] <= '1' && seen.insert(sx).second ) {
                        auto f = um.find(sx);
                        if( f != um.end() )
                            ans += cnt * f->second;
                    }
                    // backtrack
                    sx[a] = chra;
                    sx[b] = chrb;
                }
            }
            // two swap
            for(int a = 0; a < 7; ++a) {
                char chra = sx[a];

                for(int b = a+1; b < 8; ++b) {
                    // one swap
                    char chrb = sx[b];

                    sx[a] = chrb;
                    sx[b] = chra;

                    // cout << "  one swap a " << a << " b " << b << " " << sx << endl;

                    // second swap
                    for(int c = 0; c < 7; ++c) {

                        char chrc = sx[c];

                        for(int d = c+1; d < 8; ++d) {
                            if( c == a && d == b )
                                continue;

                            char chrd = sx[d];

                            sx[c] = chrd;
                            sx[d] = chrc;

                            // cout << "    two swaps c " << c << " d " << d << " " << sx << endl;

                            if( sx[0] <= '1' && seen.insert(sx).second ) {
                                auto f = um.find(sx);
                                if( f != um.end() )
                                    ans += cnt * f->second;
                            }

                            // backtrack
                            sx[c] = chrc;
                            sx[d] = chrd;
                        }
                    }

                    // backtrack
                    sx[a] = chra;
                    sx[b] = chrb;
                }
            }
        }

        return ans;
    }
};
