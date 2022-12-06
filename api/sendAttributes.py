# -*- coding: utf-8 -*-
"""
Created on Tue Dec  6 04:03:53 2022

@author: Sahil
"""

import requests

host_name = "http://demo.thingsboard.io"
access_token = "XfgfJXrjY8PhThCamEdq"

url = f"{host_name}/api/v1/{access_token}/attributes"

data = {
    "test": 69,
    "rpm": "deez nuts",
    "temperature" : "rickroll"
}

headers = {
    "Content-Type": "application/json"
}

response = requests.post(url, json=data, headers=headers)
