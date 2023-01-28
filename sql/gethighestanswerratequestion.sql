
-- 578. Get Highest Answer Rate Question
-- https://leetcode.com/problems/get-highest-answer-rate-question/




/* Write your T-SQL query statement below */

with shown
as
(
select
  question_id,
  count(*) as cnt
from
  surveylog
where
  action = 'show'
group by
  question_id
),
answered
as
(
select
  question_id,
  count(*) as cnt
from
  surveylog
where
  action = 'answer'
group by
  question_id
),
answer_rate
as
(
select
  s.question_id,
  rank() over(order by cast(isnull(a.cnt,0) as decimal)/s.cnt desc, s.question_id) as rnk
from
  shown s left join answered a on s.question_id = a.question_id
)
select
  question_id as survey_log
from
  answer_rate
where
  rnk = 1
