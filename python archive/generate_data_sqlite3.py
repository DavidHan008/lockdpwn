#! /usr/local/bin/python3

import cgi
import json
import athletemodel
import yate
import sys



form_data = cgi.FieldStorage()
athlete_name = form_data['which_athlete'].value
athletes = athletemodel.get_athlete_from_id(athlete_id)


print(yate.start_response('application/json'))
print(json.dumps(athletes))
