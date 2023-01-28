
-- 1867. Orders With Maximum Quantity Above Average
-- https://leetcode.com/problems/orders-with-maximum-quantity-above-average/


/* Write your T-SQL query statement below */

with cte (order_id,avgqoo,maxqoo)
as
(
    select
      o.order_id,
      cast(sum(o.quantity) as decimal)/count(*) as avgqoo,
      max(o.quantity) as maxqoo
    from
      ordersdetails o
    group by
      o.order_id
)
select
  order_id
from
  cte
where
  maxqoo > (select max(avgqoo) from cte)
