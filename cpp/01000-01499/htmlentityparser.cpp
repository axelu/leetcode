
// 1410. HTML Entity Parser
// https://leetcode.com/problems/html-entity-parser/





class Solution {
public:
    string entityParser(string text) {

        unordered_map<string,string> entities;
        entities.insert({"&quot;","\""});
        entities.insert({"&apos;","'"});
        entities.insert({"&amp;","&"});
        entities.insert({"&gt;",">"});
        entities.insert({"&lt;","<"});
        entities.insert({"&frasl;","/"});

        string ans = "";

        int mode = 0;   // 0 write, 1 collect
        int i = 0;      // left index
        char c;
        string entity = "";
        unordered_map<string,string>::iterator f;
        for(int j = 0; j < text.size(); ++j) {  // right index
            c = text[j];
            if( mode == 0 & c != '&' ) {
                ans += c;
            } else {
                if( mode == 0 ) {
                    entity = "&";
                    i = j;
                    mode = 1;
                } else {
                    entity += c;
                    if( c == ';' ) {
                        f = entities.find(entity);
                        if( f != entities.end() )
                            ans += f->second;
                        else
                            ans += entity;
                        mode = 0;
                    } else if( c == '&' ) {
                        entity.pop_back();
                        ans += entity;
                        entity = "&";
                        i = j;
                    }
                }
            }
        }
        // finish up - we should really not hit this condition
        if( mode == 1 )
            ans += entity;

        return ans;
    }
};
