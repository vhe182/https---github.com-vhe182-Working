#!/usr/bin/env python
#
# Copyright 2007 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
import datetime
import jinja2
import os
import webapp2

from db_models import *
from login_helper import *
from schedule_helper import *
from chart_input_helper import *

template_dir = os.path.join(os.path.dirname(__file__), 'templates')
jinja_env = jinja2.Environment(loader=jinja2.FileSystemLoader(template_dir),
                               autoescape=True)


class Handler(webapp2.RequestHandler):
    def write(self, *a, **kw):
        self.response.out.write(*a, **kw)

    def render_str(self, template, **params):
        t = jinja_env.get_template(template)
        return t.render(params)

    def render(self, template, **kw):
        self.write(self.render_str(template, **kw))

    def get_cookie(self):
        user_info = self.request.cookies.get('user_id', '')

        if user_info == '':
            return
        else:
            return User.get_by_id(int(user_info))


class RedirectUserHandler(Handler):
    def get(self):
        current_user = self.get_cookie()

        try:
            if current_user.account_type == PATIENT_TYPE:
                self.redirect('/patient/home')
            elif current_user.account_type == DOCTOR_TYPE:
                self.redirect('/doctor/home')
            elif current_user.account_type == NURSE_TYPE:
                self.redirect('/nurse/home')
            elif current_user.account_type == STAFF_TYPE:
                self.redirect('/staff/home')
        except:
            self.redirect('/login')


class PatientHomeHandler(Handler):
    def get(self):
        current_user = self.get_cookie()

        try:
            if current_user.account_type == PATIENT_TYPE:
                user_email = current_user.email
                self.render('patient_home.html', logged_in=True, email=user_email)
            else:
                self.redirect('/login')
        except:
            self.redirect('/login')


class DoctorHomeHandler(Handler):
    def get(self):
        current_user = self.get_cookie()

        try:
            if current_user.account_type == DOCTOR_TYPE:
                user_email = current_user.email
                self.render('doctor_home.html', logged_in=True,
                            email=user_email, is_admin=current_user.is_admin)
            else:
                self.redirect('/login')
        except:
            self.redirect('/login')


class NurseHomeHandler(Handler):
    def get(self):
        current_user = self.get_cookie()

        try:
            if current_user.account_type == NURSE_TYPE:
                user_email = current_user.email
                self.render('nurse_home.html', logged_in=True,
                            email=user_email, is_admin=current_user.is_admin)
            else:
                self.redirect('/login')
        except:
            self.redirect('/login')


class StaffHomeHandler(Handler):
    def get(self):
        current_user = self.get_cookie()

        try:
            if current_user.account_type == STAFF_TYPE:
                user_email = current_user.email
                self.render('staff_home.html', logged_in=True,
                            email=user_email, is_admin=current_user.is_admin)
            else:
                self.redirect('/login')
        except:
            self.redirect('/login')


class HomeHandler(Handler):
    def get(self):
        current_user = self.get_cookie()

        try:
            user_email = current_user.email
            self.render('home.html', logged_in=True, email=user_email)
        except:
            self.render('home.html')


class LoginHandler(Handler):
    def get(self):
        current_user = self.get_cookie()

        try:
            user_email = current_user.email
            self.redirect('/redirect')
        except:
            self.render("login.html")

    def post(self):
        email = self.request.get("email")
        password = self.request.get("password")
        user_exists = does_user_exist(email)

        if user_exists:
            user = get_user(email)
            if password == user.password:
                user_cookie = make_cookie(str(user.key().id()))
                self.response.headers.add_header('Set-Cookie', 'user_id=%s;Path=/' % user_cookie)
                self.redirect('/redirect')

        login_error = "Invalid Login."
        self.render("login.html", login_error=login_error)


class LogoutHandler(Handler):
    def get(self):
        self.response.headers.add_header('Set-Cookie', 'user_id=;Path=/')
        self.redirect('/')


