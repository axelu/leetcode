
-- 1082. Sales Analysis I
-- https://leetcode.com/problems/sales-analysis-i/



/* Write your T-SQL query statement below */

select
  seller_id
from (
  select
    seller_id,
    rank() over (order by sum(price) desc) as rnk
  from sales
  group by seller_id
) s
where rnk = 1
