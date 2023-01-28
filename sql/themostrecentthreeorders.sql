
-- 1532. The Most Recent Three Orders
-- https://leetcode.com/problems/the-most-recent-three-orders/



/* Write your T-SQL query statement below */

with o
as
(
select
  customer_id,
  order_id,
  order_date,
  rank() over(partition by customer_id order by order_date desc) as rnk
from
  orders
)
select
  c.name as customer_name,
  o.customer_id,
  o.order_id,
  o.order_date
from
  o join customers c on o.customer_id = c.customer_id
where
  o.rnk < 4
order by
  c.name,c.customer_id,o.order_date desc
