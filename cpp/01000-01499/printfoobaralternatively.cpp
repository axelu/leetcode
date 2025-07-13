
// 1115. Print FooBar Alternately
// https://leetcode.com/problems/print-foobar-alternately/






// either foo or bar gets called 1st
// we need to run printFoo and printBar from the respective threads
// if foo gets called, run printFoo once, then wait till bar wakes us
// if bar gets called,
//    either wait if foo wasn't called yet OR
//    run printBar
//    then wait till foo wakes us up
// repeat



class FooBar {
private:
    int n;
    int i;
    mutex cv_m;
    condition_variable cv_foo,cv_bar;


public:
    FooBar(int n) {
        this->n = n * 2;
        i = 1;
    }

    void foo(function<void()> printFoo) {
        unique_lock lck(cv_m);
        while( i != n ) {
            if( i == 1 || i > 2 ) {
        	    printFoo();
                ++i;
            }
            cv_bar.notify_one();
            if( i < n )
                cv_foo.wait(lck);
        }
        return;
    }

    void bar(function<void()> printBar) {
        unique_lock lck(cv_m);
        while( i <= n ) {
            if( i > 1 ) {
        	    printBar();
                ++i;
            }
            cv_foo.notify_one();
            if( i < n )
                cv_bar.wait(lck);
        }
        return;
    }
};
