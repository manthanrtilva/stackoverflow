
import sys

fh = open(sys.argv[1],'r')
data = fh.read()
fh.close()

pos = data.find('{')
if pos != -1: # class open
	while True:
		pos = data.find('{',pos+1)
		if pos != -1: # function open
			spos = data.rfind('}',0,pos)
			if spos != -1:
				epos = spos
				while True:
					epos = data.find('}',epos+1)
					if epos == -1:
						break;
					if data.count('{',spos+1,epos) == data.count('}',spos+1,epos+1):
						break;
				print(data[spos+1:epos+1])
				pos = epos + 1
			else:
				spos = data.rfind('{',0,pos)
				if spos != -1:
					epos = spos
					while True:
						epos = data.find('}',epos+1)
						if epos == -1:
							break;
						if data.count('{',spos+1,epos) == data.count('}',spos+1,epos+1):
							break;
					print(data[spos+1:epos+1])
				else:
					print("no start of class")
					break;
				pos = epos + 1
		else:
			break;
		if pos >= len(data):
			break;
else:
	print("Invalid input file")