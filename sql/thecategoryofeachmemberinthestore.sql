
-- 2051. The Category of Each Member in the Store
-- https://leetcode.com/problems/the-category-of-each-member-in-the-store/



/* Write your T-SQL query statement below */

/*
 * conversion rate of a member
 * (100 * total number of purchases for the member) / total number of visits for the member
 *
 */

with nbr_visits (member_id,visit_cnt)
as
(
select
  member_id,
  count(*) as visit_cnt
from
  visits
group by
  member_id
),
nbr_purchases (member_id,purchase_cnt)
as
(
select
  v.member_id,
  count(*)
from
  visits v inner join purchases p on v.visit_id = p.visit_id
group by
  v.member_id
),
conversion
as
(
select
  m.member_id,
  m.name,
  isnull(v.visit_cnt,0) as visit_cnt,
  isnull(p.purchase_cnt,0) as purchase_cnt,
  case
    when v.visit_cnt is null then -1
    else 100.0 * p.purchase_cnt/v.visit_cnt
  end as conversion_rate
from
  members m
    left outer join nbr_visits v on m.member_id = v.member_id
    left outer join nbr_purchases p on m.member_id = p.member_id
)
select
  c.member_id,
  c.name,
  case
    when c.conversion_rate = -1 then 'Bronze'
    when c.conversion_rate >= 80.0 then 'Diamond'
    when c.conversion_rate >= 50.0 then 'Gold' else 'Silver'
  end as category
from
  conversion c
