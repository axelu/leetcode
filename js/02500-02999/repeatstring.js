
// 2796. Repeat String
// https://leetcode.com/problems/repeat-string/





String.prototype.replicate = function(times) {
    let s = "";
    while(times--)
        s += this.toString();
    return s;
}
