import re

PWD_RE = re.compile(r"^.{8,20}$")
EMAIL_RE = re.compile(r"^[\S]+@[\S]+\.[\S]+$")
NAME_RE = re.compile(r"^[a-zA-z]+$")


def valid_password(password):
    return PWD_RE.match(password)


def valid_email(email):
    return EMAIL_RE.match(email)


def valid_name(name):
    return NAME_RE.match(name)


def make_cookie(id):
    return "%s" % id