
// 636. Exclusive Time of Functions
// https://leetcode.com/problems/exclusive-time-of-functions/



class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> ans(n,0);

        stack<array<int,2>> stck; // function id, start time

        // before we put something onto the stack,
        // we capture the runtime of top of stack function;
        // if we pop something from the stack,
        // we update the start time of what is then on top of stack

        for(string& s: logs) {
            int separator_idx = s.find(':');
            int function_id = stoi(s.substr(0,separator_idx));
            char event = s[separator_idx+1]; // s start, e end
            separator_idx = s.find(':',separator_idx+1);
            int time = stoi(s.substr(separator_idx+1));

            if( event == 's' ) { // start
                if( !stck.empty() )
                    ans[stck.top()[0]] += time - stck.top()[1];
                stck.push({function_id,time});

            } else { // event == 'e' end
                // function that is ending must be on the stack
                ans[stck.top()[0]] += time - stck.top()[1] + 1;
                stck.pop();
                if( !stck.empty() )
                    stck.top()[1] = time + 1;
            }
        }

        return ans;
    }
};
