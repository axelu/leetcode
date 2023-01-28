
-- 2298. Tasks Count in the Weekend
-- https://leetcode.com/problems/tasks-count-in-the-weekend/



/* Write your T-SQL query statement below */

declare @weekend_tasks int;
set @weekend_tasks = (select count(*) from tasks where datepart(weekday,submit_date) in (7,1));
declare @weekday_tasks int;
set @weekday_tasks = (select count(*) from tasks where datepart(weekday,submit_date) in (2,3,4,5,6));

select @weekend_tasks as weekend_cnt, @weekday_tasks as working_cnt;
