
-- 1336. Number of Transactions per Visit
-- https://leetcode.com/problems/number-of-transactions-per-visit/




/* Write your T-SQL query statement below */

with transactions_cnt
as
(
select
  t.user_id,
  t.transaction_date,
  count(*) tran_cnt
from
  transactions t
group by
  t.user_id,
  t.transaction_date
),

maxtrancount
as
(
select max(tran_cnt) as mx from transactions_cnt
),

counts
as
(
select 0 as tran_cnt
union all
select tran_cnt + 1 from counts where tran_cnt < (select mx from maxtrancount)
),

visit_cnt
as
(
select
  v.user_id,
  v.visit_date,
  isnull(t.tran_cnt,0) as tran_cnt
from
  visits v left join transactions_cnt t on v.user_id = t.user_id and v.visit_date = t.transaction_date
)

select
  c.tran_cnt as transactions_count,
  (select count(*) from visit_cnt i where i.tran_cnt = c.tran_cnt) as visits_count
from
  counts c
order by
  c.tran_cnt
