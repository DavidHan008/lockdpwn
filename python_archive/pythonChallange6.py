
import re
import zipfile

file = "90052"
zip = zipfile.ZipFile("C:\\Users\\vdl\\Downloads\\channel.zip")
result = ""

while True:
    text = zip.read(file + ".txt")
    file = re.findall("Next nothing is (\d+)",text)

    if file:
        file = "".join(file)
        result += zip.getinfo(file+".txt").comment
    else:
        print result
        exit(0)
    
    
















