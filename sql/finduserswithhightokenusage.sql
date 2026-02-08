
-- 3793. Find Users with High Token Usage
-- https://leetcode.com/problems/find-users-with-high-token-usage/


/* Write your T-SQL query statement below */

with cte_users as
(
select distinct user_id from prompts
),
cte_total_prompts as
(
select user_id, count(*) as prompt_count from prompts group by user_id
),
cte_sum_tokens as
(
select user_id, sum(tokens) as sum_tokens from prompts group by user_id
),
cte_average_tokens_per_prompt as
(
select
    u.user_id,
    round(((st.sum_tokens * 1.0)/tp.prompt_count),2) as avg_tokens
from
    cte_users u
    join cte_total_prompts tp on u.user_id = tp.user_id
    join cte_sum_tokens st on u.user_id = st.user_id
),
cte_max_tokens as
(
select user_id, max(tokens) as max_tokens from prompts group by user_id
)

select
    u.user_id,
    tp.prompt_count,
    dt.avg_tokens
from
    cte_users u
    join cte_total_prompts tp on u.user_id = tp.user_id
    join cte_average_tokens_per_prompt dt on u.user_id = dt.user_id
    join cte_max_tokens mt on u.user_id = mt.user_id
where
    tp.prompt_count >= 3
    and mt.max_tokens > dt.avg_tokens
order by
    dt.avg_tokens desc, u.user_id
