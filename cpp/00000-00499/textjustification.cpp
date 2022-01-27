
// 68. Text Justification
// https://leetcode.com/problems/text-justification/



class Solution {
private:
    string fullJustify(queue<string>& q, int o, int maxWidth) {
        string line;
        if( q.size() == 1 ) {
            line = q.front();
            q.pop();
            // right pad respectively left justify to max length
            while( line.size() < maxWidth )
                line += ' ';
        } else if( q.size() == 2 ) {
            line = q.front();
            q.pop();
            for(int k = 0; k < maxWidth-o; ++k)
                line += ' ';
            line += q.front();
            q.pop();
        } else {
            // q.size() > 2
            int t = (maxWidth-o)/(q.size()-1);
            int rem = (maxWidth-o)%(q.size()-1);
            line = q.front();
            q.pop();
            while( !q.empty() ) {
                for(int k = 0; k < t; ++k)
                    line += ' ';
                if( rem > 0 )
                    line += ' ';
                --rem;
                line += q.front();
                q.pop();
            }
        }
        return line;
    }

    string leftJustify(queue<string>& q, int o, int maxWidth) {
        string line = q.front();
        q.pop();
        while( !q.empty() ) {
            line += ' ';
            line += q.front();
            q.pop();
        }
        // right pad respectively left justify to max length
        while( line.size() < maxWidth )
            line += ' ';
        return line;
    }

public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int n = words.size();
        if( n == 1 ) {
            // right pad respectively left justify to max length
            while( words[0].size() < maxWidth )
                words[0] += ' ';
            return words;
        }

        vector<string> ans;
        int l = 0; // length with one separating space
        int o = 0; // length without spaces
        queue<string> q;
        for(int i = 0; i < n; ++i) {
            // can we add the current word to line w/o exceed maxWidth
            // account for min of one space to seperate current word from prior word
            if( q.size() == 0 ) {
                l = words[i].size();
                o = words[i].size();
                q.push(words[i]);
            } else if( l + 1 + words[i].size() <= maxWidth ) {
                l += 1 + words[i].size();
                o += words[i].size();
                q.push(words[i]);
            } else {
                ans.push_back(fullJustify(q,o,maxWidth));
                l = words[i].size();
                o = words[i].size();
                q.push(words[i]);
            }
        }
        //finish up, last line left justified
        ans.push_back(leftJustify(q,o,maxWidth));

        return ans;
    }
};
