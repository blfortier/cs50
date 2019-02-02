import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Users who completed the survey
users = []


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    name = request.form.get("name")
    pizza_consume = request.form.get("pizza_consumption")
    pizza_place = request.form.get("pizza_place")
    topping = request.form.get("topping")
    crust = request.form.get("crust_type")

    if not name or not pizza_consume or not pizza_place or not topping or not crust:
        return render_template("error.html", message="Please be sure to enter your name and answer all questions")

    file = open("survey.csv", "a")
    writer = csv.writer(file)
    writer.writerow((request.form.get("name"), request.form.get("pizza_consumption"), request.form.get("pizza_place"), request.form.get("crust_type"), request.form.get("topping"), request.form.get("email")))
    file.close()
    return redirect("/sheet")


@app.route("/sheet", methods=["GET"])
def get_sheet():
    file = open("survey.csv", "r")
    reader = csv.reader(file)
    users = list(reader)
    return render_template("sheet.html", users=users)
