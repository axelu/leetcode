
-- 550. Game Play Analysis IV
-- https://leetcode.com/problems/game-play-analysis-iv/




/* Write your T-SQL query statement below */

/*
-- number of players
select
  count(distinct player_id)
from
  activity
  */

with logins
as
(
select distinct
  player_id,
  event_date
from
  activity
),
loginsplus
as
(
select
  player_id,
  event_date,
  datediff(day,lag(event_date,1,'1900-01-01') over(partition by player_id order by event_date),event_date) as days_since_last_login,
  rank() over(partition by player_id order by event_date) as rnk
from
  logins
)
select
round(cast((select count(*) from loginsplus where rnk = 2 and days_since_last_login = 1) as decimal)/
  (select count(distinct player_id) from activity),2) as fraction
