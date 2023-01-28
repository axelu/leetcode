
-- 1398. Customers Who Bought Products A and B but Not C
-- https://leetcode.com/problems/customers-who-bought-products-a-and-b-but-not-c/



/* Write your T-SQL query statement below */

with a (customer_id)
as
(
select distinct customer_id from orders where product_name = 'A'
),
b (customer_id)
as
(
select distinct customer_id from orders where product_name = 'B'
),
c (customer_id)
as
(
select distinct customer_id from orders where product_name = 'C'
)
select distinct
  c.customer_id,
  c.customer_name
from
  customers c
where
  c.customer_id in (select customer_id from a) and
  c.customer_id in (select customer_id from b) and
  c.customer_id not in (select customer_id from c)
order by
  c.customer_id
