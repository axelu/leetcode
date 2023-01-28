
-- 2084. Drop Type 1 Orders for Customers With Type 0 Orders
-- https://leetcode.com/problems/drop-type-1-orders-for-customers-with-type-0-orders/



/* Write your T-SQL query statement below */

select
  o.order_id
  ,o.customer_id
  ,o.order_type
from
  orders as o
where
  o.order_type <> 1
  or (order_type = 1 and customer_id not in (
      select distinct customer_id from orders where order_type = 0
    )
  )

