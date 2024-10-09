import random

f = open('tyr_test_cases.py', 'a')

def testcase(sex, age, cho, smo, hdl, sbp, med, out):
    s = f"sex:{sex} age:{age} cho:{cho} smo:{smo} hdl:{hdl} sbp:{sbp} med:{med} out:{out}"
    print(s)
    f.write(s + '\n')
    


def randselect(l, k):
    l = [(k, v) for k, v in l] 
    c = random.choices(l, k=k)
    return c

def gimme(l):
    return randselect(l.items(), 1)[0]

scores = {
    0: 1,
    1: 1,
    2: 1,
    3: 1,
    4: 1,
    5: 2,
    6: 2,
    7: 3,
    8: 4,
    9: 5,
    10: 6,
    11: 8,
    12: 10,
    13: 12,
    14: 16,
    15: 20,
    16: 25,
}

# for age, age_score in randselect(ages.items(), 1):
#     for chol_level, chol_score_group in randselect(chol.items(), 2):
#         chol_score = chol_score_group[age51]
#         # print(age, chol_level, age_score, chol_score)
#         for smo, smo_group in smos.items():
#             smo_score = smo_group[age]
#             for hdl, hdl_score in (hdls.items()):
#                 for med, sbp_group in (sbpmeds.items()):
#                     for sbp, sbp_score in randselect(sbp_group.items(), 2):
#                         score = age_score + chol_score + smo_score + hdl_score + sbp_score
#                         score_str = ''
#                         if score < 0:
#                             score_str = '<1'
#                         elif score >= 17:
#                             score_str = '≥30 '
#                         else:
#                             score_str = str(scores[score])
#                 testcase(age, chol_level, smo, hdl, sbp, med, score_str)

from dmen import sex, ages, chol, smos, hdls, sbpmeds

for i in range(120):
    age, age_score = gimme(ages)
    chol_level, chol_score_group = gimme(chol)
    smo, smo_group = gimme(smos)
    hdl, hdl_score = gimme(hdls)
    med, sbp_group = gimme(sbpmeds)
    sbp, sbp_score = gimme(sbp_group)
    
    score = age_score + chol_score_group[age] + smo_group[age] + hdl_score + sbp_score
    score_str = ''
    if score < 0:
        score_str = '<1'
    elif score >= 17:
        score_str = '>30 '
    else:
        score_str = str(scores[score])
    testcase(sex, age, chol_level, smo, hdl, sbp, med, score_str)
    print(score)
    
    
        
                    
                    