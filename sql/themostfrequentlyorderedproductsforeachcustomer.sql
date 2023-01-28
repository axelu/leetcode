
-- 1596. The Most Frequently Ordered Products for Each Customer
-- https://leetcode.com/problems/the-most-frequently-ordered-products-for-each-customer/



/* Write your T-SQL query statement below */

select
  t.customer_id,
  t.product_id,
  p.product_name
from (

    select
      r.customer_id,
      r.product_id,
      RANK() OVER (PARTITION BY r.customer_id ORDER BY r.Quantity DESC) AS rnk
    from (
        select
          o.customer_id,
          o.product_id,
          count(*) as quantity
        from
          orders o
        group by
          o.customer_id,o.product_id
    ) r -- ranked
  ) t inner join products p on t.product_id = p.product_id
where
  t.rnk = 1


