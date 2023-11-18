
// 2296. Design a Text Editor
// https://leetcode.com/problems/design-a-text-editor/





class TextEditor {
private:
    int bufLength;
    int textLength;
    int cursorPosition;
    string buf;

    void printState() {
        cout << buf << " bufLength " << bufLength << " textLength " << textLength << " cursor " << cursorPosition << endl;
    }

    string ret() {
        if( cursorPosition == 0 ) {
            return "";
        } else if( cursorPosition >= 10 ) {
            return buf.substr(cursorPosition-10,10);
        } else {
            return buf.substr(0,cursorPosition);
        }
    }

public:
    TextEditor() {
        bufLength = 0;
        textLength = 0;
        cursorPosition = 0;
        buf = "";
    }

    void addText(string text) {
        //cout << "addText " << text << endl;
        int t_sz = text.size();

        if( cursorPosition == textLength ) {
            // the cursor is at the end of the current text,
            // so we can add the new text
            int i = 0; // position in text to be added
            for(; i < t_sz; ++i) {
                if( bufLength == textLength ) {
                    break;
                }
                buf[cursorPosition] = text[i];
                ++cursorPosition;
                ++textLength;
            }
            if( i < t_sz ) {
                buf.append(text,i,t_sz-i);
                bufLength = textLength = cursorPosition = buf.size();
            }

        } else {
            // the cursor is somewhere in the current text (including
            // potentially at the very beginning)

            buf.insert(cursorPosition,text);
            cursorPosition += t_sz;
            textLength += t_sz;
            bufLength = buf.size();
        }

        //printState();

        return;
    }

    int deleteText(int k) {
        //cout << "deleteText " << k << endl;
        if( k > cursorPosition ) {
            int t = cursorPosition;
            buf.erase(0,t);
            cursorPosition = 0;
            textLength -= t;
            bufLength = buf.size();
            //printState();
            return t;

        } else {
            cursorPosition -= k;
            buf.erase(cursorPosition,k);
            textLength -= k;
            bufLength = buf.size();
            //printState();
            return k;
        }
    }

    string cursorLeft(int k) {
        //cout << "cursorLeft " << k << endl;
        cursorPosition = max(0, cursorPosition - k);
        //printState();
        return ret();
    }

    string cursorRight(int k) {
        //cout << "cursorRight " << k << endl;
        cursorPosition = min(textLength, cursorPosition + k);
        //printState();
        return ret();
    }
};

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */
