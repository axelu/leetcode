
-- 3808. Find Emotionally Consistent Users
-- https://leetcode.com/problems/find-emotionally-consistent-users/



/* Write your T-SQL query statement below */

with cte_user_reaction__total as
(
select user_id, count(*) as reaction_total from reactions group by user_id
),
cte_user_reaction_count as
(
select user_id, reaction, count(*) as reaction_count from reactions group by user_id, reaction
),
cte_user_reaction_ratio as
(
select
    urt.user_id,
    urc.reaction,
    (urc.reaction_count * 1.0)/urt.reaction_total as reaction_ratio
from
    cte_user_reaction__total urt
        join cte_user_reaction_count urc on urt.user_id = urc.user_id
)

select
    urt.user_id,
    urr.reaction as dominant_reaction,
    round(urr.reaction_ratio, 2) as reaction_ratio
from
    cte_user_reaction__total urt
        join cte_user_reaction_ratio urr on urt.user_id = urr.user_id
where
    urt.reaction_total >= 5 and
    urr.reaction_ratio >= .6
order by
    urr.reaction_ratio desc, urt.user_id
