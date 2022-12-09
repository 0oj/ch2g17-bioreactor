import time
import random
import thingsboard as tb

db = tb.default_db()

def cheeky_write():
    db.send(curr_temp=random.randint(0, 100), curr_rpm=random.randint(0, 10000), curr_pH=random.randint(0, 14))

def log():
    curr = db.get("curr")
    with open("log/pH", "a") as pH:
        pH.write(f"{time.time()} {curr['curr_pH']}\n")
    with open("log/rpm", "a") as rpm:
        rpm.write(f"{time.time()} {curr['curr_rpm']}\n")
    with open("log/temp", "a") as temp:
        temp.write(f"{time.time()} {curr['curr_temp']}\n")
    print(f"temp: {curr['curr_temp']}, rpm: {curr['curr_rpm']}, pH: {curr['curr_pH']}")

while True:
    try:
        log()
        cheeky_write()
        time.sleep(1)
    except KeyboardInterrupt:
        print("\nbye")
        break
