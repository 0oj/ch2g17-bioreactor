# -*- coding: utf-8 -*-
"""
Created on Mon Dec  5 01:20:21 2022

@author: Sahil
"""

import requests
THINGSBOARD_URL = 'https://demo.thingsboard.io'
DEVICE_ACCESS_TOKEN = 'XfgfJXrjY8PhThCamEdq'
url = "https://demo.thingsboard.io/api/v1/XfgfJXrjY8PhThCamEdq/telemetry"
data = {
        "j,djkdn": 6060
        }
header = {
    'Content-Type': 'application/json'
    }
response = requests.post(url, json = data, headers = header)
print(response.status_code)