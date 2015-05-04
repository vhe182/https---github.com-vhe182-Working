import datetime

def valid_appointment_time(date_time):
    if date_time >= datetime.datetime.now():
        return True
    else:
        return False