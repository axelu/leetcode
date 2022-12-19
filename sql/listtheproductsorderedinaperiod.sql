
-- 1327. List the Products Ordered in a Period
-- https://leetcode.com/problems/list-the-products-ordered-in-a-period/



/* Write your T-SQL query statement below */


select
  p.product_name,
  sum(o.unit) as unit
from products p inner join orders o on
  p.product_id = o.product_id
where
  datepart(year,o.order_date) = 2020 and datepart(month,o.order_date) = 2
group by p.product_name
having sum(o.unit) >= 100
