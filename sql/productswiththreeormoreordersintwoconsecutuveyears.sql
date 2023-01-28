
-- 2292. Products With Three or More Orders in Two Consecutive Years
-- https://leetcode.com/problems/products-with-three-or-more-orders-in-two-consecutive-years/




/* Write your T-SQL query statement below */

with c
as
(
select
  product_id,
  datepart(year,purchase_date) as year
from
  orders
group by
  product_id,
  datepart(year,purchase_date)
having
  count(*) > 2
)
select distinct
  c.product_id
from
  c join c p on c.product_id = p.product_id and c.year = p.year + 1
