import requests

USERNAME = "zcabgai@ucl.ac.uk"
PASSWORD = "btslover123456"

THINGSBOARD_URL = 'https://demo.thingsboard.io'
URL = f"{THINGSBOARD_URL}/api/auth/login"

PAYLOAD = {
    "username": USERNAME,
    "password": PASSWORD
}

HEADERS = {
    'Content-Type': 'application/json'
}

response = requests.post(URL, json=PAYLOAD, headers=HEADERS)

JWT_TOKEN = response.json()["token"]
print(JWT_TOKEN)

'''
curl -v -X POST https://demo.thingsboard.io/api/auth/login \
--header "Content-Type:application/json" \
--data '{"username":"zcabgai@ucl.ac.uk","password": "btslover123456"}'
'''
