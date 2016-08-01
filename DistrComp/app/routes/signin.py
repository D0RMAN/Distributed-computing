from app import flask_app, login_manager, bcrypt
from app.forms.signin import SigninForm
from app.models.user import User
from flask import render_template, flash, redirect, g, url_for, session, request, abort
from flask.ext.login import login_user, logout_user, current_user, login_required

@flask_app.before_request
def before_request():
    g.user = current_user

@flask_app.route('/signin', methods=['GET', 'POST'])
def signin():

    form = SigninForm()
    
    if request.method == 'GET':
        if g.user is not None and g.user.is_authenticated:
            return redirect(url_for('home'))

    if request.method == 'POST':
        if form.validate_on_submit():
            
            test_user = User.query.filter_by(email=form.email.data).first()
            
            if test_user is not None and \
               bcrypt.check_password_hash(test_user.password_hash, form.password.data):
                
                login_user(test_user, remember=form.remember_me.data)
                flash('Sign in successfully')

                # TODO!
                # next_url = request.args.get('next')
                # if not next_is_valid(next_url):
                #     return abort(400)
                return redirect(url_for('home'))

            else:
                flash('Login Errror: User does not exists.')
        else:
            flash('Some errors with validate on submit')
    return render_template('signin.html', form=form, title='Sign In')
