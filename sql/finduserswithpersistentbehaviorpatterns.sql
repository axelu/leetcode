
-- 3832. Find Users with Persistent Behavior Patterns
-- https://leetcode.com/problems/find-users-with-persistent-behavior-patterns/





/* Write your T-SQL query statement below */

-- select * from activity

/*
 questioning this requirement
 "The user performed exactly one action per day during that period."
                     --------------------------
 see this input, user 1 has on 2024-01-01 two different actions,
 but still she is expected to show in results
 that seemingly conflicts with requirements
 | user_id | action_date | action |
 | ------- | ----------- | ------ |
 | 1       | 2024-01-01  | login  |
 | 1       | 2024-01-01  | click  |
 | 1       | 2024-01-02  | login  |
 | 1       | 2024-01-03  | login  |
 | 1       | 2024-01-04  | login  |
 | 1       | 2024-01-05  | login  |
 | 1       | 2024-01-06  | logout |

*/

-- see also 2752. Customers with Maximum Number of Transactions on Consecutive Days
-- https://leetcode.com/problems/customers-with-maximum-number-of-transactions-on-consecutive-days/

with cte_action_start_end as
(
select
    user_id,
    action_date,
    [action],
    CASE
        when LAG(action_date) over(partition by user_id, [action] order by action_date) is not null
        then
            CASE
                when DATEDIFF(dd, LAG(action_date) over(partition by user_id, [action] order by action_date), action_date) > 1
                then 1
                else 0
            END
        else 1
    END as is_start,
    CASE
        when LEAD(action_date) over(partition by user_id, [action] order by action_date) is not null
        then
            CASE
                when DATEDIFF(dd, action_date, LEAD(action_date) over(partition by user_id, [action] order by action_date)) > 1
                then 1
                else 0
            END
        else 1
    END as is_end
from
    activity
),
cte_action_start_end_filtered as
(
select
    ase.user_id,
    ase.action_date,
    ase.[action],
    ase.is_start,
    ase.is_end,
    CASE
        when ase.is_start = 1 and ase.is_end = 1
        then 1
        else
            CASE
                when ase.is_end = 0
                then 0
                else DATEDIFF(dd, (
                                    select max(i.action_date)
                                    from cte_action_start_end as i
                                    where i.user_id = ase.user_id and i.is_start = 1 and i.action_date < ase.action_date
                                   ),
                              ase.action_date
                     ) + 1
            END
    END as consecutive_days
from
    cte_action_start_end as ase
where
    ase.is_start = 1 OR ase.is_end = 1
)
select
    asef.user_id,
    asef.[action],
    asef.consecutive_days as streak_length,
    dateadd (dd, (asef.consecutive_days * -1) + 1, asef.action_date) as [start_date],
    asef.action_date as end_date
from
    cte_action_start_end_filtered asef
where
    asef.is_end = 1 -- could be ommitted
    and asef.consecutive_days >= 5
order by streak_length desc, user_id




-- select * from activity

