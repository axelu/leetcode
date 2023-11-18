
// 972. Equal Rational Numbers
// https://leetcode.com/problems/equal-rational-numbers/




// see https://en.wikipedia.org/wiki/0.999...


class Solution {
private:
    int get_integer_part(string rn) {
        int dotpos = rn.find('.');
        if( dotpos == string::npos )
            return stoi(rn);
        else
            return stoi(rn.substr(0,dotpos));
    }

    string get_decimal_part(string rn) {
        // return NNNNNNNN
        int n = rn.size();
        int dotpos = rn.find('.');
        if( dotpos == string::npos || dotpos == n-1 )
            return "00000000";

        int reppos = rn.find('(');
        if( reppos == string::npos ) {
            // we have a non-repeating decimal part but
            // no repeating part
            string t = rn.substr(dotpos+1);
            // add trailing zeros up to a length of 8
            while( t.size() < 8 )
                t += '0';
            return t;
        }

        // we have a non-repeating decimal part (maybe) and
        // we have a repeating decimal part
        string t = rn.substr(dotpos+1,reppos - (dotpos+1));
        string r = rn.substr(reppos+1,(n-1) - (reppos+1));
        for(int i = 0; i < 8; ++i)
            r += r;
        string tr = t + r;
        return tr.substr(0,8);
    }

    void adjust9999(int& integerpart, string& decimalpart) {
        if( decimalpart.substr(4) != "9999" )
            return;

        decimalpart = decimalpart.substr(0,4) + "0000";

        int carry = 1;
        int i = 3;
        while( i >= 0 && carry ) {
            if( decimalpart[i] == '9' ) {
                decimalpart[i] = '0';
            } else {
                decimalpart[i] = ++decimalpart[i];
                carry = 0;
            }
            --i;
        }

        if( carry )
            ++integerpart;

        return;
    }

public:
    bool isRationalEqual(string s, string t) {

        int s_integerpart = get_integer_part(s);
        string s_decimalpart = get_decimal_part(s);
        //cout << "s int " << s_integerpart << " dec " << s_decimalpart << endl;
        adjust9999(s_integerpart,s_decimalpart);
        //cout << "s int " << s_integerpart << " dec " << s_decimalpart << " after adjustment" << endl;

        int t_integerpart = get_integer_part(t);
        string t_decimalpart = get_decimal_part(t);
        //cout << "t int " << t_integerpart << " dec " << t_decimalpart << endl;
        adjust9999(t_integerpart,t_decimalpart);
        //cout << "t int " << t_integerpart << " dec " << t_decimalpart << " after adjustment" << endl;

        return s_integerpart == t_integerpart && s_decimalpart == t_decimalpart;
    }
};
