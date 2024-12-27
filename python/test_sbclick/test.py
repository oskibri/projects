#!/bin/env python3
from datetime import datetime
from sbch import chonnect
import sys

boltid = sys.argv[1]

start_date = datetime(2024, 10, 20)
end_date = datetime(2024, 10, 21, 23, 59, 59)

connection = chonnect('sbadmin', 'D44T00kin')
result = connection.boltdr(boltid, start_date, end_date)
connection.disconnect()

print(result)
