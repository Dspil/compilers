import sys
import os

print(os.getcwd())
exe = sys.argv[1]
dout_file = sys.argv[2]
print(dout_file)
out = os.popen("./{}".format(exe)).read().strip().split('\n')
with open(dout_file, 'r') as fhandle:
    dout = fhandle.read().strip().split('\n')
flag = True
for i in range(len(out)):
	if out[i] != dout[i]:
		print("Failure in testcase {}".format(i+1))
		flag = False
if flag:
	print("Success")
