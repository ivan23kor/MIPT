import email
import imaplib
import os
import re
import smtplib
import sys
import time

from email.mime.application import MIMEApplication
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email_settings import *
from os.path import basename
from settings import *


def printf(string):
    string_to_print = string
    sys.stdout.write(string_to_print)
    sys.stdout.flush()


def save_image(mail):
    email_addr = ''
    image = NO_IMAGE
    messages = []
    try:
        mail.select('inbox')

        type, messages = mail.search(None,
                                     'UnSeen',
                                     '(SUBJECT \"{0}\")'.format(SECRET_SUBJECT))

        for mail_id in messages[0].split():
            typ, messages = mail.fetch(mail_id, '(RFC822)')
            for response in reversed(messages):
                if isinstance(response, tuple):
                    msg = email.message_from_string(response[1])
                    email_addr = email.utils.parseaddr(msg['From'])[1]
                    image = save_attachment(msg, email_addr)
                    if image != NO_IMAGE:
                        break

    except Exception as e:
        raise RuntimeError('Saving image from {0} failed.'.format(email_addr))

    return (email_addr, image)


def save_attachment(msg, email_addr, download_folder='media'):
    att_path = NO_IMAGE
    for part in msg.walk():
        if part.get_content_maintype() == 'multipart':
            continue
        if part.get('Content-Disposition') is None:
            continue

        filename = email_addr + '.' + part.get_filename().split('.')[-1]
        att_path = os.path.join(os.getcwd(), download_folder, filename)

        if not os.path.isfile(att_path):
            file = open(att_path, 'wb')
            file.write(part.get_payload(decode=True))
            file.close()
        else:
            print('File {0} already exists'.format(att_path))
        break

    return att_path


def get_msg_text(problems):
    PARAM_NAMES = [['px1', 'px2', 'pz1', 'pz2'], ['el1', 'el2', 'el3', 'mod'],
                   ['bit{}'.format(i) for i in range(1, 12)],
                   ['num1', 'num2', 'num3', 'num'], ['n', 'e', 'c'],
                   ['n', 'e', 'm'], ['p', 'g', 'y', 'x', 'M', 'k'],
                   ['p', 'g', 'y', 'x', 'M', 'k'], ['a', 'b', 'mod'],
                   ['x', 'y', 'a', 'b', 'mod'],
                   ['m', 'a', 'b', 'mod', 'Gx', 'Gy', 'size', 'Qx', 'Qy', 'k']]
    problems_with_names = zip(PARAM_NAMES, problems)

    # Header
    tab = '&nbsp;&nbsp;&nbsp;&nbsp;'
    text = ('<p style="text-align: center;"><b style="color: rgb(0, 153, 0); '
            + 'font-size: 40px;">Important!</b></p>')
    # Rules
    text += ('<p style="font-style: oblique; font-size:19px;">'
             + 'Check the problems input parameters and send back the correct'
             + ' version of them.<br>'
             + 'For example, if I sent you "1) px1 = 1/5, px2 = 2/5, pz1 = 3/5,'
             + ' pz2 = 4/5" for problem 1 but the correct probabilities are'
             + ' px1 = 1/5, px2 = 4/5, pz1 = 1/5, pz2 = 4/5, then reply with:'
             + '<br>1) px1 = 1/5, px2 = 4/5, pz1 = 1/5, pz2 = 4/5<br>'
             + 'Do so for every problem parsed in a wrong way and send them all'
             + ' in one message.</p>')
    text += ('<b style="font-size: 21px;"">Make sure you input the problem'
             + ' numbers and the parameters correctly as this is your last'
             + ' chance to affect parsing.</b><br><br>')

    # Problems
    text += '<div style="line-height: 200%">'
    for num, (names, problem) in enumerate(problems_with_names, 1):
        lacking_args_count = len(names) - len(problem)
        for _ in range(lacking_args_count):
            problem.append('?')

        if lacking_args_count != 0:
            text += '<u style="color: rgb(211, 0, 0)">'

        # Append arguments
        text += '{}) '.format(num)
        if num == 3:
            text += 'sequence = {}'.format(problem[0])
            text += (',{tab}{}'*len(problem[1:])).format(*(problem[1:]),tab=tab)
        else:
            text += '{} = {}'.format(names[0], problem[0])
            for (name, val) in zip(names[1:], problem[1:]):
                text += ',{tab}{} = {}'.format(name, val, tab=tab)

        if lacking_args_count != 0:
            text += '</u>'
        text += '<br>'

    # Separating line
    text += '</div><hr>'

    text += ('<br><br>--<br>Best regards,<br>the GetEasy10 team')

    return text

