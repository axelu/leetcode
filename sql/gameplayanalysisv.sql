
-- 1097. Game Play Analysis V
-- https://leetcode.com/problems/game-play-analysis-v/





/* Write your T-SQL query statement below */

with activityplus
as
(
select
  player_id,
  event_date,
  rank() over(partition by player_id order by event_date) as first_login,
  case
    when lead(event_date) over(partition by player_id order by event_date) is null
    then 0
    else
      case
        when datediff(day,event_date,lead(event_date) over(partition by player_id order by event_date)) = 1
        then 1
        else 0
      end
  end as next_day_login
from
  activity
),

install_dates
as
(
select distinct
  event_date as install_dt,
  count(*) as installs
from
  activityplus
where
  first_login = 1
group by
  event_date
),

day_one_retention
as
(
select distinct
  event_date as install_dt,
  count(*) as installs_with_next_day_login
from
  activityplus
where
  first_login = 1 and next_day_login = 1
group by
  event_date
)

select
  id.install_dt,
  id.installs,
  round(cast(isnull(odr.installs_with_next_day_login,0) as decimal)/id.installs,2) as Day1_retention
from
  install_dates id left join day_one_retention odr on id.install_dt = odr.install_dt
