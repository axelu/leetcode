
-- 1083. Sales Analysis II
-- https://leetcode.com/problems/sales-analysis-ii/



/* Write your T-SQL query statement below */

select
  distinct l.buyer_id
  -- ,r.buyer_id
from
  ( select s.buyer_id
    from sales s inner join product p on s.product_id = p.product_id where p.product_name = 'S8'
  ) as l left outer join (
    select s.buyer_id
    from sales s inner join product p on s.product_id = p.product_id where p.product_name = 'iPhone'
  ) as r on l.buyer_id = r.buyer_id
where r.buyer_id is null
