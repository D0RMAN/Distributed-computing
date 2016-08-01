from flask.ext.wtf import Form
from flask.ext.wtf.file import FileRequired, FileField
from wtforms.fields import StringField
# from wtforms.fields import StringField, FileField
# from wtforms import FileField
from wtforms.widgets import TextArea
from wtforms.validators import DataRequired, Length
from app.forms import length_error_message

class TaskForm(Form):
	title = StringField(
			"Title", 
			validators = [
				DataRequired(), 
				Length(min = 1, max = 50, message = 'Title field error: ' + length_error_message)
			])
	description = StringField("Description", widget=TextArea())
	library = FileField('Your Library', validators=[FileRequired()])