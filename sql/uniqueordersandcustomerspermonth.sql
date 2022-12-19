
-- 1565. Unique Orders and Customers Per Month
-- https://leetcode.com/problems/unique-orders-and-customers-per-month/



/* Write your T-SQL query statement below */


select
  concat_ws('-',datepart(year,order_date),format(datepart(month,order_date),'d2')) as month,
  count(order_id) as order_count,
  count(distinct customer_id) as customer_count
from orders
where invoice > 20
group by datepart(year,order_date),datepart(month,order_date)
