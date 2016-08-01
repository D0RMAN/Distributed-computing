WTF_CSRF_ENABLED = True
SECRET_KEY = '7svcymy84asc4cw9m8r5gi8ky4k8ydrgzk89awcnliy8tc4aw9wf839'

UPLOAD_FOLDER = 'user_libs'
ALLOWED_EXTENSIONS = set(['dll', 'so'])


def create_sqlalchemy_database_uri():
	""" Pretty simple URI creator. Works only with MySQL. """
	db_dialect = 'mysql'
	db_driver = ''
	user_name = 'd_comp_admin'
	user_password = '12345'
	host = 'localhost'
	db_name = 'distr_comp'
	return db_dialect + db_driver + '://' + user_name + ':' + user_password + '@' + host + '/' + db_name + '?charset=utf8'

SQLALCHEMY_DATABASE_URI = create_sqlalchemy_database_uri()

# SQLALCHEMY_TRACK_MODIFICATIONS
# If set to True, Flask-SQLAlchemy will track modifications 
# of objects and emit signals. The default is None, which 
# enables tracking but issues a warning that it will be disabled 
# by default in the future. This requires extra memory and should 
# be disabled if not needed.
SQLALCHEMY_TRACK_MODIFICATIONS = False

# SQLALCHEMY_MAX_OVERFLOW
# Controls the number of connections that can be created after 
# the pool reached its maximum size. When those additional connections 
# are returned to the pool, they are disconnected and discarded.

# SQLALCHEMY_POOL_RECYCLE
# Number of seconds after which a connection is automatically recycled. 
# This is required for MySQL, which removes connections after 8 hours 
# idle by default. Note that Flask-SQLAlchemy automatically sets this 
# to 2 hours if MySQL is used.

# SQLALCHEMY_POOL_TIMEOUT	
# Specifies the connection timeout for the pool. Defaults to 10.

# SQLALCHEMY_POOL_SIZE
# The size of the database pool. Defaults to the engine's default (usually 5)

# SQLALCHEMY_NATIVE_UNICODE
# Can be used to explicitly disable native unicode support. This is 
# required for some database adapters (like PostgreSQL on some 
# Ubuntu versions) when used with improper database defaults that 
# specify encoding-less databases.

# SQLALCHEMY_RECORD_QUERIES
# Can be used to explicitly disable or enable query recording. Query 
# recording automatically happens in debug or testing mode. See 
# get_debug_queries() for more information.

# SQLALCHEMY_ECHO
# If set to True SQLAlchemy will log all the statements issued to stderr 
# which can be useful for debugging.

# SQLALCHEMY_BINDS
# A dictionary that maps bind keys to SQLAlchemy connection URIs. 
# For more information about binds see Multiple Databases with Binds 
# (http://flask-sqlalchemy.pocoo.org/2.1/binds/#binds).