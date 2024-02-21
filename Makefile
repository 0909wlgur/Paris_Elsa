CC = g++
CXXFLAGS = -g -Wall
OBJS = find_max_batch.o find_partition_ratio.o determine_gpu_partition.o paris.o\
allocate_mig.o mig.o\
elsa_util.o schedule_new_query.o schedule_when_emergency.o elsa.o test_main.o 
TARGET = test_main
 
$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS)

test_main.o: paris.o allocate_mig.o elsa.o 
	$(CC) $(CXXFLAGS) -c test_main.cpp

globals.o:
	$(CC) $(CXXFLAGS) -c globals.cpp

find_max_batch.o: globals.o
	$(CC) $(CXXFLAGS) -c find_max_batch.cpp

find_partition_ratio.o: globals.o
	$(CC) $(CXXFLAGS) -c find_partition_ratio.cpp

determine_gpu_partition.o: globals.o
	$(CC) $(CXXFLAGS) -c determine_gpu_partition.cpp

paris.o: find_max_batch.o find_partition_ratio.o determine_gpu_partition.o
	$(CC) $(CXXFLAGS) -c paris.cpp

mig.o: globals.o
	$(CC) $(CXXFLAGS) -c mig.cpp

allocate_mig.o: mig.o
	$(CC) $(CXXFLAGS) -c allocate_mig.cpp

elsa_util.o:
	$(CC) $(CXXFLAGS) -c elsa_util.cpp

schedule_new_query.o: elsa_util.o
	$(CC) $(CXXFLAGS) -c schedule_new_query.cpp

schedule_when_emergency.o: elsa_util.o
	$(CC) $(CXXFLAGS) -c schedule_when_emergency.cpp

elsa.o: schedule_new_query.o schedule_when_emergency.o elsa_util.o
	$(CC) $(CXXFLAGS) -c elsa.cpp

clean:
	rm -f *.o $(TARGET)