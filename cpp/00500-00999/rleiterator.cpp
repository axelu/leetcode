
// 900. RLE Iterator
// https://leetcode.com/problems/rle-iterator/





class RLEIterator {
private:
    vector<int> * pEncoding;
    long sz,i,s,e,pos;

public:
    RLEIterator(vector<int>& encoding) {
        pEncoding = &encoding;
        sz  = encoding.size();

        i   = 0;          // pos in encoding
        // handle 0's
        while( encoding[i] == 0 && i < sz )
            i += 2;
        s   = 0;                         // current value in sequence start index
        e   = i < sz ? encoding[i] : -1; // next value in sequence start index

        pos = -1;         // pos in sequence
    }


    int next(int n) {
        // cout << "next i " << i << " s " << s << " e " << e << " pos " << pos << endl;
        if( i == sz )
            return -1;

        pos += (long)n;
        // cout << "  new pos " << pos << endl;
        if( s <= pos && pos < e )
            return pEncoding->at(i+1);

        // advance in encoding if needed
        while( i+2 < sz ) {
            i += 2;
            s = e;
            e += (long)pEncoding->at(i);
            if(s <= pos && pos < e )
                break;
        }
        // cout << "  new i " << i << " s " << s << " e " << e << endl;
        if( i == sz-2 && e <= pos )
            return -1;
        else
            return pEncoding->at(i+1);
    }
};

/**
 * Your RLEIterator object will be instantiated and called as such:
 * RLEIterator* obj = new RLEIterator(encoding);
 * int param_1 = obj->next(n);
 */
