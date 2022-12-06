import requests

host_name = "http://demo.thingsboard.io"
access_token = "XfgfJXrjY8PhThCamEdq"
client_keys = "temperature" # you can ony request one at a time, just do a for loop where you change client_keys
shared_keys = "shared1,shared2"

url = f"{host_name}/api/v1/{access_token}/attributes?clientKeys={client_keys}&sharedKeys={shared_keys}"
response = requests.get(url)
responseString = response._content.decode("ascii")