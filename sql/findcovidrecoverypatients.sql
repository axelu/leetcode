
-- 3586. Find COVID Recovery Patients
-- https://leetcode.com/problems/find-covid-recovery-patients/





/* Write your T-SQL query statement below */

/* refefence implementation counts days from '1st' Positive
   to 1st negative after that if any

| test_id | patient_id | test_date  | result       |
| ------- | ---------- | ---------- | ------------ |
| 1       | 1          | 2023-01-15 | Positive     |
| 13      | 1          | 2023-01-24 | Positive     |
| 2       | 1          | 2023-01-25 | Negative     |

assume only one test per day per patient

also, see these test results
| test_id | patient_id | test_date  | result       |
| ------- | ---------- | ---------- | ------------ |
| 22      | 6          | 2023-02-11 | Positive     |
| 23      | 6          | 2023-03-25 | Inconclusive |
| 24      | 6          | 2023-04-26 | Negative     |
| 25      | 6          | 2023-05-11 | Inconclusive |
| 26      | 6          | 2023-06-13 | Positive     |
| 27      | 6          | 2023-07-19 | Negative     |

expected answer is 74 days, which is the 1st cycle

 */

with cte1 as
(
select
    -- o.test_id,
    o.patient_id,
    o.test_date as pos_test_date,
    -- o.result,
    (select min(i.test_date) from covid_tests i where
        i.patient_id = o.patient_id and
        i.test_date >= o.test_date and
        i.result = 'Negative'
    ) as neg_test_date
from
    covid_tests o
where
    result = 'Positive'
),
-- need to eliminate where patient, test_date and neg_test_date is same
cte2 as
(
select
    patient_id,
    pos_test_date,
    neg_test_date,
    RANK() over(partition by patient_id, neg_test_date order by pos_test_date) as rnk
from
    cte1
where
    neg_test_date is not NULL
),
-- select * from cte2
cte3 as
(
select
    cte2.patient_id,
    cte2.pos_test_date,
    cte2.neg_test_date,
    RANK() over(partition by patient_id order by pos_test_date) as rnk
from
    cte2
where
    cte2.rnk = 1
)
-- select * from cte3


select
    cte3.patient_id,
    p.patient_name,
    p.age,
    datediff(day,cte3.pos_test_date,cte3.neg_test_date) as recovery_time
from
    cte3 join patients p on cte3.patient_id = p.patient_id
where
    cte3.rnk = 1
order by
    datediff(day,cte3.pos_test_date,cte3.neg_test_date), p.patient_name


