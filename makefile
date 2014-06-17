CC = g++
CFLAGS  = -g -Wall -Weffc++
LFLAGS = -L/usr/lib -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect -lPocoFoundation -lPocoUtil
IFLAGS=-I/usr/local/include -I/usr/include -I/usr/include/opencv
OFILES = bin/Main.o bin/Simulation.o bin/Customers.o bin/Customer.o bin/RegularCustomer.o bin/VipCustomer.o bin/MyOwnLogger.o bin/FaceDetection.o bin/ItemList.o bin/AllItemList.o

# All Targets
all: sim_coffee_shop


sim_coffee_shop: $(OFILES)
	$(CC) -o bin/sim_coffee_shop $(OFILES) $(LFLAGS)

bin/Main.o: src/Main.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c -Linclude -o bin/Main.o src/Main.cpp

bin/Simulation.o: src/Simulation.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c -Linclude -o bin/Simulation.o src/Simulation.cpp

bin/Customers.o: src/Customers.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c -Linclude -o bin/Customers.o src/Customers.cpp    

bin/Customer.o: src/Customer.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c -Linclude -o bin/Customer.o src/Customer.cpp

bin/RegularCustomer.o: src/RegularCustomer.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c -Linclude -o bin/RegularCustomer.o src/RegularCustomer.cpp

bin/VipCustomer.o: src/VipCustomer.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c -Linclude -o bin/VipCustomer.o src/VipCustomer.cpp

bin/MyOwnLogger.o: src/MyOwnLogger.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c -Linclude -o bin/MyOwnLogger.o src/MyOwnLogger.cpp 

bin/FaceDetection.o: src/FaceDetection.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c -Linclude -o bin/FaceDetection.o src/FaceDetection.cpp

bin/ItemList.o: src/ItemList.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c -Linclude -o bin/ItemList.o src/ItemList.cpp 	

bin/AllItemList.o: src/AllItemList.cpp
	$(CC) $(CFLAGS) $(IFLAGS) -c -Linclude -o bin/AllItemList.o src/AllItemList.cpp

#Clean the build directory
clean:
	rm -f bin/*