class RegisterPatientHandler(Handler):
    def get(self):
        self.render("register_patient.html", logged_in=True, email="")

    def post(self):
        first_name = self.request.get("first_name")
        last_name = self.request.get("last_name")
        email = self.request.get("email")
        password = self.request.get("password")
        verify_password = self.request.get("verify_password")

        taken_email = does_user_exist(email)

        if (valid_email(email) and valid_password(password) and password == verify_password
                and valid_name(first_name) and valid_name(last_name) and not taken_email):
            new_user = User(first_name=first_name, last_name=last_name, email=email,
                            password=password, account_type=PATIENT_TYPE, is_admin=False,
                            is_locked=False)
            new_user.put()

            self.redirect('/')
        else:
            email_error = ''
            password_error = ''
            verify_password_error = ''
            name_error = ''

            if not valid_email(email):
                email_error = "Email address is not valid."
            if not valid_password(password):
                password_error = "Password is not valid."
            if password != verify_password:
                verify_password_error = "Passwords do not match."
            if taken_email:
                email_error = "Email address already exists in the system."
            if not valid_name(first_name) or not valid_name(last_name):
                name_error = "Invalid characters in name."

            self.render("register_patient.html",
                        email_error=email_error,
                        password_error=password_error,
                        verify_password_error=verify_password_error,
                        name_error=name_error)


class CreateAccountHandler(Handler):
    def get(self):
        self.render('create_account.html')

    def post(self):
        first_name = self.request.get("first_name")
        last_name = self.request.get("last_name")
        email = self.request.get("email")
        password = self.request.get("password")
        verify_password = self.request.get("verify_password")
        account_type = self.request.get("account_type")
        admin_email = self.request.get("admin_email")
        admin_password = self.request.get("admin_password")

        is_admin = self.request.get('is_admin', '').lower() in ['true', 'yes', 't', '1', 'on', 'checked']

        taken_email = does_user_exist(email)

        if (valid_email(email) and valid_password(password) and password == verify_password
                and valid_name(first_name) and valid_name(last_name) and not taken_email
                and valid_account_type(account_type)
                and valid_admin(admin_email, admin_password)):

            new_user = User(first_name=first_name, last_name=last_name, email=email,
                            password=password, account_type=account_type, is_admin=is_admin,
                            is_locked=False)
            new_user.put()

            self.redirect('/')
        else:
            email_error = ''
            password_error = ''
            verify_password_error = ''
            name_error = ''
            admin_error = ''

            if not valid_email(email):
                email_error = "Email address is not valid."
            if not valid_password(password):
                password_error = "Password is not valid."
            if password != verify_password:
                verify_password_error = "Passwords do not match."
            if taken_email:
                email_error = "Email address already exists in the system."
            if not valid_name(first_name) or not valid_name(last_name):
                name_error = "Invalid characters in name."
            if not valid_admin(admin_email, admin_password):
                admin_error = "Invalid admin credentials."

            self.render("create_account.html",
                        logged_in=True,
                        email="",
                        email_error=email_error,
                        password_error=password_error,
                        verify_password_error=verify_password_error,
                        name_error=name_error,
                        admin_error=admin_error)


class ScheduleAppointmentHandler(Handler):
    def get(self):
        current_user = self.get_cookie()

        try:
            if current_user.account_type == STAFF_TYPE:
                user_email = current_user.email
                self.render('schedule_appointment.html', logged_in=True, email=user_email)
            else:
                self.redirect('/login')
        except:
            self.redirect('/login')

    def post(self):
        current_user = self.get_cookie()
        user_email = current_user.email
        patient_email = self.request.get("patient_email")
        doctor_email = self.request.get("doctor_email")
        year = self.request.get("year")
        month = self.request.get("month")
        day = self.request.get("day")
        hour = self.request.get("hour")
        minute = self.request.get("minute")

        valid_date_time = False
        date_and_time_tmp = "%s-%s-%s %s:%s" % (year, month, day, hour, minute)
        try:
            date_and_time = datetime.datetime.strptime(date_and_time_tmp, "%Y-%m-%d %H:%M")
            valid_date_time = True
        except:
            valid_date_time = False

        if (does_patient_exist(patient_email) and does_doctor_exit(doctor_email)
                and valid_appointment_time(date_and_time)
                and not_conflicting_appointment(doctor_email, date_and_time)
                and valid_date_time):
            new_appointment = Appointment(patient_email=patient_email, doctor_email=doctor_email, date_and_time =  date_and_time)
            new_appointment.put()
            self.redirect('/staff/home')
        else:
            error_message = ''
            if not does_patient_exist(patient_email):
                error_message += "Patient with that email doesn't exit. "
            if not does_doctor_exit(doctor_email):
                error_message += "Doctor with that email doesn't exit. "
            if not valid_date_time or not valid_appointment_time(date_and_time):
                error_message += "Invalid date and time for appointment. "
            if not valid_date_time or not not_conflicting_appointment(doctor_email, date_and_time):
                error_message += "Conflicting appointment at that date and time. "

            self.render('schedule_appointment.html',
                        logged_in=True, email=user_email, error_message=error_message)


