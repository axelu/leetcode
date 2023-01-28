
-- 1174. Immediate Food Delivery II
-- https://leetcode.com/problems/immediate-food-delivery-ii/



/* Write your T-SQL query statement below */

with a
as
(
select
  delivery_id,
  customer_id,
  order_date,
  customer_pref_delivery_date
from 
  (
    select
      delivery_id,
      customer_id,
      order_date,
      customer_pref_delivery_date,
      rank() over(partition by customer_id order by order_date) as rnk
    from
      delivery
  ) t
where
  rnk = 1
)
select 
  round(
    (select count(*) from a where order_date = customer_pref_delivery_date) * 100.0 / 
      (select count(*) from a),2
  ) as immediate_percentage
