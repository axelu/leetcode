
-- 3384. Team Dominance by Pass Success
-- https://leetcode.com/problems/team-dominance-by-pass-success/




/* Write your T-SQL query statement below */

with passes_details as
(
select
    p.pass_from,
    tf.team_name as team_from,
    p.pass_to,
    tp.team_name as team_to,
    p.time_stamp,
    CASE
        when cast(substring(p.time_stamp,1,2) as int) > 45
        then 2
        else
            CASE
                when cast(substring(p.time_stamp,1,2) as int) = 45 and cast(substring(p.time_stamp,4,2) as int) > 0
                then 2
                else 1
            END
    END as half_number
from
    passes p join teams tf on p.pass_from = tf.player_id
             join teams tp on p.pass_to = tp.player_id
),
passes_score as
(
select
    team_from as team_name,
    half_number,
    CASE
        when team_from = team_to
        then 1
        else -1
    END pass_score
from
    passes_details
)
select
    team_name,
    half_number,
    sum(pass_score) as dominance
from
    passes_score
group by
    team_name,
    half_number
order by
    team_name,
    half_number
