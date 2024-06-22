
// 2777. Date Range Generator
// https://leetcode.com/problems/date-range-generator/





/**
 * @param {string} start
 * @param {string} end
 * @param {number} step
 * @yields {string}
 */
var dateRangeGenerator = function* (start, end, step) {
    // new Date(year, monthIndex, day)

    const dt_start = new Date(start);
    const dt_end = new Date(end);
    const msday = 86400000;

    let f = 0;
    while ( dt_start.getTime() + (f * step * msday) <= dt_end.getTime() ) {
        const dt = new Date(dt_start.getTime() + (f * step * msday));
        let [str_month, day, year] = [
            dt.getMonth(),
            dt.getDate(),
            dt.getFullYear(),
        ];
        let month = parseInt(str_month) + 1;
        if( month < 10)
            str_month = '0' + month;
        else
            str_month = month;
        if( day < 10 )
            day = '0' + day;
        yield year + '-' + str_month + '-' + day;
        ++f;
    }

};

/**
 * const g = dateRangeGenerator('2023-04-01', '2023-04-04', 1);
 * g.next().value; // '2023-04-01'
 * g.next().value; // '2023-04-02'
 * g.next().value; // '2023-04-03'
 * g.next().value; // '2023-04-04'
 * g.next().done; // true
 */
