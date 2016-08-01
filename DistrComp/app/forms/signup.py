from flask.ext.wtf import Form
from flask.ext.wtf.html5 import EmailField
from wtforms import StringField, BooleanField, SelectField, PasswordField 
from wtforms.validators import DataRequired, Email, EqualTo, Length
from app.forms import length_error_message

class SignupForm(Form):
	email = EmailField(
			"Email", 
			validators = [
				DataRequired(), 
				Email(), 
				Length(min=5, max=30, message='Email field error: '+length_error_message)
			])
	password = PasswordField(
			"Password", 
			validators = [
				DataRequired(), 
				Length(min=5, max=30, message='Password field error: '+length_error_message)
			])
	password_confirm = PasswordField(
			"Password Confirm", 
			validators = [
				DataRequired(), 
				EqualTo('password', message = 'Passwords must match'),
				Length(min=5, max=30, message='Password Confirm field error: '+length_error_message)
			])
	nickname = StringField(
			"Nickname", 
			validators = [
				DataRequired(),
				Length(min=5, max=30, message='Nickname field error: '+length_error_message)
			])
	requisite = StringField(
			"Requisite", 
			validators = [
				DataRequired(),
				Length(min=5, max=30, message='Requisite field error: '+length_error_message)
			])
	name = StringField(
			"Name",
			validators = [
				Length(min=5, max=30, message='Name field error: '+length_error_message)
			])
	surname = StringField(
			"Surname",
			validators = [
				Length(min=5, max=30, message='Surname field error: '+length_error_message)
			])			