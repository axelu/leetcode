
-- 3198. Find Cities in Each State
-- https://leetcode.com/problems/find-cities-in-each-state/




/* Write your T-SQL query statement below */

SELECT state, STRING_AGG(city, ', ') WITHIN GROUP (ORDER BY city ASC) AS cities
FROM cities
GROUP BY state
ORDER BY state;
