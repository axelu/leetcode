
-- 2308. Arrange Table by Gender
-- https://leetcode.com/problems/arrange-table-by-gender/


/* Write your T-SQL query statement below */

select
  t.user_id,
  t.gender
from
(
select
  user_id,
  gender,
  case
    when gender = 'female' then 1
    when gender = 'other' then 2 else 3
  end as rnk
from
  genders
) t
order by
  row_number() over(partition by t.rnk order by t.user_id),rnk
