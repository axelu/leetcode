
-- 1142. User Activity for the Past 30 Days II
-- https://leetcode.com/problems/user-activity-for-the-past-30-days-ii/




/* Write your T-SQL query statement below */

-- unique users
declare @uu decimal;
set @uu = (
    select count(*) from (
    select distinct user_id from activity where activity_date between dateadd(day,-29,'2019-07-27') and '2019-07-27'
    ) t
)

-- nbr sessions
declare @s int;
set @s = (
    select count(*) from (
    select distinct session_id from activity where activity_date between dateadd(day,-29,'2019-07-27') and '2019-07-27'
    ) t
)

-- average number of sessions per user = nbr sessions / nbr users
if @uu = 0
    select 0 as average_sessions_per_user
else
    select round(@s/@uu,2) as average_sessions_per_user
