from flask import Flask, render_template,request


app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/greet", methods=["POST"])
def greet():
    name = request.form.get("name", "default")
    ## Request.args.get is for get methods
    ## Request.form.get is for post methods
    return render_template("greet.html", name=name)