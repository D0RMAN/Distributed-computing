__all__ = [
	'signin', 
	'signup', 
	'signout', 
	'create_task', 
	'home', 
	'user',
	'tasks',
	'task_on_id', 
	'download_the_app',
	'download_lib'
	]

from config import ALLOWED_EXTENSIONS

def allowed_file(filename):
    return '.' in filename and \
        filename.rsplit('.', 1)[1] in ALLOWED_EXTENSIONS 