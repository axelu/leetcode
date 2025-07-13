
// 1195. Fizz Buzz Multithreaded
// https://leetcode.com/problems/fizz-buzz-multithreaded/





class FizzBuzz {
private:
    int n;

    // mutex mask_mtx;
    // int mask;
    int i;

    mutex cv_m;
    // condition_variable cv;

    condition_variable cv_fizz,cv_buzz,cv_fizzbuzz,cv_printnunber;

public:
    FizzBuzz(int n) {
        this->n = n+1;

        // we don't know in which order our four functions will be called.
        // once all of them have been called though, we can print our sequence
        // mask = 0;
        i = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        /*
        mask_mtx.lock();
        // cout << "fizz called" << endl;
        mask |= 1;
        mask_mtx.unlock();
        */
        unique_lock lck(cv_m);
        while( i != n ) {
            while( i != n && ((i % 3) || !(i % 5)) ){
                cv_fizz.wait(lck);
            }
            bool printed = false;
            while( i != n && (!(i % 3) && (i % 5)) ) {
                printFizz();
                ++i;
                printed = true;
            }

            if( printed && i == n ) {
                // we need to tell the others that we are done
                // cv_fizz.notify_one();
                cv_buzz.notify_one();
                cv_fizzbuzz.notify_one();
                cv_printnunber.notify_one();
            }
            if( printed && i != n ) {
                // we need to tell the next one
                if( !(i % 3) && (i % 5 ) )
                    cv_fizz.notify_one();
                else if( (i % 3) && !(i % 5 ) )
                    cv_buzz.notify_one();
                else if( !(i % 3) && !(i % 5 ) )
                    cv_fizzbuzz.notify_one();
                else
                    cv_printnunber.notify_one();
            }
        }

        return;
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        /*
        mask_mtx.lock();
        // cout << "buzz called" << endl;
        mask |= 2;
        mask_mtx.unlock();
        */
        unique_lock lck(cv_m);
        while( i != n ) {
            while( i != n && (!(i % 3) || (i % 5)) ){
                cv_buzz.wait(lck);
            }
            bool printed = false;
            while( i != n && ((i % 3) && !(i % 5)) ) {
                printBuzz();
                ++i;
                printed = true;
            }

            if( printed && i == n ) {
                // we need to tell the others that we are done
                cv_fizz.notify_one();
                // cv_buzz.notify_one();
                cv_fizzbuzz.notify_one();
                cv_printnunber.notify_one();
            }
            if( printed && i != n ) {
                // we need to tell the next one
                if( !(i % 3) && (i % 5 ) )
                    cv_fizz.notify_one();
                else if( (i % 3) && !(i % 5 ) )
                    cv_buzz.notify_one();
                else if( !(i % 3) && !(i % 5 ) )
                    cv_fizzbuzz.notify_one();
                else
                    cv_printnunber.notify_one();
            }
        }

        return;
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        /*
        mask_mtx.lock();
        // cout << "fizzbuzz called" << endl;
        mask |= 4;
        mask_mtx.unlock();
        */
        unique_lock lck(cv_m);
        while( i != n ) {
            while( i != n && ((i % 3) || (i % 5)) ){
                cv_fizzbuzz.wait(lck);
            }
            bool printed = false;
            while( i != n && (!(i % 3) && !(i % 5)) ) {
                printFizzBuzz();
                ++i;
                printed = true;
            }

            if( printed && i == n ) {
                // we need to tell the others that we are done
                cv_fizz.notify_one();
                cv_buzz.notify_one();
                // cv_fizzbuzz.notify_one();
                cv_printnunber.notify_one();
            }
            if( printed && i != n ) {
                // we need to tell the next one
                if( !(i % 3) && (i % 5 ) )
                    cv_fizz.notify_one();
                else if( (i % 3) && !(i % 5 ) )
                    cv_buzz.notify_one();
                else if( !(i % 3) && !(i % 5 ) )
                    cv_fizzbuzz.notify_one();
                else
                    cv_printnunber.notify_one();
            }
        }

        return;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        /*
        mask_mtx.lock();
        // cout << "printNumber called" << endl;
        mask |= 8;
        mask_mtx.unlock();
        */
        unique_lock lck(cv_m);
        while( i != n ) {
            while( i != n && (!(i % 3) || !(i % 5)) ){
                cv_printnunber.wait(lck);
            }
            bool printed = false;
            while( i != n && ((i % 3) && (i % 5)) ) {
                printNumber(i);
                ++i;
                printed = true;
            }

            if( printed && i == n ) {
                // we need to tell the others that we are done
                cv_fizz.notify_one();
                cv_buzz.notify_one();
                cv_fizzbuzz.notify_one();
                // cv_printnunber.notify_one();
            }
            if( printed && i != n ) {
                // we need to tell the next one
                if( !(i % 3) && (i % 5 ) )
                    cv_fizz.notify_one();
                else if( (i % 3) && !(i % 5 ) )
                    cv_buzz.notify_one();
                else if( !(i % 3) && !(i % 5 ) )
                    cv_fizzbuzz.notify_one();
                else
                    cv_printnunber.notify_one();

            }
        }

        return;
    }
};
