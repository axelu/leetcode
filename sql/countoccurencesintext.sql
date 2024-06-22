
-- 2738. Count Occurrences in Text
-- https://leetcode.com/problems/count-occurrences-in-text/





/* Write your T-SQL query statement below */

declare @bull int;
set @bull = (select count(*) from Files where content like '% bull %');

declare @bear int;
set @bear = (select count(*) from Files where content like '% bear %');

select 'bull' as word, @bull as count
union
select 'bear', @bear
