
// 1625. Lexicographically Smallest String After Applying Operations
// https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/


class Solution {
private:
    int A,B;
    size_t N;
    string r;
    unordered_set<string> seen;

    string opA(string s) {
        auto it = begin(s);
        for(int i = 1; i < N; i += 2)
            *(it+i) = 48 + (*(it+i) - 48 + A) % 10;
        return s;
    }

    string opB(string s) {
        rotate(s.rbegin(), s.rbegin() + B, s.rend());
        return s;
    }

    void dfs(string s) {
        if( seen.find(s) != seen.end() ) return;

        if( s < r ) r = s;
        seen.insert(s);

        // operation A
        dfs(opA(s));

        // operation B
        dfs(opB(s));
    }



public:
    string findLexSmallestString(string s, int a, int b) {
        N = s.size();
        A = a;
        B = b;

        r = s;
        dfs(s);

        return r;
    }
};
