
-- 3204. Bitwise User Permissions Analysis
-- https://leetcode.com/problems/bitwise-user-permissions-analysis/






/* Write your T-SQL query statement below */

-- resources
-- https://explainextended.com/2009/07/13/sql-server-aggregate-bitwise-or/
-- https://stackoverflow.com/questions/71251827/sql-aggregate-logical-operations


/*
-- OR -> any_perms
SELECT
  MAX(permissions & 1) +
  MAX(permissions & 2) +
  MAX(permissions & 4) +
  MAX(permissions & 8)
FROM user_permissions
*/
/*
-- AND -> common_perms
SELECT
  MIN(permissions & 1) +
  MIN(permissions & 2) +
  MIN(permissions & 4) +
  MIN(permissions & 8)
FROM user_permissions
*/


with bits as
(
SELECT  0 AS b
UNION ALL
SELECT  b + 1
FROM    bits
WHERE   b <= 29
),
perms_calc as
(
SELECT  bts.b, POWER(2, bts.b) AS bitmask, up.user_id, POWER(2, bts.b) & up.permissions as bitset
FROM    bits as bts, user_permissions as up
),
common_perms_calc as
(
select bitmask, MIN(bitset) as common_permissions from perms_calc group by bitmask
),
common_perms_res as
(
select SUM(common_permissions) as common_perms from common_perms_calc
),
any_perms_res as
(
select SUM(DISTINCT bitset) as any_perms from perms_calc
)
select cpr.common_perms, apr.any_perms from common_perms_res cpr, any_perms_res apr
