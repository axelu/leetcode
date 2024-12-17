
-- 3390. Longest Team Pass Streak
-- https://leetcode.com/problems/longest-team-pass-streak/







/* Write your T-SQL query statement below */

/* a group of passes is NOT interrupted at the half time (found out via testing, does not make sense)
 * we have three cases when a new group of passes starts
 *   team_from team_to
 *   1.      A A
 *           A B
 *           A A
 *   team_from team_to
 *   2.      A A
 *           A B
 *           B B
 *   team_from team_to
 *   3.      A A
 *           A A
 *           B B
 *   however per problem criteria, only case 2 to consider, OJ delivers wrong result actually for case 3
 *   so we will assume there is always a turnover record aka team_from != team_to separating a streak
 *   which makes for another case though
 *   team_from team_to
 *   4.      A B
 *           B A
 *           A A
 * we need to account for no passes, but testing reveals if no passes, team is not shown in table, so we do not need to consider
 */

with passes_details as
(
select
    p.pass_from,
    tf.team_name as team_from,
    p.pass_to,
    tp.team_name as team_to,
    p.time_stamp
from
    passes p join teams tf on p.pass_from = tf.player_id
             join teams tp on p.pass_to = tp.player_id
)
-- select * from passes_details order by time_stamp
,
passes_partition as
(
select
    ROW_NUMBER() over (partition by team_from order by time_stamp) as passid,
    team_from,
    team_to,
    time_stamp
from
    passes_details
)
-- select * from passes_partition order by team_from, passid
,
passes_first_last as
(
select
    passid,
    team_from,
    CASE
        when (team_from = team_to AND ((LAG (team_from) OVER (partition by team_from order by passid) IS NULL) OR (LAG (team_to) OVER (partition by team_from order by passid) <> team_to)))
        then 1
        else 0
    END as is_first,
    CASE
        when (team_from = team_to AND ((LEAD (team_from) OVER (partition by team_from order by passid) IS NULL) OR (LEAD (team_to) OVER (partition by team_from order by passid) <> team_to)))
        then 1
        else 0
    END as is_last
from
    passes_partition
)
-- select * from passes_first_last order by team_from, passid
,
first_last as
(
select
    passid,
    team_from,
    is_first,
    is_last,
    CASE
        when ( is_first = 1 and is_last = 1 )
        then passid
        else
            CASE
                when ( is_first = 0 and is_last = 1 )
                then LAG(passid) over(partition by team_from order by passid)
                else -1
            END
    END as first_passid
from
    passes_first_last
where
    is_first = 1 or is_last = 1
)
-- select * from first_last order by team_from, passid
,
first_last_ranked as
(
select
    first_passid,
    team_from,
    passid as last_passid,
    passid - first_passid + 1 as consecutive_passes_len,
    RANK() over(partition by team_from order by passid - first_passid + 1 desc) as rnk
from
    first_last
where
    first_passid <> -1
)
select distinct team_from as team_name, consecutive_passes_len as longest_streak from first_last_ranked where rnk = 1 order by team_name
