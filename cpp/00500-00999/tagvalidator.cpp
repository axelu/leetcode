
// 591. Tag Validator
// https://leetcode.com/problems/tag-validator/






class Solution {
public:
    bool isValid(string code) {
        // code will not have leading or trailing spaces
        int n = code.size(); // 1 <= code.length <= 500

        // minimum valid code
        // <A></A>

        if( n < 7 || code[0] != '<' || code[n-1] != '>' )
            return false;

        int mode = 0; // 0 not inside cdata, 1 inside cdata

        stack<string> stck;                     // contains expected closing tag
        char c;
        string t;
        string cdopen = "[CDATA[";
        int i;
        for(int j = 0; j < code.size(); ++j) {  // right index
            /*
            cout << "index j " << j << " " << code[j] << " ";
            cout << "stck size " << stck.size() << " mode " << mode << endl;
            */

            // at any point a tag has to be open
            if( j > 0 && stck.empty() )
                return false;

            c = code[j];

            if( mode == 0 ) {
                if( c == '<' ) {
                    // at minimum we need to have another 3 chars
                    // </A>
                    if( j > n-4 )
                        return false;

                    if( code[j+1] == '/' ) {
                        // closing tag
                        if( stck.empty() )
                            return false;
                        t = stck.top();
                        stck.pop();
                        j += 2;
                        for(int k = 0; k < t.size(); ++k) {
                            if( t[k] != code[j] )
                                return false;
                            ++j;
                        }
                    } else if( code[j+1] == '!' ) {
                        // begin of cdata ?
                        // at minimum we need to have another 15 chars
                        // <![CDATA[]]></A>
                        if( j > n-16 )
                            return false;
                        j += 2;
                        for(int k = 0; k < 7; ++k) {
                            if( cdopen[k] != code[j] )
                                return false;
                            ++j;
                        }
                        --j; // the loop will advance j
                        mode = 1;
                    } else if( isupper(code[j+1]) ) {
                        // opening tag
                        // at minimum we need to have another 6 chars
                        // <A></A>
                        if( j > n-7 )
                            return false;

                        ++j;
                        // advance till we find >
                        t = "";
                        i = 0;
                        while( code[j] != '>' ) {
                            if( ++i > 9 )
                                return false;
                            if( !isupper(code[j]) )
                                return false;
                            t += code[j];
                            ++j;
                        }
                        stck.push(t);

                    } else {
                        return false;
                    }
                }
                // here we would be inside tag content

            } else {
                // inside cdata
                if( c == ']' ) {
                    // is this marking the end of cdata?
                    // at minimum we need to have another 6 chars
                    // ]]></A>
                    if( j > n-7 )
                        return false;
                    if( code[j+1] == ']' && code[j+2] == '>' ) {
                        mode = 0;
                        j += 2;
                    }
                }
            }

        }

        // unclosed tag
        if( !stck.empty() )
            return false;

        return true;
    }
};
