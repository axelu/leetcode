
-- 1747. Leetflex Banned Accounts
-- https://leetcode.com/problems/leetflex-banned-accounts/



/* Write your T-SQL query statement below */

with cte
as
(
select
  row_number() over(order by (select null)) as rownbr,
  account_id,
  ip_address,
  login,
  logout
from
  loginfo
),
b
as
(
select
  l.rownbr as l_rownbr,
  l.account_id as l_account_id,
  l.ip_address as l_ip_address,
  l.login as l_login,
  l.logout as l_logout,
  r.rownbr as r_rownbr,
  r.account_id as r_account_id,
  r.ip_address as r_ip_address,
  r.login as r_login,
  r.logout as r_logout
from
  cte l left join cte r on
    l.rownbr < r.rownbr and
    l.account_id = r.account_id and
    l.logout >= r.login and
    l.login <= r.logout
)
select distinct
  l_account_id as account_id
from
  b
where
  r_ip_address is not null and l_ip_address <> r_ip_address
