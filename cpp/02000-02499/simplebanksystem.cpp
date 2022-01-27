
// 2043. Simple Bank System
// https://leetcode.com/problems/simple-bank-system/



class Bank {
private:
    int n;
    long long * _balance;

    bool isValidAccount(int account) {
        if( account < 1 || account > n )
            return false;
        return true;
    }
public:
    Bank(vector<long long>& balance) {
        n = balance.size();
        _balance = balance.data();
    }

    bool transfer(int account1, int account2, long long money) {
        if( !isValidAccount(account1) || !isValidAccount(account2) )
            return false;
        if( _balance[account1-1] < money )
            return false;

        _balance[account1-1] -= money;
        _balance[account2-1] += money;

        return true;
    }

    bool deposit(int account, long long money) {
        if( !isValidAccount(account) )
            return false;

        _balance[account-1] += money;

        return true;
    }

    bool withdraw(int account, long long money) {
        if( !isValidAccount(account) )
            return false;
        if( _balance[account-1] < money )
            return false;

        _balance[account-1] -= money;

        return true;
    }
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */
