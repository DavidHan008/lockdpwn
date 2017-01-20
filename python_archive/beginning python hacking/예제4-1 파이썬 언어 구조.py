#story of "hong gil dong"                                          #(1)

name = "Hong Gil Dong"                                             #(2)
age = 18
weight = 69.3

skill = ["sword","spear","bow","axe"]                              #(3)
power = [98.5, 89.2, 100, 79.2]

querySkill = raw_input("select weapon: ")                          #(4)

print "\n"
print "----------------------------------------"
print "1.name:", name                                              #(5)
print "2.age:", age
print "3.weight:", weight

i=0
print str(123)

for each_item in skill:                                             # (6)
    
(7) if(each_item == querySkill):                                    #(8)
        
(9)     print "4.armed weapon:",each_item, "[ power", power[i],"]"
        print ">>>i am ready to fight"
        
(10) i = i+1                                                        #(11)
        
print "----------------------------------------"
print "\n"

>>> 
select weapon: sword


----------------------------------------
1.name: Hong Gil Dong
2.age: 18
3.weight: 69.3
4.armed weapon: sword [ power 98.5 ]
>>>i am ready to fight
----------------------------------------