class StaffViewScheduleHandler(Handler):
    def get(self):
        current_user = self.get_cookie()

        try:
            if current_user.account_type == STAFF_TYPE:
                user_email = current_user.email
                appointments = get_appointments()
                if appointments is not None:
                    self.render('staff_view_schedule.html', logged_in=True, email=user_email,
                                appointments=appointments)
                else:
                    self.render('staff_view_schedule.html', logged_in=True, email=user_email)
            else:
                self.redirect('/')
        except:
            self.redirect('/')

    def post(self):
        current_user = self.get_cookie()
        user_email = current_user.email
        doctor_email = self.request.get('doctor_email')
        if does_doctor_exit(doctor_email):
            appointments = get_appointments(True, doctor_email)
            self.render('staff_view_schedule.html', logged_in=True, email=user_email,
                        appointments=appointments)
        else:
            appointments = get_appointments()
            error_message = "No doctor in system with that email."
            self.render('staff_view_schedule.html', logged_in=True, email=user_email,
                        appointments=appointments, error_message=error_message)


class MedicalEnterChartHandler(Handler):
    def get(self):
        current_user = self.get_cookie()

        try:
            if (current_user.account_type == DOCTOR_TYPE or
                    current_user.account_type == NURSE_TYPE):
                user_email = current_user.email
                self.render('enter_patient_chart.html', logged_in=True, email=user_email)
        except:
            self.redirect('/login')

    def post(self):
        current_user = self.get_cookie()
        user_email = current_user.email

        patient_email = self.request.get('patient_email')
        height = self.request.get('height')
        weight = self.request.get('weight')
        systolic = self.request.get('systolic')
        diastolic = self.request.get('diastolic')
        diagnosis = self.request.get('diagnosis')
        comments = self.request.get('comments')
        blood_pressure = "%s/%s" % (systolic, diastolic)

        if (does_patient_exist(patient_email) and valid_height(height) and
                valid_weight(weight) and valid_blood_pressure(systolic, diastolic)):
            chart_entry = PatientChart(email=patient_email, height=height, weight=weight,
                                       blood_pressure=blood_pressure, comments=comments,
                                       diagnosis=diagnosis)
            chart_entry.put()
            self.redirect('/redirect')
        else:
            error_message = ""
            if not does_doctor_exit(patient_email):
                error_message += "Patient does not exist under that email. "
            if not valid_height(height) or not valid_weight(weight):
                error_message += "Height in weight must be numbers."
            if not valid_blood_pressure(systolic, diastolic):
                error_message += "Invalid input for blood pressure"

            self.render('enter_patient_chart.html', logged_in=True, email=user_email, error_message=error_message)

