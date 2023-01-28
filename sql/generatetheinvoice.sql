
-- 2362. Generate the Invoice
-- https://leetcode.com/problems/generate-the-invoice/



/* Write your T-SQL query statement below */
with invoice_details
as
(
select
  o.invoice_id,
  o.product_id,
  o.quantity,
  o.quantity*p.price as price
from
  purchases o join products p on o.product_id = p.product_id
),
invoice_rank
as
(
select
  id.invoice_id,
  rank() over (order by sum(id.price) desc, id.invoice_id) as rnk
from
  invoice_details id
group by
  id.invoice_id
)
select
  id.product_id,
  id.quantity,
  id.price
from
  invoice_details id
where
  id.invoice_id in (select invoice_id from invoice_rank where rnk = 1)
