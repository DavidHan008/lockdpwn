import sys

if len(sys.argv) != 2:
    print "Please supply a filename"
    raise SystemExit(1)

f = open(sys.argv[1])
lines = f.readlines()
f.close()
fvalues = [float(line) for line in lines]

print "The minimum values is " , min(fvalues)
print "The maximum values is " , max(fvalues)
