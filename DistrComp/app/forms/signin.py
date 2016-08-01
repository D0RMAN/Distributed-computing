from flask.ext.wtf import Form
from flask.ext.wtf.html5 import EmailField
from wtforms import StringField, BooleanField, PasswordField 
from wtforms.validators import DataRequired, Email, Length
from app.forms import length_error_message

class SigninForm(Form):
	"""docstring for SigninForm"""
	email = EmailField(
			"Email Address", 
			validators = [
				DataRequired(), 
				Email(), 
				Length(min = 5, max = 30, message = 'Email field error: ' + length_error_message)
			])
	password = PasswordField(
			"Password", 
			validators = [
				DataRequired(), 
				Length(min = 5, max = 30, message = 'Password field error: ' + length_error_message)
			])
	remember_me = BooleanField("Remember Me", default = False)