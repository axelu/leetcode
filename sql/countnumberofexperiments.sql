
-- 1990. Count the Number of Experiments
-- https://leetcode.com/problems/count-the-number-of-experiments/




/* Write your T-SQL query statement below */


with
cpe
as
(
    select * from ( values
        ('Android','Reading'),('Android','Sports'),('Android','Programming'),
        ('IOS','Reading'),('IOS','Sports'),('IOS','Programming'),
        ('Web','Reading'),('Web','Sports'),('Web','Programming')
    ) t(platform,experiment_name)
),
cpe_cnt
as
(select platform, experiment_name, count(*) as num_experiments from experiments group by platform,experiment_name)

select
  cpe.platform,
  cpe.experiment_name,
  isnull(cpe_cnt.num_experiments,0) as num_experiments
from
  cpe left join cpe_cnt on cpe.platform = cpe_cnt.platform and cpe.experiment_name = cpe_cnt.experiment_name
