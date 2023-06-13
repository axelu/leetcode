
// 2241. Design an ATM Machine
// https://leetcode.com/problems/design-an-atm-machine/


/* vector<int> -> { $20 notes, $50 notes, $100 notes, $200 notes, $500 notes}
 *
 */
class ATM {
private:

    long denominations[5] = {20,50,100,200,500};

    vector<long> _banknotesCount;

    bool _withdraw(int amount, int i, vector<int>& notes ) {
        if( i == -1 )
            return amount == 0;

        // we always must to use the largest note possible,
        // if we have any

        if( amount >= denominations[i] && _banknotesCount[i] > 0 ) {

            long t = min(_banknotesCount[i], amount / denominations[i]);
            amount -= t * denominations[i];
            _banknotesCount[i] -= t;
            notes[i] += t;
        }

        bool f = _withdraw(amount,i-1,notes);
        if( !f ) {
            // backtrack
            _banknotesCount[i] += notes[i];
        }

        return f;
    }

public:
    ATM() {
        _banknotesCount.assign(5,0);
    }

    void deposit(vector<int> banknotesCount) {
        for(int i = 0; i < 5; ++i)
           _banknotesCount[i] += banknotesCount[i];

        return;
    }

    vector<int> withdraw(int amount) {
        vector<int> notes(5,0);
        if( _withdraw(amount,4,notes) )
            return notes;

        return {-1};
    }
};

/**
 * Your ATM object will be instantiated and called as such:
 * ATM* obj = new ATM();
 * obj->deposit(banknotesCount);
 * vector<int> param_2 = obj->withdraw(amount);
 */
