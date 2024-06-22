
// 2019. The Score of Students Solving Math Expression
// https://leetcode.com/problems/the-score-of-students-solving-math-expression/





class Solution {
private:
    int mem[31][31];

    int solve(string& s, int b, int e) {
        if( mem[b][e] != -1 )
            return mem[b][e];

        stack<int> stck;
        stck.push(s[b]-'0');
        for(int i = b+2; i <= e; i += 2) {
            if( s[i-1] == '*' ) {
                int a = stck.top();
                stck.pop();
                stck.push(a * (s[i]-'0'));
            } else {
                stck.push(s[i]-'0');
            }
        }

        int ret = 0;
        while( !stck.empty() ) {
            ret += stck.top();
            stck.pop();
        }

        return mem[b][e] = ret;
    }

    unordered_set<int> mem1[31][31];

    unordered_set<int> rec(string& s, int b, int e) {
        // cout << "rec b " << b << " e " << e << endl;
        if( b == e )
            return {s[e]-'0'};

        if( e - b + 1 == 3 ) {
            int t = s[b+1] == '*' ? (s[b]-'0') * (s[e]-'0') : (s[b]-'0') + (s[e]-'0');
            return {t};
        }

        if( !mem1[b][e].empty() )
            return mem1[b][e];

        unordered_set<int> ret;
        for(int i = b; i <= e; i += 2) {
            if( i < e ) {
                auto a = rec(s,b,i);
                auto b = rec(s,i+2,e);
                if( s[i+1] == '*' ) {
                    for(int x: a)
                        for(int y: b) {
                            int t = x*y;
                            if( t <= 1000 ) // based on constraint given in problem
                                ret.insert(x*y);
                        }

                } else { // s[i+1] == '+'
                    for(int x: a)
                        for(int y: b) {
                            int t = x+y;
                            if( t <= 1000 ) // based on constraint given in problem
                                ret.insert(x+y);
                        }
                }
            }
        }

        return mem1[b][e] = ret;
    }

public:
    int scoreOfStudents(string& s, vector<int>& answers) {
        int n = s.size(); // 3 <= s.length <= 31
        // worst case s.length == 31, s is 9*9*9*9...*9 -> correct ans =    1853020188851841 (16 9s and 15 *)
        //                                                      LONG_MAX 9223372036854775807
        // BUT per constraint:
        // Test data are generated such that the correct answer of the expression is in the range of [0, 1000]

        memset(mem,-1,sizeof mem);
        int correct_answer = solve(s,0,n-1);
        unordered_set<int> possible_answers = rec(s,0,n-1);
        // debug
        /*
        cout << "correct answer " << correct_answer << endl;
        cout << possible_answers.size() << " possible answers ";
        for(int x: possible_answers)
            cout << x << " ";
        cout << endl;
        */

        int ans = 0;
        for(int res: answers) {
            if( res == correct_answer )
                ans += 5;
            else if( possible_answers.find(res) != possible_answers.end() )
                ans += 2;
        }

        return ans;
    }
};
