
// 854. K-Similar Strings
// https://leetcode.com/problems/k-similar-strings/



class Solution {
public:
    int kSimilarity(string s1, string s2) {
        int n = s1.size(); // s1.size() == s2.size()

        // s2 -> pos,bit
        int t2[n];
        for(int i = 0; i < n; ++i) {
            int t2idx = (s2[i]-'a') * n + i;
            t2[i] = t2idx;
        }

        struct T {
            int steps;
            int pos;
            bitset<120> mat;
            T(int x, int p, bitset<120> v) : steps(x), pos(p), mat(v) {}
        };

        auto cmp = [](const T& a, const T& b) {
            if( a.steps > b.steps ) {
                return true;
            } else if( a.steps == b.steps ) {
                if( a.pos < b.pos ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<T,vector<T>,decltype(cmp)> pq(cmp);

        unordered_set<bitset<120>> seen;

        bitset<120> v;
        for(int i = 0; i < n; ++i)
            v.set((s1[i] - 'a') * n + i);

        // BFS

        pq.push({0,0,v});
        seen.insert(v);
        while ( !pq.empty() ) {
            T t = pq.top();
            pq.pop();

            // cout << "t.s " << t.s << " t.pos " << t.pos << endl;

            if( t.pos == n )
                return t.steps;

            if( t.mat.test(t2[t.pos]) ) {
                pq.push({t.steps,t.pos+1,t.mat});
                continue;
            }

            // let us swap s[pos] with char s2[pos] found in s at
            // pos < x < n

            // int sidx = t.s[t.pos]-'a'; // cout << "sidx " << sidx << endl;
            int sidx = 0;
            for(; sidx < 6; ++sidx) {
                int idx = sidx * n + t.pos;
                if( t.mat.test(idx) )
                    break;
            }


            int tidx = t2[t.pos]/n; // cout << "tidx " << tidx << endl;
            for(int i = t.pos+1; i < n; ++i) {
                int k = tidx * n + i;
                if( t.mat.test(k) ) {
                    // swap
                    t.mat.flip(k);              // true -> false
                    t.mat.flip(sidx * n + i);   // false -> true
                    // t.s[i] = t.s[t.pos];
                    // t.s[t.pos] = s2[t.pos];

                    // cout << "t.s new " << t.s << endl;

                    if( !seen.count(t.mat) ) {
                        seen.insert(t.mat);
                        pq.push({t.steps+1,t.pos+1,t.mat});
                    }/* else {
                        cout << "seen" << endl;
                    }*/

                    // backtrack
                    // t.s[t.pos] = t.s[i];
                    // t.s[i] = s2[t.pos];
                    t.mat.flip(sidx * n + i);
                    t.mat.flip(k);
                }
            }

        }

        return -1; // satisfy compiler
    }
};
