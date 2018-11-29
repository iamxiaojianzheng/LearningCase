# coding: utf-8

import re


# ## 思路
# 1. 先判断算术式中是否存在非数字、运算符以外的字符，如果有则报错提示！
# 2. 替换算术式中可以合并的运算符，例如：++可以合并为+，+-可以合并为-，等等
# 2. 判断算术式中是否有括号并检查是否成对
# 3. 每次运算都是优先提取出整个算术式中最里层括号中的运算式
# 4. 提取出后，计算结果然后将结果替换之前的运算式
# 5. 重复第3点

# ## 可能会遇到的问题
# 1. 比较麻烦的就是负数问题，但一个式子是这样时：-1--1*-1，处理起来就容易出错，除法同理
# 2. 如何通过正则表达式提取最里层括号中的算术式

# ## 解决办法
#     1. 正确提取出乘除法算术式的正则表达式：'-?(-?\d+\.?\d*\*-?\d+\.?\d*)'，'-?(-?\d+\.?\d*/-?\d+\.?\d*)'
#     2. 提取出最里层括号中的算术式的正则表达式：re.findall('\([^()]*\)', '1+(1+1-((1*1+(2/2)+((-4)+4)))')[-1]



def calculate(formula):
    if check(formula):
        return "输入的算术式有误，请检查后再次尝试！"
    regex = '\([^()]*\)'
    text = format_formula(formula)
    while True:
        kuohao_list = re.findall(regex, text)
        # 如果算术式中存在括号
        if kuohao_list:
            kuohao = kuohao_list[-1]
            # 计算出括号中的表达式结果
            result = operate(kuohao[1:-1])
            # 用结果替换表达式
            text = text.replace(kuohao, str(result))
        else:
            result = operate(text)
            if re.match('-?\d+\.0', result):
                return int(float(result))
            else:
                return float(result)


def operate(formula):
    # 计算不含括号的算术式
    multiply_divide_regex = '-?(-?\d+\.?\d*)([*/])(-?\d+\.?\d*)'
    add_subtract_regex = '(-?\d+\.?\d*)([+\-])(-?\d+\.?\d*)'
    text = formula
    while True:
        multiply_divide = re.findall(multiply_divide_regex, text)
        add_subtract = re.findall(add_subtract_regex, text)
        # 乘除法
        if multiply_divide:
            a, operator, b = multiply_divide[0]
            result = 0
            if operator == '*':
                result = float(a) * float(b)
            else:
                if float(b) == 0:
                    raise ZeroDivisionError('除数不能为0！')
                result = float(a) / float(b)
            text = text.replace(''.join([a, operator, b]), str(result))
        # 加减法
        elif add_subtract:
            a, operator, b = add_subtract[0]
            result = 0
            if operator == '+':
                result = float(a) + float(b)
            else:
                result = float(a) - float(b)
            text = text.replace(''.join([a, operator, b]), str(result))
            # print(text)
        # 最后只剩下结果
        else:
            return text



def check(s):
    # 检查算术式的正确性
    return  re.findall('[^ 0-9+\-*/\(\)]', s) or len(re.findall('\(', s)) != len(re.findall('\)', s))

def format_formula(s):
    # 格式化运算符
    format_dict = {
        '++': '+',
        '--': '+',
        '+-': '-',
        '-+': '-',
        '*+': '*',
        '/+': '/',
        ' ': '',
    }
    for key in format_dict:
        s = s.replace(key, format_dict[key])
    return s


print(calculate('1+2- (3*4 + (78+98*12) + ( (1-2)+45/5 ))'))
