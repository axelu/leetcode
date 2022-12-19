
-- 1777. Product's Price for Each Store
-- https://leetcode.com/problems/products-price-for-each-store/


/* Write your T-SQL query statement below */

select *
from
(
  select product_id,store,price from products
) as SourceTable pivot(avg(price) for store in (store1,store2,store3)) as PivotTable
