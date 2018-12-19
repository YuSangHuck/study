OBJS = TestMain.o Thread.o TestCase3.o TestCase2.o TestCase1.o Scheduler.o Queue.o Init.o Common.o
# OBJS = Queue.o z.o
LIBS =

CC = gcc
CFLAGS = -g -c
LDFLAGS = -lpthread

TARGET = TestMain.out
# TARGET = z.out

CORE = core
PCH = *.gch

$(TARGET) : $(OBJS) $(LIBS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS) $(LDFLAGS)



# TestMain : $(OBJS)
# 	gcc -o TestMain -g $(OBJS) -lpthread
# TestMain.o : TestCase1.h TestCase2.h TestCase3.h Init.h Scheduler.h Thread.h
# 	gcc -c -g TestMain.c #Thread.h
# Thread.o : Thread.h
# 	gcc -c -g Thread.c
# TestCase3.o : TestCase3.h #Thread.h
# 	gcc -c -g TestCase3.c
# TestCase2.o : TestCase2.h #Thread.h
# 	gcc -c -g TestCase2.c
# TestCase1.o : TestCase1.h #Thread.h
# 	gcc -c -g TestCase1.c
# Scheduler.o : Scheduler.h #Init.h Thread.h Queue.h Common.h
# 	gcc -c -g Scheduler.c
# Queue.o : Queue.h
# 	gcc -c -g Queue.c
# Init.o : Init.h
# 	gcc -c -g Init.c
# Common.o : Common.h
# 	gcc -c -g Common.c
clean:
	rm -f $(OBJS) $(TARGET) $(CORE) $(PCH)
