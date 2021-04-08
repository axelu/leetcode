




-- 1795. Rearrange Products Table
-- https://leetcode.com/problems/rearrange-products-table/


/* Write your T-SQL query statement below */

select product_id, store, price
  from Products
  unpivot
  (
    price for store in (store1, store2, store3)
  ) unpiv
