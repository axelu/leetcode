
-- 3051. Find Candidates for Data Scientist Position
-- https://leetcode.com/problems/find-candidates-for-data-scientist-position/




/* Write your T-SQL query statement below */

SELECT candidate_id --, Python, Tableau, Postgresql
FROM
(
SELECT candidate_id, skill
FROM candidates
WHERE skill in ('Python', 'Tableau', 'PostgreSQL')
) p
PIVOT
(
COUNT (skill)
FOR skill IN
(Python, Tableau, PostgreSQL)
) AS pvt
where Python >= 1 and Tableau >= 1 and Postgresql >= 1
