
-- 3278. Find Candidates for Data Scientist Position II
-- https://leetcode.com/problems/find-candidates-for-data-scientist-position-ii/






/* Write your T-SQL query statement below */


with projects_skill_count as -- also gives unique projects
(
    select project_id, count(*) as skill_cnt from projects group by project_id
),

projects_candidates_skills as
(
select
    p.project_id,
    p.skill as pskill,
    p.importance,
    c.candidate_id,
    c.skill as cskill,
    c.proficiency
from
    projects p join candidates c on p.skill = c.skill
),

project_candidates_skill_match as
(
select distinct
    project_id,
    candidate_id,
    count(*) as match_cnt
from
    projects_candidates_skills
group by
    project_id,
    candidate_id
),

project_candidates as
(
select
    p.project_id,
    p.candidate_id
from
    project_candidates_skill_match p
        join projects_skill_count psc on p.project_id = psc.project_id and p.match_cnt = psc.skill_cnt
),

project_candidates_calc as
(
select
    pcs.project_id,
    pcs.pskill,
    pcs.importance,
    pcs.candidate_id,
    pcs.proficiency,
    CASE
        when pcs.importance > pcs.proficiency then -5
        else
            CASE
                when pcs.importance < pcs.proficiency then 10
                else 0
            END
    END as score
from
    projects_candidates_skills pcs join project_candidates pc on pcs.project_id = pc.project_id and pcs.candidate_id = pc.candidate_id
),

project_candidates_score as
(
select
    project_id,
    candidate_id,
    sum(score) + 100 as score
from
    project_candidates_calc
group by
    project_id,
    candidate_id
),

project_candidates_ranked as
(
select
    project_id,
    candidate_id,
    score,
    RANK() OVER (partition by project_id order by score desc, candidate_id) as rnk
from
    project_candidates_score
)
select project_id, candidate_id, score from project_candidates_ranked where rnk = 1 order by project_id

