import csv
import enum
from collections import defaultdict

file = open("records_full.csv")

records = []
records_d = defaultdict(list)

with file:
    for line in file.readlines():
        records.append(line.split(','))


for i, rec in enumerate(records):
    records[i][4] = float(rec[4])
    records[i][5] = float(rec[5])
    records_d[rec[2]].append(rec)

for st, recs in sorted(records_d.items()):
    print(f'{st} ', end='')
    #min long
    print(f'{min(recs, key=lambda x: x[5])[0]}', end=' ')
    #max long
    print(f'{max(recs, key=lambda x: x[5])[0]}', end=' ')
    #max lat
    print(f'{max(recs, key=lambda x: x[4])[0]}', end=' ')
    #min lat
    print(f'{min(recs, key=lambda x: x[4])[0]}', end=' ')
    print()