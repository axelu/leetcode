
// 984. String Without AAA or BBB
// https://leetcode.com/problems/string-without-aaa-or-bbb/



class Solution {
public:
    string strWithout3a3b(int a, int b) {
        string s = "";

        string chra = "a";
        string chrb = "b";
        if( b > a ) {
            int t = a;
            a = b;
            b = t;
            chra = "b";
            chrb = "a";
        }

        while( a+b > 0 ) {

           if( a > b ) {
               if( a >= 2 ) {
                    s += chra + chra;
                    a -= 2;
                    if( b > 0 ) {
                        s += chrb;
                        --b;
                    }
               } else {
                   s += chra;
                   --a;
               }

           } else { // a == b
               if( a >= 2 ) {
                    s += chra + chra + chrb + chrb;
                    a -= 2;
                    b -= 2;
               } else {
                    s += chra + chrb;
                    --a;
                    --b;
               }
           }
        }

        return s;
    }
};
