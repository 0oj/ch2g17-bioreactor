# create a flask server which can listen to post requests on /prefs and sets thingsboard attributes accordingly and serves www folder as static files on /

import os 

import api.thingsboard as tb
from flask import Flask, request, send_from_directory, redirect

app = Flask(__name__)
db = tb.default_db()

@app.route("/prefs", methods=["POST"])
def prefs():
    data = request.form

    if not data:
        return "no data", 400
    
    pref_temp = data["pref_temp"]
    pref_rpm = data["pref_rpm"]
    pref_pH = data["pref_pH"]

    if not pref_temp or not pref_rpm or not pref_pH:
        return "missing data", 400

    status = db.send(pref_temp=pref_temp, pref_rpm=pref_rpm, pref_pH=pref_pH)

    if status != 200:
        return "error sending", 500
    
    else: 
        return redirect("/")
        return f"<html><body>preferences set to:</br></br>temp: {pref_temp}</br>rpm: {pref_rpm}</br>pH: {pref_pH}</br></br>:)</body></html>", 200

    return "huh? you shouldn't see this ever", 500

@app.route("/log/<path:filename>")
def logs(filename):
    if os.path.isfile(f"log/{filename}"):
        return send_from_directory("log", filename, cache_timeout=0)
    
    return "file not found", 404

@app.route("/")
def index():
    return send_from_directory("www", "index.html")

@app.route("/<path:path>")
def static_files(path):
    return send_from_directory("www", path)

@app.route("/clearlogs")
def clearlogs():
    os.system("sh tools/clearlogs.sh")
    return redirect("/")

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)
