
// 2129. Capitalize the Title
// https://leetcode.com/problems/capitalize-the-title/



class Solution {
private:
    void capitalize(string& title, int i, stack<char>& stck) {
        int l = stck.size();
        int j = i+1;
        if( l > 2 ) {
            if( !isupper(stck.top()) )
                title[j] -= 32;
            stck.pop();
            ++j;
            while(!stck.empty()) {
                if( isupper(stck.top()) )
                    title[j] += 32;
                stck.pop();
                ++j;
            }
        } else {
            if( isupper(stck.top()) )
                title[j] += 32;
            stck.pop();
            ++j;
            if(!stck.empty()) {
                if( isupper(stck.top()) )
                    title[j] += 32;
                stck.pop();
            }
        }
    }

public:
    string capitalizeTitle(string title) {
        stack<char> stck;
        char c;
        for(int i = title.size()-1; i >= 0; --i) {
            c = title[i];
            if( c != ' ' ) {
                stck.push(c);
                continue;
            }
            capitalize(title,i,stck);

        }
        // finish up
        capitalize(title,-1,stck);

        return title;
    }
};
