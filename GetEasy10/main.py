import email
import imaplib
import smtplib
import sys
import time
sys.path.insert(0, './parser/')

from email_settings import *
from parser import *
from preprocessor import preprocess
from problem import solve, problem1_solve
from server import *
from settings import RECONNECTION_TIMEOUT


def printf(string):
    string_to_print = string
    sys.stdout.write(string_to_print)
    sys.stdout.flush()


if __name__ == '__main__':
    # Login
    mail = imaplib.IMAP4_SSL(SMTP_SERVER)
    mail.login(EMAIL, PASSWORD)

    while True:
        email_addr = ''
        image_filename = NO_IMAGE
        problems = []
        # Initializing conversation with user
        try:
            email_addr, image_filename = save_image(mail)
            if image_filename == NO_IMAGE:
                printf('No messages. Waiting ')
            while image_filename == NO_IMAGE:
                printf('.')
                time.sleep(RECONNECTION_TIMEOUT)
                email_addr, image_filename = save_image(mail)

            printf('\n-{}*\n'.format('*-'*39))
            printf('Started working with {}.\n'.format(email_addr))
        except Exception as e:
            printf('Initial messaging failed. ')
            printf('Reason: {0}\n'.format(str(e)))
            printf('\n{}\n'.format('^'*80))
            continue

        # Initial image parsing
        try:
            preprocess(image_filename)
            problems = parse_image(image_filename)
            printf('Parsed image with ABBYY.\n')
        except Exception as e:
            send_msg(email_addr, 'Sorry, image processing failed(')
            printf('Preprocessing or ABBYY failed. ')
            printf('Reason: {0}\n'.format(str(e)))
            printf('\n{}\n'.format('^'*80))
            continue


        # email_addr = 'fedosov.pa@phystech.edu'
        # Human-aided parsing
        try:
            problems = correct_problems(mail, email_addr, problems)
            printf('{} has corrected problems.\n'.format(email_addr))
        except Exception as e:
            send_msg(email_addr, 'Sorry, parsing your parameters failed(')
            printf('Could not get correct parameters. ')
            printf('Reason: {0}\n'.format(str(e)))
            printf('\n{}\n'.format('^'*80))
            continue

        # Solving
        try:
            answer_filename = solve(problems, image_filename)
            printf('I have solved. It was easy!\n')
        except Exception as e:
            send_msg(email_addr, 'Sorry, problem solving failed(')
            printf('I could not solve. It was too hard =(')
            printf('Reason: {0}'.format(str(e)))
            printf('\n{}\n'.format('^'*80))
            continue

        # Sending
        try:
            send_answer(mail, email_addr, answer_filename)
            printf('I am done with user {}.\n'.format(email_addr))
        except Exception as e:
            printf('I could not service user {}. '.format(email_addr))
            printf('Reason: {0}'.format(str(e)))
            printf('\n{}\n'.format('^'*80))
            continue

        printf('\n-{}*\n'.format('*-'*39))

    mail.close()
