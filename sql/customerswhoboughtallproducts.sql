
-- 1045. Customers Who Bought All Products
-- https://leetcode.com/problems/customers-who-bought-all-products/




/* Write your T-SQL query statement below */

declare @product_cnt int;
set @product_cnt = (select count(*) from product);

with o
as
(
select distinct customer_id from customer
),
cte
as
(
select
  o.customer_id,
  (select
    count(distinct product_key)
   from
    customer it
   where
    it.customer_id = o.customer_id
  ) as distinct_product_cnt
from
  customer o
)
select
  distinct customer_id
from
  cte
where
  distinct_product_cnt = @product_cnt
