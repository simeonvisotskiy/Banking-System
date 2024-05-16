import smtplib
import random
import ssl
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import sys
import os
import json



def send_verification_email(receiver_email):

    sender_email = "simeonvisotskiy@outlook.com"  
    password = os.getenv("EMAIL_PASSWORD")  

    print(f"DEBUG: Retrieved EMAIL_PASSWORD: {password}")

    if not password:
        raise ValueError("Email password not found in environment variables")

    verification_code = str(random.randint(100000, 999999))

    message = MIMEMultipart("alternative")
    message["Subject"] = "Your Verification Code"
    message["From"] = sender_email
    message["To"] = receiver_email

    text = f"Your verification code is: {verification_code}"
    html = f"<html><body><p>Your verification code is: <strong>{verification_code}</strong></p></body></html>"

    part1 = MIMEText(text, "plain")
    part2 = MIMEText(html, "html")

    message.attach(part1)
    message.attach(part2)

    context = ssl.create_default_context()
    with smtplib.SMTP("smtp-mail.outlook.com", 587) as server:
        server.starttls(context=context)
        server.login(sender_email, password)
        server.sendmail(sender_email, receiver_email, message.as_string())


    with open("verification_code.txt", "w") as file:
        file.write(verification_code)

    return verification_code

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python send_email.py <recipient_email>")
        sys.exit(1)

    receiver_email = sys.argv[1]
    send_verification_email(receiver_email)
