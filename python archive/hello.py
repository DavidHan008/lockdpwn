# -*- coding: utf-8 -*-
if product == "game" and type == "pirate memory" \
               and not (age < 4 or age > 8):
    print "I'll take it!"

    
if suffix == ".htm":
    content = "text/html"

elif suffix == ".jpg":
    content = "image/jpeg"

elif suffix == ".png":
    content = "image/png"

else:
    raise RuntimeError("Unknown content type")

if 'spam' in s:
    has_spam = True
else:
    has_spam = False


has_spam = 'spam' in s



f = open("foo.txt")
line = f.readline()
while line:
    print line,
    line = f.readline()
f.close()

for line in open("foo.txt"):
    print line,


f = open("out","w")
while year <= numyears:
    principal = principal * ( 1 + rate)
    print >> f, "%3d %0.2f" % (year,principal)
    year += 1

f.close


f.write("%3d %0.2f\n" % (year,principal))

import sys
sys.stdout.write("Enter your name : ")
name = sys.stdin.readline()


name = raw_input("Enter your name: ")




a = "Hello World"
b = 'python is groovy'
c = """Computer say 'No'"""


print '''Content-type: text/html
<h1> Hello World </h1>
Click <a href="http://www.python.org">here</a>.'''

a = "Hello World"
b = a[4]
c = a[:5] # c = 'Hello'
d = a[6:] # d = 'World'
e = a[3:8] # e = 'lo Wo'

g = a + " This is a test"

x = '37'
y = '42'
z = x + y # z = 3742
z = int(x) + int(y) # z = 79


s = "The value pf x os " + str(x)
s = "The value pf x os " + repr(x)
s = "The value pf x os " + format(x,'4d')


names = [ 'Dave', 'Mark','Ann','Phill' ]
a = names[2] # a = 'Ann'

namaes[0] = 'Jeff' # 'Dave' --> 'Jeff'

names.append('Paula') # 리스트 끝에 새로운 항목 추가

names.insert(2,'Thomas') # 가운데 새로운 항목 삽입

b = names[0:2] # 'Jeff' ,'Mark' 반환

c = names[2:] # 'Thomas' 'Ann' 'Phill' 'Paula'

names[1] = 'Jeff'

names[0:2] = ['Dave','Mark','Jeff'] # 리스트 교체

a = [1,2,3] + [4,5] # [1,2,3,4,5]

names = []
names = list()


a = [1,'Dave',3.14 ['Mark', 7, 9 [100,101]], 10]


a[1]  # 'Dave'
a[3][2] # '9'
a[3][3][1] # '101'


# tuple
stock = ('G00G',100,490.10)
address = ('www.python.org',80)
person = (first_name , last_name, phone)

a = ( )
b = (item, )
c = item,

name,shares,price = stock
host,prot = address
first_name, last_name, phone= person


filename = 'portfolio.csv'
portfolio = []
for line in open(filename):
    fields = line.split(",")
    name = fields[0]
    shares = int(fields[1])
    price = float(fields[2])
    stock = (name,shares,price)
    portfolio.append(stcok)

total =0.0
for name,shares,price in portfolio:
    total += shares * price
s = set([3,5,9,10])
t = set('Hello')




