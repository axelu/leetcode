
-- 1364. Number of Trusted Contacts of a Customer
-- https://leetcode.com/problems/number-of-trusted-contacts-of-a-customer/


/* Write your T-SQL query statement below */

with trusted_contacts_cnt (user_id,cnt)
as
(
select
  t.user_id,
  count(*) as cnt
from (
    select
      c.user_id,
      c.contact_name,
      c.contact_email,
      u.customer_id
    from
      -- contacts c left outer join customers u on c.contact_email = u.email
      contacts c inner join customers u on c.contact_email = u.email
  ) t
group by
  t.user_id
),
contacts_cnt (user_id,cnt)
as
(
select
  t.user_id,
  count(*) as cnt
from
  contacts t
group by
  t.user_id
)
select
  i.invoice_id,
  c.customer_name,
  i.price,
  isnull(a.cnt,0) as contacts_cnt,
  isnull(b.cnt,0) as trusted_contacts_cnt
from
  invoices i
    inner join customers c on i.user_id = c.customer_id
    left outer join contacts_cnt a on i.user_id = a.user_id
    left outer join trusted_contacts_cnt b on i.user_id = b.user_id
order by
  i.invoice_id

