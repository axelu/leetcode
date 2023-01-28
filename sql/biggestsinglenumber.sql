
-- 619. Biggest Single Number
-- https://leetcode.com/problems/biggest-single-number/




/* Write your T-SQL query statement below */


with t as
(
    select
        num
        ,count(num) as cnt
    from MyNumbers
    group by num
)
select
    max(num) as num
from t
where cnt = 1
