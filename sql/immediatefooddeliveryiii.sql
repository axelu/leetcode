
-- 2686. Immediate Food Delivery III
-- https://leetcode.com/problems/immediate-food-delivery-iii/




/* Write your T-SQL query statement below */


with all_orders as
(
select
  order_date,
  count(*) as cnt
from
  delivery
group by
  order_date
),
immediate_orders as
(
select
  order_date,
  count(*) as cnt
from
  delivery
where
  order_date = customer_pref_delivery_date
group by
  order_date
)
select
  ao.order_date,
  round(isnull(io.cnt,0)*100.0/ao.cnt,2) as immediate_percentage
  -- ao.cnt as total,
  -- isnull(io.cnt,0) as immediate
from
  all_orders ao left outer join immediate_orders io on ao.order_date = io.order_date
order by
  ao.order_date