class SendMessageHandler(Handler):
    def get(self):
        current_user = self.get_cookie()
        user_email = current_user.email
        try:
            if current_user.account_type == PATIENT_TYPE:
                self.render('send_message_patient.html', logged_in=True, email=user_email)
            elif current_user.account_type == STAFF_TYPE:
                self.render('send_message_staff.html', logged_in=True, email=user_email)
        except:
            self.redirect('/login')

    def post(self):
        current_user = self.get_cookie()
        user_email = current_user.email

        try:
            #Send this message to all staff members
            sent_message = self.request.get('sent_message')
            if current_user.account_type == PATIENT_TYPE:
                new_message = Messages(recipient_email = STAFF_TYPE, sender_email= user_email, message = sent_message)
                new_message.put()
                self.redirect('/view/messages')
            elif current_user.account_type == STAFF_TYPE:
                recipient_email = self.request.get('recipient_email')
                new_message = Messages(recipient_email = recipient_email, sender_email = STAFF_TYPE, message = sent_message)
                new_message.put()
                self.redirect('/view/messages')
        except:
            self.redirect('/login')



class ViewMessageHandler(Handler):
    def get(self):
        current_user = self.get_cookie()
        try:
            user_email = current_user.email
            if current_user.account_type == PATIENT_TYPE:
                messages = get_messages(user_email)
                self.render('view_messages.html', logged_in=True,
                            email=user_email, messages=messages)
            elif current_user.account_type == STAFF_TYPE:
                messages = get_messages(STAFF_TYPE)
                self.render('view_messages.html', logged_in=True,
                            email=user_email, messages=messages)
        except:
            self.redirect('/login')


class ViewSentMessageHandler(Handler):
    def get(self):
        current_user = self.get_cookie()
        try:
            user_email = current_user.email
            messages = get_sent_messages(user_email)
            self.render('view_sent_messages.html', logged_in=True
                        ,email=user_email, messages=messages)
        except:
            self.redirect('/login')

class ViewChartHandler(Handler):
    def get(self):
        current_user = self.get_cookie()
        try:
            user_email = current_user.email
            if current_user.account_type == PATIENT_TYPE:
                charts = get_charts(user_email)
                self.render('view_charts_patient.html', logged_in=True,
                            email=user_email, charts=charts)
            elif (current_user.account_type == DOCTOR_TYPE
                    or current_user.account_type == NURSE_TYPE):
                self.render('view_charts_medical.html', logged_in=True,
                            email=user_email)
        except:
            self.redirect('/login')

    def post(self):
        current_user = self.get_cookie()
        user_email = current_user = current_user.email
        patient_email = self.request.get('patient_email')
        if does_patient_exist(patient_email):
            charts = get_charts(patient_email)
            self.render('view_charts_medical.html', logged_in=True,
                        email=user_email, charts=charts)
        else:
            error_message = ""
            if not does_patient_exist(patient_email):
                error_message += "Patient does not exist under that email. "

            self.render('view_charts_medical.html', logged_in=True,
                        email=user_email, error_message=error_message)


class MedicalFindPatientHandler(Handler):
    def get(self):
        current_user = self.get_cookie()

        try:
            user_email = current_user.email
            if (current_user.account_type == STAFF_TYPE or
                    current_user.account_type == DOCTOR_TYPE or
                    current_user.account_type == NURSE_TYPE):
                self.render('find_patient.html', logged_in=True, email=user_email)
            else:
                self.redirect('/login')
        except:
            self.redirect('/login')


    def post(self):
        current_user = self.get_cookie()
        user_email = current_user.email
        last_name = self.request.get('last_name')

        error_message = ""
        if does_patient_last_name_exist(last_name):
            patients = get_patients_with_last_name(last_name)
            self.render('find_patient.html', logged_in=True,
                        email=user_email, patients=patients)
        else:
            error_message = "Patient does not exist under that last name. "
            self.render('find_patient.html', logged_in=True,
                        email=user_email, error_message=error_message)


class DoctorViewSchedule(Handler):
    def get(self):
        current_user = self.get_cookie()

        try:
            user_email = current_user.email
            if current_user.account_type == DOCTOR_TYPE:
                appointments = get_appointments(True, user_email)
                self.render('doctor_view_schedule.html', logged_in=True,
                            email=user_email, appointments=appointments)
            else:
                self.redirect('/login')
        except:
            self.redirect('/login')


