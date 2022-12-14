import os
import re

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_mail import Mail, Message

# Configure application
app = Flask(__name__)


# Requires that "Less secure app access" be on
# https://support.google.com/accounts/answer/6010255
app.config["MAIL_DEFAULT_SENDER"] = os.environ["MAIL_DEFAULT_SENDER"]
app.config["MAIL_PASSWORD"] = os.environ["MAIL_PASSWORD"]
app.config["MAIL_PORT"] = 587
app.config["MAIL_SERVER"] = "smtp.gmail.com"
app.config["MAIL_USE_TLS"] = True
app.config["MAIL_USERNAME"] = os.environ["MAIL_USERNAME"]
mail = Mail(app)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("Name")
        month = request.form.get("Month")
        day = request.form.get("Day")
        db.execute("INSERT INTO birthdays (name,month,day) VALUES (?,?,?)", name,month,day)
        # TODO: Add the user's entry into the database


        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthday_database = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthday_database = birthday_database)


@app.route("/deregister", methods=["POST"])
def deregister():
    if request.method == "POST":
        id = request.form.get("id")
    if id:
        db.execute("DELETE FROM birthdays WHERE id =?", id)
    return redirect("/")



































































































