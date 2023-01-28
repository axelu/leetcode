
-- 1454. Active Users
-- https://leetcode.com/problems/active-users/



/* Write your T-SQL query statement below */

declare @n int;
set @n = 4; -- n+1 consecutive logins

-- eliminate multiple logins per day
with login_day
as
(
select distinct
  id,
  login_date
from
  logins
),
c
as
(
select
  id,
  login_date,
  case
    when lag(login_date,@n) over(partition by id order by login_date) is null
    then null
    else
      case
        when datediff(day,lag(login_date,@n) over(partition by id order by login_date),login_date) = @n
        then lag(login_date,@n) over(partition by id order by login_date)
        else null
      end
  end as consecutive
from
  login_day
)
select distinct
  a.id,
  a.name
from
  accounts a join c on a.id = c.id and c.consecutive is not null
order by
  a.id
