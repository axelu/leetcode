
-- 1549. The Most Recent Orders for Each Product
-- https://leetcode.com/problems/the-most-recent-orders-for-each-product/




/* Write your T-SQL query statement below */

with cte
as
(
select
  order_id,
  order_date,
  product_id,
  rank() over(partition by product_id order by order_date desc) as rnk
from
  orders
)
select
  p.product_name,
  cte.product_id,
  cte.order_id,
  cte.order_date
from
  cte join products p on cte.product_id = p.product_id
where
  cte.rnk = 1
order by
  p.product_name, cte.product_id, cte.order_id
