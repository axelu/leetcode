
// 3714. Longest Balanced Substring II
// https://leetcode.com/problems/longest-balanced-substring-ii/



// based on hints
// even though I had arrived at the prefixSum idea on my own

class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();

        int mx_consecutive = 1;
        int consecutive_a = 0;
        int consecutive_b = 0;
        int consecutive_c = 0;

        int prefixSum_a[100001];prefixSum_a[0] = 0; // "1-indexed"
        int prefixSum_b[100001];prefixSum_b[0] = 0; // "1-indexed"
        int prefixSum_c[100001];prefixSum_c[0] = 0; // "1-indexed"
        //vector<int> prefixSum_a(n+1, 0); // "1-indexed"
        //vector<int> prefixSum_b(n+1, 0); // "1-indexed"
        //vector<int> prefixSum_c(n+1, 0); // "1-indexed"


        int mx_2 = 0;
        int last_a = -1;
        int last_b = -1;
        int last_c = -1;
        map<int,int> ab{{0,-1}}; // key: prefixSum_a[i+1]-prefixSum_b[i+1] value: i
        map<int,int> ac{{0,-1}}; // key: prefixSum_a[i+1]-prefixSum_c[i+1] value: i
        map<int,int> bc{{0,-1}}; // key: prefixSum_b[i+1]-prefixSum_c[i+1] value: i

        int mx_3 = 0;
        // key: {prefixSum_a[i+1]-prefixSum_b[i+1], prefixSum_a[i+1]-prefixSum_c[i+1]} value: i
        map<pair<int,int>,int> abc{{{0,0},-1}};

        for(int i = 0; i < n; ++i) {
            if( s[i] == 'a' ) {
                mx_consecutive = max({mx_consecutive, consecutive_b, consecutive_c});
                consecutive_b = 0;
                consecutive_c = 0;
                ++consecutive_a;

                prefixSum_a[i+1] = prefixSum_a[i] + 1;
                prefixSum_b[i+1] = prefixSum_b[i];
                prefixSum_c[i+1] = prefixSum_c[i];

                // when was the last time we saw b and c if ever?
                // let last_b be the index we saw b last
                // let last_c be the index we saw c last
                // if last_b < last_c, that means
                //    last_b+1..i we have only seen a and c
                //    we have a streak of a's and c's
                // if last_c < last_b, that means
                //    last_c+1..i we have only seen a and b
                //    we have a streak of a's and b's
                // note watch out for last_b == last_c, that means
                //    we have only seen a up to this point
                if( last_b < last_c ) {
                    int curr_ac = prefixSum_a[i+1] - prefixSum_c[i+1];
                    auto f = ac.find(curr_ac);
                    if( f != ac.end() ) {
                        int dist = i - f->second;
                        mx_2 = max(mx_2, dist);
                    }

                } else if( last_c < last_b ) {
                    int curr_ab = prefixSum_a[i+1] - prefixSum_b[i+1];
                    auto f = ab.find(curr_ab);
                    if( f != ab.end() ) {
                        int dist = i - f->second;
                        mx_2 = max(mx_2, dist);
                    }
                }
                // bc.clear();bc.insert({0,i});
                bc.clear(); bc.insert({prefixSum_b[i+1] - prefixSum_c[i+1], i});
                ac.insert({prefixSum_a[i+1] - prefixSum_c[i+1], i});
                ab.insert({prefixSum_a[i+1] - prefixSum_b[i+1], i});

                last_a = i;

            } else if( s[i] == 'b' ) {
                mx_consecutive = max({mx_consecutive, consecutive_a, consecutive_c});
                consecutive_a = 0;
                consecutive_c = 0;
                ++consecutive_b;

                prefixSum_a[i+1] = prefixSum_a[i];
                prefixSum_b[i+1] = prefixSum_b[i] + 1;
                prefixSum_c[i+1] = prefixSum_c[i];

                // when was the last time we saw a and c if ever?
                // let last_a be the index we saw a last
                // let last_c be the index we saw c last
                // if last_a < last_c, that means
                //    last_a+1..i we have only seen b and c
                //    we have a streak of b's and c's
                // if last_c < last_a, that means
                //    last_c+1..i we have only seen a and b
                //    we have a streak of a's and b's
                // note watch out for last_a == last_c, that means
                //    we have only seen a up to this point
                if( last_a < last_c ) {
                    int curr_bc = prefixSum_b[i+1] - prefixSum_c[i+1];
                    auto f = bc.find(curr_bc);
                    if( f != bc.end() ) {
                        int dist = i - f->second;
                        mx_2 = max(mx_2, dist);
                    }

                } else if( last_c < last_a ) {
                    int curr_ab = prefixSum_a[i+1] - prefixSum_b[i+1];
                    auto f = ab.find(curr_ab);
                    if( f != ab.end() ) {
                        int dist = i - f->second;
                        mx_2 = max(mx_2, dist);
                    }
                }
                //ac.clear();ac.insert({0,i});
                ac.clear();ac.insert({prefixSum_a[i+1] - prefixSum_c[i+1], i});
                bc.insert({prefixSum_b[i+1] - prefixSum_c[i+1], i});
                ab.insert({prefixSum_a[i+1] - prefixSum_b[i+1], i});

                last_b = i;

            } else { // s[i] == 'c'
                mx_consecutive = max({mx_consecutive, consecutive_a, consecutive_b});
                consecutive_a = 0;
                consecutive_b = 0;
                ++consecutive_c;

                prefixSum_a[i+1] = prefixSum_a[i];
                prefixSum_b[i+1] = prefixSum_b[i];
                prefixSum_c[i+1] = prefixSum_c[i] + 1;

                // when was the last time we saw a and b if ever?
                // let last_a be the index we saw a last
                // let last_b be the index we saw b last
                // if last_a < last_b, that means
                //    last_a+1..i we have only seen b and c
                //    we have a streak of b's and c's
                // if last_b < last_a, that means
                //    last_b+1..i we have only seen a and c
                //    we have a streak of a's and c's
                // note watch out for last_a == last_b, that means
                //    we have only seen a up to this point
                if( last_a < last_b ) {
                    int curr_bc = prefixSum_b[i+1] - prefixSum_c[i+1];
                    auto f = bc.find(curr_bc);
                    if( f != bc.end() ) {
                        int dist = i - f->second;
                        mx_2 = max(mx_2, dist);
                    }

                } else if( last_b < last_a ) {
                    int curr_ac = prefixSum_a[i+1] - prefixSum_c[i+1];
                    auto f = ac.find(curr_ac);
                    if( f != ac.end() ) {
                        int dist = i - f->second;
                        mx_2 = max(mx_2, dist);
                    }
                }
                //ab.clear();ab.insert({0,i});
                ab.clear();ab.insert({prefixSum_a[i+1] - prefixSum_b[i+1], i});
                ac.insert({prefixSum_a[i+1] - prefixSum_c[i+1], i});
                bc.insert({prefixSum_b[i+1] - prefixSum_c[i+1], i});

                last_c = i;
            }

            int abc_ab = prefixSum_a[i+1] - prefixSum_b[i+1];
            int abc_ac = prefixSum_a[i+1] - prefixSum_c[i+1];
            auto p = abc.insert({{abc_ab, abc_ac},i});
            if( !p.second ) {
                mx_3 = max(mx_3, i - p.first->second);
            }
        }
        // finish up
        mx_consecutive = max({mx_consecutive, consecutive_a, consecutive_b, consecutive_c});

        // cout << "mx_consecutive " << mx_consecutive << endl;
        // cout << "mx_2 " << mx_2 << endl;
        // cout << "mx_3 " << mx_3 << endl;

        return max({mx_consecutive, mx_2, mx_3});
    }
};
