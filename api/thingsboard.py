# -*- coding: utf-8 -*-
"""
Created on Mon Dec  5 01:20:21 2022

@authors: Sahil, 0oj
"""

import requests

THINGSBOARD_URL = 'https://demo.thingsboard.io'
DEVICE_ACCESS_TOKEN = 'XfgfJXrjY8PhThCamEdq'
DEVICE_ID = "5b6712d0-736b-11ed-8cca-2dceeb936109"

class DB:
    def __init__(self, url, access_token, device_id):
        self.url = url
        self.access_token = access_token
        self.device_id = device_id
        self.url = f"{url}/api/v1/{access_token}/attributes"
        self.headers = {
            "Content-Type": "application/json"
        }
    
    def send(self, **data):
        response = requests.post(self.url, json=data, headers=self.headers)
        return response.status_code
    
    def get(self, pref_or_curr="curr"):
        response = requests.get(self.url)
        json = response.json()["client"]
        if pref_or_curr == "pref":
            data = {
                "pref_temp":    json["pref_temp"],
                "pref_rpm":     json["pref_rpm"],
                "pref_pH":      json["pref_pH"]
            }
        elif pref_or_curr == "curr":
            data = {
                "curr_temp":    json["curr_temp"],
                "curr_rpm":     json["curr_rpm"],
                "curr_pH":      json["curr_pH"]
            }
        return data

def default_db():
    return DB(THINGSBOARD_URL, DEVICE_ACCESS_TOKEN, DEVICE_ID)

if __name__ == "__main__":
    db = DB(THINGSBOARD_URL, DEVICE_ACCESS_TOKEN, DEVICE_ID)
    print(db.send(pref_temp=23, pref_rpm=5000, pref_pH=7))
    print(db.send(curr_temp=13, curr_rpm=8000, curr_pH=12))
    print(db.get())
