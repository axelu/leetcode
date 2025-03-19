
-- 3415. Find Products with Three Consecutive Digits
-- https://leetcode.com/problems/find-products-with-three-consecutive-digits/




/* Write your T-SQL query statement below */

select
    product_id,
    [name]
from
    Products
where
    [name] like '%[^0-9][0-9][0-9][0-9][^0-9]%' or
    [name] like '[0-9][0-9][0-9][^0-9]%' or
    [name] like '%[^0-9][0-9][0-9][0-9]' or
    [name] like '[0-9][0-9][0-9]'
order by
    product_id
