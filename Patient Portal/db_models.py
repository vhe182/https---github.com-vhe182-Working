import datetime
from google.appengine.ext import db

PATIENT_TYPE = "PATIENT"
DOCTOR_TYPE = "DOCTOR"
NURSE_TYPE = "NURSE"
STAFF_TYPE = "STAFF"

ACCOUNT_TYPES = {PATIENT_TYPE, DOCTOR_TYPE, NURSE_TYPE, STAFF_TYPE}


class User(db.Model):
    first_name = db.StringProperty(required=True)
    last_name = db.StringProperty(required=True)
    email = db.StringProperty(required=True)
    password = db.StringProperty(required=True)
    account_type = db.StringProperty(required=True)
    is_admin = db.BooleanProperty(required=True)
    is_locked = db.BooleanProperty(required=True)
    created = db.DateTimeProperty(auto_now=True)


class Messages(db.Model):
    recipient_email = db.StringProperty(required=True)
    sender_email = db.StringProperty(required=True)
    message = db.TextProperty(required=True)
    status = db.StringProperty(required=False)
    date = db.DateTimeProperty(auto_now=True)


class PatientChart(db.Model):
    email = db.StringProperty(required=True)
    height = db.StringProperty(required=True)
    weight = db.StringProperty(required=True)
    blood_pressure = db.StringProperty(required=True)
    comments = db.TextProperty(required=False)
    diagnosis = db.TextProperty(required=False)
    created = db.DateTimeProperty(auto_now=True)


class Bill(db.Model):
    patient_email = db.StringProperty(required=True)
    created = db.DateTimeProperty(auto_now=True)
    routine_physical_adult = db.BooleanProperty(default=False)
    female_exam = db.BooleanProperty(default=False)
    child_exam = db.BooleanProperty(default=False)
    emergency_room_adult = db.BooleanProperty(default=False)
    emergency_room_child = db.BooleanProperty(default=False)
    allergy_study = db.BooleanProperty(default=False)
    routine_electrocardiogram = db.BooleanProperty(default=False)
    blood_test = db.BooleanProperty(default=False)
    urinalysis_test = db.BooleanProperty(default=False)
    mri = db.BooleanProperty(default=False)
    cat = db.BooleanProperty(default=False)
    sum = db.FloatProperty(default=0)


class Prices(db.Model):
    routine_physical_adult = db.FloatProperty(default=110.00)
    female_exam = db.FloatProperty(default=100.00)
    child_exam = db.FloatProperty(default=75.00)
    emergency_room_adult = db.FloatProperty(default=570.00)
    emergency_room_child = db.FloatProperty(default=480.00)
    allergy_study = db.FloatProperty(default=250.00)
    routine_electrocardiogram = db.FloatProperty(default=60.00)
    blood_test = db.FloatProperty(default=22.00)
    urinalysis_test = db.FloatProperty(default=16.00)
    mri = db.FloatProperty(default=902.00)
    cat = db.FloatProperty(default=623.10)


class Appointment(db.Model):
    patient_email = db.StringProperty(required=True)
    doctor_email = db.StringProperty(required=True)
    date_and_time = db.DateTimeProperty(required=True)
    checked_in = db.BooleanProperty(default=False)
    checked_out = db.BooleanProperty(default=False)
    is_cancelled = db.BooleanProperty(default=False)
    created = db.DateTimeProperty(auto_now=True)


def does_user_exist(x):
    user_db = db.GqlQuery("SELECT * FROM User WHERE email = :text", text=x)
    user = user_db.get()

    return user is not None


def does_patient_exist(x):
    user_db = db.GqlQuery("SELECT * FROM User WHERE email = :text AND account_type = 'PATIENT'", text=x)
    patient = user_db.get()

    return patient is not None


def does_doctor_exit(x):
    user_db = db.GqlQuery("SELECT * FROM User WHERE email = :text AND account_type = 'DOCTOR'", text=x)
    doctor = user_db.get()

    return doctor is not None


def does_patient_last_name_exist(last_name):
    patient_db = db.GqlQuery("SELECT * FROM User WHERE last_name = :ln AND "
                             "account_type = 'PATIENT'", ln=last_name)
    patient = patient_db.get()

    return patient is not None



def get_user(x):
    user_db = db.GqlQuery("SELECT * FROM User where email = :text", text=x)
    user = user_db.get()

    return user


def get_appointments(filter_by_doctor=False, doctors_email=''):
    today_date = datetime.date.today()
    if filter_by_doctor:
        appointment_db = db.GqlQuery("SELECT * FROM Appointment "
                                     "WHERE doctor_email = :de AND "
                                     "date_and_time >= :td",
                                     de=doctors_email, td=today_date)
        return list(appointment_db)
    else:
        appointment_db = db.GqlQuery("SELECT * FROM Appointment "
                                     "WHERE date_and_time >= :td",
                                     td=today_date)
        return list(appointment_db)


def get_messages(recipient_email):
    messages_db = db.GqlQuery("SELECT * FROM Messages "
                              "WHERE recipient_email = :re",
                              re=recipient_email)
    return list(messages_db)


def get_sent_messages(sender_email):
    messages_db = db.GqlQuery("SELECT * FROM Messages"
                              " WHERE sender_email = :se",
                              se=sender_email)
    return list(messages_db)


def get_charts(patient_email):
    patient_chart_db = db.GqlQuery("SELECT * FROM PatientChart "
                                   "WHERE email = :pe",
                                   pe=patient_email)
    return list(patient_chart_db)


def get_patients_with_last_name(last_name):
    user_db = db.GqlQuery("SELECT * FROM User "
                          "WHERE last_name = :ln AND "
                          "account_type = 'PATIENT'",
                          ln=last_name)
    return list(user_db)


def not_conflicting_appointment(doctor_email, date_time):
    appointment_db = db.GqlQuery("SELECT * FROM Appointment "
                                 "WHERE doctor_email = :de AND "
                                 "date_and_time = :dt",
                                 de=doctor_email, dt=date_time)
    appointment = appointment_db.get()

    return appointment is None


def valid_admin(email, password):
    if email != "admin" or password != "admin123":
        admin_db = db.GqlQuery("SELECT * FROM User Where email = :text AND is_admin = TRUE", text=email)
        admin = admin_db.get()

        return admin is not None
    else:
        return True

def valid_account_type(account_type):
    if account_type not in ACCOUNT_TYPES:
        return False
    else:
        return True