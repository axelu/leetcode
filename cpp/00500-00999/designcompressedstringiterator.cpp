
// 604. Design Compressed String Iterator
// https://leetcode.com/problems/design-compressed-string-iterator/



class StringIterator {
private:
    const char* s;  // compressed string
    int N;          // length of compressed string;
    int i;          // current position in compressed string
    char currChar;
    int n;          // count of current char
    int j;          // nbr of times we handed out the current char

    void setCurrChar() {
        string cnt = "";
        currChar = s[i];
        n = 0;
        ++i;
        for(; i < N; ++i) {
            if( isdigit(s[i]) ) {
                cnt += s[i];
                continue;
            }
            break;
        }
        n = !cnt.empty() ? stoi(cnt) : 0;
        j = 0;
    }

public:
    StringIterator(string& compressedString) {
        N = compressedString.size(); // 1 <= compressedString.length <= 1000
                                     // how could it be 1, when the constraint is:
                                     //   each letter followed by a positive integer?
        i = 0;
        n = 0;
        j = 0;
        if( N == 0 ) return;
        s = compressedString.c_str();
        setCurrChar();
    }

    char next() {
        if( j == n && i >= N ) return ' ';
        char c = currChar;
        ++j;
        if( n == j ) setCurrChar();
        return c;
    }

    bool hasNext() {
        if( j == n &&  i >= N ) return false;
        return true;
    }
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator* obj = new StringIterator(compressedString);
 * char param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
