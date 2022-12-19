
-- 1484. Group Sold Products By The Date
-- https://leetcode.com/problems/group-sold-products-by-the-date/



/* Write your T-SQL query statement below */

select
  sell_date,
  count(distinct product) as num_sold,
  string_agg(product,',') within group (order by product) as products
from
  ( select distinct sell_date,product from activities ) a
group by sell_date
order by sell_date