def send_msg(email_addr, text):
    msg = MIMEText(text, 'html', 'utf-8')
    msg['From'] = EMAIL
    msg['Subject'] = SECRET_SUBJECT
    msg['To'] = email_addr

    server = smtplib.SMTP('smtp.gmail.com:587')
    server.ehlo()
    server.starttls()
    server.login(EMAIL, PASSWORD)
    server.sendmail(EMAIL, email_addr, msg.as_string())
    server.quit()

def receive_correction(email_addr, mail):
    mail.select('inbox')

    messages = []
    type, messages = mail.search(None,
                                 'UnSeen',
                                 '(SUBJECT {0})'.format(SECRET_SUBJECT),
                                 '(FROM {0})'.format(email_addr))

    text = ''
    for mail_id in messages[0].split():
        typ, messages = mail.fetch(mail_id, '(RFC822)')
        for response in reversed(messages):
            if isinstance(response, tuple):
                msg = email.message_from_string(response[1])
                if msg.is_multipart():
                    text = msg.get_payload(0).get_payload()

    return text

def get_correct_problems(corrected_text, problems):
    # Formatting reply
    try:
        msg_end = re.search('Check the problems', corrected_text).start()
    except Exception:
        msg_end = 650
    corrected_text = corrected_text[:msg_end]
    corrected_text = re.sub('[ *;]+', '', corrected_text)
    corrected_text = corrected_text.splitlines()

    # Parsing problems
    for line in corrected_text:
        # For every line in the reply that start with: "problem_num)"
        match = re.match('[0-9]{1,2}\)', line)
        if match:
            try:
                num = int(line[:match.end() - 1])
            except TypeError as e:
                raise e
                return problems

            if num == 11:
                line = ''.join((line, corrected_text[corrected_text.index(line) + 1]))

            line = re.sub('[a-zA-Z0-9]+=', '', line)
            line = line.split(',')
            line[0] = line[0][match.end():]
            problems[num - 1] = line

    return problems

def correct_problems(mail, email_addr, problems):
    text = get_msg_text(problems)

    try:
        send_msg(email_addr, text)
    except RuntimeError as e:
        raise e
        return problems

    try:
        corrected_text = receive_correction(email_addr, mail)
        if not corrected_text:
            printf('No corrected messages from {0}. Waiting '.format(
                                                                    email_addr))
        while not corrected_text:
            printf('.')
            time.sleep(RECONNECTION_TIMEOUT)
            corrected_text = receive_correction(email_addr, mail)
    except Exception as e:
        raise RuntimeError('Receiving correction from {0} failed.'.format(
                                                                    email_addr))
        return problems

    try:
        corrected_problems = get_correct_problems(corrected_text, problems)
    except TypeError as e:
        raise TypeError('{0} sent wrong corrections.'.format(email_addr))

    
    return corrected_problems

def send_answer(mail, email_addr, answer_filename):
    msg = MIMEMultipart()
    msg['From'] = EMAIL
    msg['Subject'] = SECRET_SUBJECT
    msg['To'] = email_addr

    msg.attach(MIMEText('Good luck!'))

    with open(answer_filename, 'rb') as answer_file:
        part = MIMEApplication(answer_file.read(), Name=basename('answer.txt'))
    part['Content-Disposition'] = 'attachment; filename=\"{0}\"'.format(
                                                        basename('answer.txt'))
    msg.attach(part)

    try:
        server = smtplib.SMTP('smtp.gmail.com:587')
        server.ehlo()
        server.starttls()
        server.login(EMAIL, PASSWORD)
        server.sendmail(EMAIL, email_addr, msg.as_string())
        server.quit()
    except Exception as e:
        raise RuntimeError('Answer sending to {0} failed.'.format(email_addr))
