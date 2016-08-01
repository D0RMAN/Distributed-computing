from flask import Flask

flask_app = Flask(__name__)
flask_app.config.from_object('config')



from flask.ext.bcrypt import Bcrypt

bcrypt = Bcrypt(flask_app)



from flask.ext.sqlalchemy import SQLAlchemy

app_db = SQLAlchemy(flask_app)



from flask.ext.login import LoginManager

login_manager = LoginManager(flask_app)
login_manager.init_app(flask_app)
login_manager.login_view = 'signin'



from app.models.user import User

@login_manager.user_loader
def load_user(user_id):
	return User.query.filter_by(user_id = int(user_id)).first()

work_app_rel_path = 'static/libs'
work_app_filename = 'UserApp'

from app.routes import *
from app.models import *