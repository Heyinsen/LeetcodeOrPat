f1=open("data.in","r")
f2=open("data.out","r")
lines_a=f1.readlines()
lines_b=f2.readlines()
flag=1
for i in range(0,len(lines_a)):
    if(lines_a[i] != lines_b[i]):
        print(i)
        flag=0
        break
if(flag):
    print("ok")