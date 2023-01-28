
-- 586. Customer Placing the Largest Number of Orders
-- https://leetcode.com/problems/customer-placing-the-largest-number-of-orders/



/* Write your T-SQL query statement below */

select t.customer_number
from (
    select top 1
      customer_number,
      count(customer_number) as cnt
    from
      orders
    group by customer_number
    order by count(customer_number) desc
) t
