from app import flask_app, app_db, bcrypt

class User(app_db.Model):
	user_id = app_db.Column(app_db.Integer, primary_key = True)
	email = app_db.Column(app_db.String(100), unique = False)
	name = app_db.Column(app_db.String(50), unique = False)
	surname = app_db.Column(app_db.String(50), unique = False)
	nickname = app_db.Column(app_db.String(50), unique = True)
	password_hash = app_db.Column(app_db.String(60), unique = True)
	requisite = app_db.Column(app_db.String(30), unique = True)
	tasks = app_db.relationship('Task', backref = 'author', lazy = 'dynamic')

	def is_authenticated(self):
		return True

	def is_anonymous(self):
		return False

	def is_active(self):
		return True

	def get_id(self):
		return unicode(str(self.user_id))

	def __init__(self, email, name, surname, nickname, password, requisite):
		self.email = email
		self.name = name
		self.surname = surname
		self.nickname = nickname
		self.password_hash = bcrypt.generate_password_hash(password)
		self.requisite = requisite

	# def __refl__(self):
		