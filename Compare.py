from os import system
system("g++ rand.cpp -g -o rand -O2 -std=c++17")
system("g++ std.cpp -g -o std -O2 -std=c++17")
system("g++ temp.cpp -g -o temp -O2 -std=c++17")
for i in range(1,10000):
        system("./rand")
        system("./std")
	system("./temp")
	if( system("diff -w temp.out temp.ans")!= 0 ):
		break
	print(i)
