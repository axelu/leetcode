
-- 3465. Find Products with Valid Serial Numbers
-- https://leetcode.com/problems/find-products-with-valid-serial-numbers/






/* Write your T-SQL query statement below */

select
    product_id,
    product_name,
    [description]
from
    products
where
    [description] is not NULL and
    len([description]) >= 11 and
    charindex('SN', [description]) > 0 and
    charindex('-', [description]) > 0 and
    (
    [description] like 'SN[0-9][0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]' or
    [description] like '% SN[0-9][0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]' or
    [description] like 'SN[0-9][0-9][0-9][0-9]-[0-9][0-9][0-9][0-9] %' or
    [description] like '% SN[0-9][0-9][0-9][0-9]-[0-9][0-9][0-9][0-9] %'
    )
order by
    product_id
