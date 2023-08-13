
// 2758. Next Day
// https://leetcode.com/problems/next-day/



Date.prototype.nextDay = function() {

    let ms = this.getTime();
    ms += 86400000; // 60*60*24*1000;

    let nd = new Date(ms);
    let y = nd.getFullYear();
    let m = nd.getMonth() + 1;
    if( m < 10 )
        m = "0" + m;
    let d = nd.getDate();
    if( d < 10 )
        d = "0" + d;

    return y + "-" + m + "-" + d;
}

/**
 * const date = new Date("2014-06-20");
 * date.nextDay(); // "2014-06-21"
 */
