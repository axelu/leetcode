
-- 2984. Find Peak Calling Hours for Each City
-- https://leetcode.com/problems/find-peak-calling-hours-for-each-city/



/* Write your T-SQL query statement below */

with calls_hour as
(
select
    city,
    datepart(hh, call_time) as calling_hour,
    1 as call
from
    Calls
),
sum_hour as
(
select
    city,
    calling_hour,
    sum(call) as number_of_calls
from
    calls_hour
group by
    city, calling_hour
),
ranked_hour as
(
select
    city,
    calling_hour,
    number_of_calls,
    rank() over(partition by city order by number_of_calls desc) as rnk
from
    sum_hour
)
select
    city,
    calling_hour as peak_calling_hour,
    number_of_calls
from
    ranked_hour
where
    rnk = 1
order by
    calling_hour desc, city desc
