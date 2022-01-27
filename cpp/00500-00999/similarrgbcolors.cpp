
// 800. Similar RGB Color
// https://leetcode.com/problems/similar-rgb-color/



/* hex dec
 * 00    0
 * 11   17
 * 22   34
 * 33   51
 * 44   68
 * 55   85
 * 66  102
 * 77  119
 * 88  136
 * 99  153
 * aa  170
 * bb  187
 * cc  204
 * dd  221
 * ee  238
 * ff  255
*/
class Solution {
private:
    // hex to decimal
    int h2d(string s) {
        int ret = isdigit(s[1]) ? (int)s[1]-48 : (int)s[1]-87;
        ret += isdigit(s[0]) ? ((int)s[0]-48)*16 : ((int)s[0]-87)*16;
        return ret;
    }

    // decimal to hex
    string d2h(int i) {
        if( i == 0 ) return "00";
        string r = "";
        int rem;
        while( i > 0 ) {
            rem = i % 16;
            if( rem > 9 )
                r.insert(r.begin(),'W' + rem);
            else
                r = to_string(rem) + r;
            i /= 16;
        }
        return r;
    }

public:
    string similarRGB(string color) {
        int ir = h2d(color.substr(1,2));
        int ig = h2d(color.substr(3,2));
        int ib = h2d(color.substr(5,2));

        // brute force
        // 16*16*16 = 4096 tries
        int mx = INT_MIN;
        int dr,dg,db,sr,sg,sb;
        for(int i = 0; i <= 255; i += 17) {
            dr = -((ir-i)*(ir-i));
            for(int j = 0; j <= 255; j += 17) {
                dg = (ig-j)*(ig-j);
                for(int k = 0; k <= 255; k += 17) {
                    db = (ib-k)*(ib-k);
                    if( dr-dg-db > mx ) {
                        mx = dr-dg-db;
                        sr = i;
                        sg = j;
                        sb = k;
                    }
                }
            }
        }
        return "#" + d2h(sr) + d2h(sg) + d2h(sb);
    }
};