class ReceiptCreationHandler(Handler):
    def get(self):
        current_user = self.get_cookie()

        try:
            if current_user.account_type == STAFF_TYPE:
                user_email = current_user.email
                self.render('create_receipt.html', logged_in=True, email=user_email,
                            current_user = current_user)
            else:
                self.redirect('/login')
        except ValueError:
            self.redirect('/login')

    def post(self):
            current_user = self.get_cookie()
            patient_email = self.request.get('patient_email')
            total = 0.00
            routine_physical_adult = self.request.get('routine_physical_adult', '').lower() in ['true']
            female_exam = self.request.get('female_exam', '').lower() in ['true']
            child_exam = self.request.get('child_exam', '').lower() in ['true']
            emergency_room_adult = self.request.get('emergency_room_adult', '').lower() in ['true']
            emergency_room_child = self.request.get('emergency_room_child', '').lower() in ['true']
            allergy_study = self.request.get('allergy_study', '').lower() in ['true']
            routine_electrocardiogram = self.request.get('routine_electrocardiogram', '').lower() in ['true']
            blood_test = self.request.get('blood_test', '').lower() in ['true']
            urinalysis_test = self.request.get('urinalysis_test', '').lower() in ['true']
            mri = self.request.get('mri', '').lower() in ['true']
            cat = self.request.get('cat', '').lower() in ['true']
            if does_patient_exist(patient_email) and total is not 0:
                    new_prices = Prices()
                    if routine_physical_adult:
                        total += new_prices.routine_physical_adult
                    if female_exam:
                        total += new_prices.female_exam
                    if child_exam:
                        total += new_prices.child_exam
                    if emergency_room_adult:
                        total += new_prices.emergency_room_adult
                    if emergency_room_child:
                        total += new_prices.emergency_room_child
                    if allergy_study:
                        total += new_prices.allergy_study
                    if routine_electrocardiogram:
                        total += new_prices.routine_electrocardiogram
                    if blood_test:
                        total += new_prices.blood_test
                    if urinalysis_test:
                        total += new_prices.urinalysis_test
                    if mri:
                        total += new_prices.mri
                    if cat:
                        total += new_prices.cat
                    new_bill = Bill(patient_email=patient_email,
                                    routine_physical_adult=routine_physical_adult,
                                    female_exam=female_exam,
                                    child_exam=child_exam,
                                    emergency_room_adult=emergency_room_adult,
                                    emergency_room_child=emergency_room_child,
                                    allergy_study=allergy_study,
                                    routine_electrocardiogram=routine_electrocardiogram,
                                    blood_test=blood_test,
                                    urinalysis_test=urinalysis_test,
                                    mri=mri,
                                    cat=cat,
                                    sum=total)
                    patient = get_user(patient_email)
                    self.render('view_receipt.html', logged_in=True, current_user=current_user, new_bill=new_bill,
                                new_prices=new_prices, patient=patient)
            else:
                error_message = ""
                if not does_patient_exist(patient_email):
                    error_message += "Error: Patient does not exist under that email."
                if total is 0:
                    error_message += "Error: Total can not be zero"
                self.render('create_receipt.html', logged_in=True, email=current_user.email,
                            error_message=error_message)



app = webapp2.WSGIApplication([
    ('/', HomeHandler),
    ('/login', LoginHandler),
    ('/logout', LogoutHandler),
    ('/create_receipt', ReceiptCreationHandler),
    ('/register_patient', RegisterPatientHandler),
    ('/create_account', CreateAccountHandler),
    ('/redirect', RedirectUserHandler),
    ('/patient/home', PatientHomeHandler),
    ('/doctor/home', DoctorHomeHandler),
    ('/doctor/schedule', DoctorViewSchedule),
    ('/nurse/home', NurseHomeHandler),
    ('/staff/home', StaffHomeHandler),
    ('/staff/schedule', ScheduleAppointmentHandler),
    ('/staff/view/schedule', StaffViewScheduleHandler),
    ('/medical/chart', MedicalEnterChartHandler),
    ('/view/chart', ViewChartHandler),
    ('/view/messages', ViewMessageHandler),
    ('/view/messages/compose', SendMessageHandler),
    ('/view/messages/sent', ViewSentMessageHandler),
    ('/medical/find/patient', MedicalFindPatientHandler)
], debug=True)
