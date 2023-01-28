
-- 1677. Product's Worth Over Invoices
-- https://leetcode.com/problems/products-worth-over-invoices/



/* Write your T-SQL query statement below */


select
  p.name
  ,isnull(i.rest,0) as rest
  ,isnull(i.paid,0) as paid
  ,isnull(i.canceled,0) as canceled
  ,isnull(i.refunded,0) as refunded
from
  product as p left outer join (
    select
      product_id
      ,sum(rest) as rest
      ,sum(paid) as paid
      ,sum(canceled) as canceled
      ,sum(refunded) as refunded
    from
      invoice
    group by
      product_id
  ) as i on p.product_id = i.product_id
order by
  p.name
