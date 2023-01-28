
-- 1164. Product Price at a Given Date
-- https://leetcode.com/problems/product-price-at-a-given-date/



/* Write your T-SQL query statement below */

select
  distinct p.product_id,
  coalesce(
      (select top 1
         it.new_price
       from
         products it
       where
         it.product_id = p.product_id and
         it.change_date <= '2019-08-16'
       order by
         it.change_date desc
      ),
      10
  ) as price
from
  products p
