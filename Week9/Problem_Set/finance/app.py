import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    user_id = session["user_id"]
    stocks = db.execute("SELECT symbol,name,price, SUM(shares) AS totalshares FROM transactions WHERE user_id =? GROUP BY symbol",user_id)
    cash = db.execute("SELECT cash FROM users WHERE id =?",user_id)[0]["cash"]
    total_worth = cash
    for stock in stocks:
        total_worth += stock["price"] * stock["totalshares"]
    return render_template("index.html", stocks=stocks, cash = usd(cash), total_worth = usd(total_worth))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        symbol_check = lookup(symbol)

        if not symbol:
            ## User entered no stock symbol
            return apology("Enter a Stock Symbol")
        elif not symbol_check:
            return apology("Symbol does not exist!")

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Shares must be integer")

        if shares <=0:
            return apology("Shares must be a positive integer! ")

        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        stock_name = symbol_check["name"]
        stock_price = symbol_check["price"]
        total_price = stock_price * shares
        remaining_cash = cash - total_price

        if cash < total_price:
            return apology("You don't have enough cash")

        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?",remaining_cash, user_id)
            db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES(?,?,?,?,?,?)",
                        user_id, stock_name, shares, stock_price, "buy" , symbol)
        return redirect("/")

    else:
        return render_template("buy.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_id = session["user_id"]
    """Sell shares of stock"""
    if request.method == "POST":
        user_id = session["user_id"]
        symbol =request.form.get("symbol")
        symbol_check = lookup(symbol)
        shares_to_sell = int(request.form.get("shares_to_sell"))

        if shares_to_sell <=0:
            return apology("Shares must be a positive number more than 0!")

        stock_price = symbol_check["price"]
        stock_name = symbol_check["name"]
        price = shares_to_sell * stock_price
        shares_owned = db.execute("SELECT shares FROM transactions WHERE user_id =? AND symbol =? GROUP BY symbol", user_id, symbol)[0]["shares"]
        if shares_owned < shares_to_sell:
            return apology("You do not have enough shares to sell!")

        current_cash = db.execute("SELECT cash FROM users WHERE id =?", user_id)[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id =?", current_cash + price, user_id)
        db.execute("INSERT INTO transactions (user_id,name,shares,price,type,symbol) VALUES(?,?,?,?,?,?)",
        user_id,stock_name, -shares_to_sell, stock_price,"sell",symbol)
        return redirect("/")
    else:
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
        return render_template("sell.html", symbols = symbols)

#only need to see transactions, so shd be only need method = get
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute("SELECT type,symbol,price,shares,time FROM transactions WHERE user_id =?",user_id)
    return render_template("history.html", transactions=transactions, usd = usd)




@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method =="POST":
        ## Getting the stock symbol from the front end
        stock = request.form.get("stock")

        ## This helps to check if the user did indeed enter a stock into the text field
        if not stock:
            return apology("Stock Not Given")

        ## This will parse the stock to lookup
        checked_stock = lookup(stock)

        if not checked_stock:
            return apology("Invalid Stock Entered")

        ## Creating the name of the variable that will be sent to quoted.html
        return render_template("quoted.html", checked_stock = checked_stock)

    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method=="POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Username not detected!")
        elif not password:
            return apology("Password not deteceted!")
        elif not confirmation:
            return apology("Confirmation not detected")

        if password != confirmation:
            return apology("Passwords are mismatched")

        hash = generate_password_hash(password)
        try:
            db.execute("INSERT INTO users (username,hash) VALUES (?,?)", username,hash)
            return redirect("/")
        except:
            return apology("User has already been registered previously")

    else:
        return render_template("register.html")

@app.route("/add_cash", methods =["GET","POST"])
@login_required
def add_cash():
    ## Ensuring request method is POST
    if request.method == "POST":
        user_id = session["user_id"]
        inserted_cash = request.form.get("add_cash")

        ## Ensuring either cash was added or removed
        if not inserted_cash:
            return apology("Cash was not edited!")

        ## Ensure cash inserted was > 0 and a numeric
        elif not str.isdigit(inserted_cash) or float(inserted_cash) <= 0:
            return apology("Cash inserted was is not a numeric or less than 0!")

        ## Updating SQL database:
        inserted_cash = float(inserted_cash)
        rows = db.execute("SELECT cash FROM users WHERE id =?",user_id)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", rows[0]["cash"] + inserted_cash, user_id)

        return redirect("/")

    else:
        return render_template("add_cash.html")

@app.route("/remove_cash", methods =["GET","POST"])
@login_required
def remove_cash():
    if request.method=="POST":
        user_id = session["user_id"]
        remove_cash = request.form.get("remove_cash")

        if not remove_cash:
            return apology("Cash to remove is empty!")

        elif not str.isdigit(remove_cash) or float(remove_cash) <= 0:
            return apology("Cash to remove is less than 0!")

        remove_cash = float(remove_cash)# Convert the remove_cash to float
        rows = db.execute("SELECT cash FROM users WHERE id =?",user_id)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", rows[0]["cash"] - remove_cash, user_id)

        return redirect("/")

    else:
        return render_template("remove_cash.html")


@app.route("/deregister",methods=["GET","POST"])
@login_required
def deregister():
    if request.method=="GET":
        user_id = session["user_id"]

        if user_id:
            db.execute("DELETE FROM transactions WHERE user_id =?", user_id)
            db.execute("DELETE FROM users WHERE id =?", user_id)
            session.clear()
            return render_template("deregister.html")





