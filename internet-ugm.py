import requests
import getpass
import re
from urllib.parse import urlparse
import ipaddress


def internet_connected():
    res = requests.get("http://gamabox.id/", allow_redirects=False)

    if res.status_code == 302 and 'location' in res.headers:
        o = urlparse(res.headers['location'])
        return not private_ip(o.netloc.split(":")[0])
    
    return True

def private_ip(ip_addr):
    try:
        return ipaddress.ip_address(ip_addr).is_private
    except ValueError:
        return False

def login():    
    BASE_URL = "https://sso.ugm.ac.id/cas/login?service=https://internet.ugm.ac.id/sso/login"

    session = requests.Session()

    res = session.get(BASE_URL)

    match = re.search("[A-Z0-9]{96}", res.text)



    data={
        "username": input("Username: "),
        "password": getpass.getpass(),
        "lt": match.group(),
        "_eventId": "submit", 
        "submit": "LOGIN", 
    }

    session.post(BASE_URL, data=data)

if not internet_connected():
    print("Trying to login...")
    login()

    print("Succeed Connected" if internet_connected() else "Not Succeed")