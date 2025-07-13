
-- 3580. Find Consistently Improving Employees
-- https://leetcode.com/problems/find-consistently-improving-employees/



/* Write your T-SQL query statement below */

with cte1 as -- employees with at least 3 reviews
(
select
    count(*) as cnt,
    employee_id
from
    performance_reviews
group by
    employee_id
having count(*) >= 3
),
cte2 as -- rank the reviews in order to get the last 3 reviews
(
select
    rank() over (partition by pr.employee_id order by pr.review_date desc) as rnk,
    pr.employee_id,
    pr.review_date,
    pr.rating
from
    performance_reviews pr join cte1 on pr.employee_id = cte1.employee_id
),
cte3 as -- calc next and next next rating for the last three reviews
(
select
    rnk,
    employee_id,
    rating,
    isnull(lag(rating,1) over(partition by employee_id order by rnk),-1) as next_rating,
    isnull(lag(rating,2) over(partition by employee_id order by rnk),-1) as next_next_rating
from
    cte2
where
    rnk <= 3
),
cte4 as -- get employee_id if increase oldest to middle review_date
(
select employee_id from cte3 where rnk = 3 and next_rating > rating
),
cte5 as -- get employee_id if increase middle to newest review_date
(
select employee_id from cte3 where rnk = 2 and next_rating > rating
)
select
    cte3.employee_id,
    e.name,
    cte3.next_next_rating - cte3.rating as improvement_score
from cte3 join employees e on cte3.employee_id = e.employee_id
where
    cte3.employee_id in (select employee_id from cte4) and
    cte3.employee_id in (select employee_id from cte5) and
    cte3.rnk = 3
order by
    (cte3.next_next_rating - cte3.rating) desc, e.name
