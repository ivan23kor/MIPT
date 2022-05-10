# -*- coding: utf-8 -*-
import os
import re


def initial_parsing(image):
    text = image[:-3] + 'txt'
    # os.system('cp ../Test_photos/second_eng.txt {1}'.format(image, text))
    exe = os.path.join(os.getcwd(), 'parser/process.py')
    os.system('python {exe} \"{image}\" \"{text}\"'.format(exe=exe, image=image,
                                                           text=text))

    return text


"""
Args:
  lines pertinents to the problem only
"""
def parse_problem1(lines):
    params = []

    for line in lines:
        probabilities = re.findall('[0-9]+ ?\/ ?[0-9]+', line)
        for probability in probabilities:
            params.append(probability)

    return params

def parse_problem2(lines):
    params = []

    for line in lines:
        numbers = re.findall('[0-9]+ ?[.,]{1} ?[0-9]+ ?[.,]{1} ?[0-9]+', line)
        if numbers:
            for number in numbers[0].split(' '):
                params.append(number.strip(',.'))

    # modulo
    params.append('499')

    return params

def parse_problem3(lines):
    params = []

    for line in lines:
        bits = re.findall('[01]{1} ?[,.]{1} ?', line)
        if bits:
            params = [bit.strip(' ,.') for bit in bits]

    return params

def parse_problem4(lines):
    params = []

    for line in lines:
        nums = re.findall('[0-9]+[,.]{1} ?[0-9]+[,.]{1} ?[0-9]+', line)
        if nums:
            for num in nums[0].replace(' ', '').replace('.', '.').split(','):
                params.append(num)
            break
        
    for line in lines:
        num = re.findall('[a-zA-Z] [0-9]+ [a-zA-Z]', line)
        if num:
            params.append(num[0][2:-2])

    return params

def parse_problem5(lines):
    params = []

    for line in lines:
        keys = re.findall('[\=\*]{1} ?[0-9]+', line)
        for key in keys:
            params.append(key.replace('*', '=').replace(' ', '').split('=')[-1])

    return params

def parse_problem6(lines):
    params = []

    for line in lines:
        keys = re.findall('[\=\*]{1} ?[0-9]+', line)
        for key in keys:
            params.append(key.replace('*', '=').replace(' ', '').split('=')[-1])

    return params

def parse_problem7(lines):
    params = []

    for line in lines:
        keys = re.findall('[\=\*]{1} ?[0-9]+', line)
        for key in keys:
            params.append(key.replace('*', '=').replace(' ', '').split('=')[-1])

    # OCR often confuses 9 with 0
    if params[-1] == '0':
        params[-1] = '9'

    return params

def parse_problem8(lines):
    params = []

    for line in lines:
        keys = re.findall('[\=\*]{1} ?[0-9]+', line)
        for key in keys:
            params.append(key.replace('*', '=').replace(' ', '').split('=')[-1])

    return params

    return params

def parse_problem9(lines):
    params = []

    for line in lines:
        equation = re.findall('[\+\-]{1}[ 0-9]+[rxz]{1} ?[\+\-]{1}[ 0-9]+', line)
        if equation:
            a_b = equation[0].replace(' ', '').replace('+', '')
            for char in 'rxz':
                if len(a_b.split(char)) == 2:
                    params.append(a_b.split(char)[0])
                    params.append(a_b.split(char)[1])

    params.append('11')
    return params

def parse_problem10(lines, problem9):
    params = []

    for line in lines:
        point = re.findall('\( ?-?[0-9]+ ?[;:]{1} ?-?[0-9]+ ?\)', line)
        if point:
            coords = point[0].replace(':', ';').replace(' ', '').split(';')
            params.append(coords[0][1:])
            params.append(coords[1][:-1])

    params.extend(problem9)
    return params

def parse_problem11(lines, problem9):
    params_ranges = [(52, 62), ()]
    params = []

    m = re.findall('((m|ni|in) ?[\=\*]{1} ?[0-9]+)', lines[0][47:57])
    if m:
        params.append(m[0][0].replace('*', '=').replace(' ', '').split('=')[-1])

    params.extend(problem9)

    G = re.findall('[GOC0]{1} ?\( ?-?[0-9]+ ?[;:]{1} ?-?[0-9]+ ?\)', lines[1])
    if G:
        coords = G[0].replace(':', ';').replace(' ', '').split(';')
        params.append(coords[0][2:])
        params.append(coords[1][:-1])

    for line in lines[1:3]:
        size = re.findall('\-? ?[0-9]+ ?\. *O', line)
        if size:
            params.append(size[0].split('.')[0])
            break

    Q = re.findall('[QOC0]{1} ?\( ?-?[0-9]+ ?[;:]{1} ?-?[0-9]+ ?\)', lines[2])
    if Q:
        coords = Q[0].replace(':', ';').replace(' ', '').split(';')
        params.append(coords[0][2:])
        params.append(coords[1][:-1])

    for line in lines[len(lines) - 2:]:
        k = re.findall('k ?[m=]{1} ?[0-9]+\. *$', line.rstrip())
        if k:
            params.append(k[0].replace('m', '=').split('=')[-1][:-1])

    return params

def parse_lines_to_params(lines):
    params = []

    beginnings = dict(zip([i for i in range(1, 12)], [None]*11))
    for num, line in enumerate(lines):
        # Segregate on problems
        matching_lines = re.findall('^([1-9]{1}|10|11){1}\.', line.strip())
        if matching_lines:
            problem_num = int(matching_lines[0])
            beginnings[problem_num] = num
            if problem_num == 4 and lines[num + 1].find('RSA') != -1:
                beginnings[problem_num + 1] = num + 1

    i = 1
    for i in range(1, 9):
        if beginnings[i] and beginnings[i + 1]\
                         and beginnings[i + 1] > beginnings[i]:
            method = globals().get('parse_problem{0}'.format(i))
            params.append(method(lines[beginnings[i]:beginnings[i + 1]]))
        else:
            params.append([])

    i = 9
    if beginnings[i] and beginnings[i + 1]\
                         and beginnings[i + 1] > beginnings[i]:
        problem9 = parse_problem9(lines[beginnings[i]:beginnings[i + 1]])
        params.append(problem9)
    else:
        params.append([])

    i = 10
    if beginnings[i] and beginnings[i + 1]\
                         and beginnings[i + 1] > beginnings[i]:
        params.append(parse_problem10(lines[beginnings[i]:beginnings[i + 1]],
                                      problem9))
    else:
        params.append([])

    i = 11
    if beginnings[i]:
        params.append(parse_problem11(lines[beginnings[i]:], problem9))
    else:
        params.append([])

    return params

def parse_image(image):
    result = []

    text = initial_parsing(image)
    
    with open(text, 'r') as file:
        result = parse_lines_to_params(file.readlines())

    return result


# if __name__ == '__main__':
#     with open('../Test_photos/second_eng.txt', 'r') as file:
#         print(parse_lines_to_params(file.readlines()))
