
// 1215. Stepping Numbers
// https://leetcode.com/problems/stepping-numbers/



class Solution {
public:
    vector<int> countSteppingNumbers(int low, int high) {

        set<long> t;

        // BFS
        queue<string> q;
        q.push("0");
        q.push("1");
        q.push("2");
        q.push("3");
        q.push("4");
        q.push("5");
        q.push("6");
        q.push("7");
        q.push("8");
        q.push("9");
        while( !q.empty() ) {
            string a = q.front();
            q.pop();

            int a0 = a[0] - 48;

            if( a0 != 0 ) {
                long x = stol(a);
                if( x >= low && x <= high )
                    t.insert(x);
                if( x >= high )
                    continue;
            }

            string a_new;
            // add to the left
            // +1
            if( a0 < 9 ) {
                switch(a0) {
                    case 0 :
                        a_new = "1" + a;
                        break;
                    case 1 :
                        a_new = "2" + a;
                        break;
                    case 2 :
                        a_new = "3" + a;
                        break;
                    case 3 :
                        a_new = "4" + a;
                        break;
                    case 4 :
                        a_new = "5" + a;
                        break;
                    case 5 :
                        a_new = "6" + a;
                        break;
                    case 6 :
                        a_new = "7" + a;
                        break;
                    case 7 :
                        a_new = "8" + a;
                        break;
                    default :
                        a_new = "9" + a;
                }
                q.push(a_new);
            }
            // -1
            if( a0 > 0 ) {
                switch(a0) {
                    case 1 :
                        a_new = "0" + a;
                        break;
                    case 2 :
                        a_new = "1" + a;
                        break;
                    case 3 :
                        a_new = "2" + a;
                        break;
                    case 4 :
                        a_new = "3" + a;
                        break;
                    case 5 :
                        a_new = "4" + a;
                        break;
                    case 6 :
                        a_new = "5" + a;
                        break;
                    case 7 :
                        a_new = "6" + a;
                        break;
                    case 8 :
                        a_new = "7" + a;
                        break;
                    default :
                        a_new = "8" + a;
                }
                q.push(a_new);
            }
        }

        // Note: account for low = 0

        int n = low == 0 ? t.size()+1 : t.size();
        if( n == 0 )
            return {};
        vector<int> ans(n);
        int i = 0;
        if( low == 0 ) {
            ans[0] = 0;
            ++i;
        }
        for(int x : t) {
            ans[i] = x;
            ++i;
        }

        return ans;
    }
};
