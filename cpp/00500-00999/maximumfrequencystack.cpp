
// 895. Maximum Frequency Stack
// https://leetcode.com/problems/maximum-frequency-stack/
// day 28 February 2021 challenge
// https://leetcode.com/explore/featured/card/february-leetcoding-challenge-2021/587/week-4-february-22nd-february-28th/3655/



class FreqStack {
private:
    unordered_map<int,int> o; // key,frequency
    map<int,stack<int>> fl; // frequencyList, basically stack by frequency

public:
    FreqStack() {
    }

    void push(int x) {
        // locate x and determine x's current frequency
        unordered_map<int,int>::iterator f = o.find(x);
        if( f == o.end() ) {
            // we have not seen x before
            // add x to the stack of frequency 1
            fl[1].push(x);
            // update our key,frequency map
            o.insert({x,1});
        } else {
            // add x to the stack current frequency+1
            int currFrequency = f->second;
            fl[currFrequency+1].push(x);
            // update our key,frequency map
            // increment the frequency of x
            ++f->second;
        }
    }

    int pop() {
        // return the top element of the stack with the highest frequency
        int ans = fl.rbegin()->second.top();
        fl.rbegin()->second.pop();
        int currFrequency = fl.rbegin()->first;
        if( fl.rbegin()->second.empty() )
            fl.erase(currFrequency);
        // update our key,frequency map
        if( currFrequency == 1 ) {
            o.erase(ans);
        } else {
            --o[ans];
        }
        return ans;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 */
