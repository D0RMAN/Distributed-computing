from app import flask_app, app_db, bcrypt
from app.forms.signup import SignupForm
from flask import render_template, flash, redirect, request, url_for
from app.models.user import User

@flask_app.route('/signup', methods=['GET', 'POST'])
def signup():
    form = SignupForm()
    if request.method == 'POST':
        if form.validate_on_submit():
            new_user = User(
                email = form.email.data,
                name = form.name.data,
                surname = form.surname.data,
                nickname = form.nickname.data,
                password = form.password.data,
                requisite = form.requisite.data)
            app_db.session.add(new_user)
            app_db.session.commit()
            return redirect(url_for('home', user=new_user))
        else:
            flash('Some errors with validate on submit')
    return render_template('signup.html', form=form, title='Sign Up')