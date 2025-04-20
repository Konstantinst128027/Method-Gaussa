CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall
GTEST_LIBS = -lgtest -lgtest_main -pthread
EIGEN = -I/usr/include/eigen3

EXECUTABLE_1 = main
EXECUTABLE_2 = tests
$(EXECUTABLE_1): function.o main.o 
	$(CXX) $(EIGEN) function.cpp main.cpp -o $(EXECUTABLE_1)
$(EXECUTABLE_2): function.o big_test.o gtest_modal_tests.o
	$(CXX) $(CXXFLAGS) $(EIGEN)  function.cpp big_test.cpp gtest_modal_tests.cpp -o $(EXECUTABLE_2) $(GTEST_LIBS)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(EIGEN) -c $< -o $@
clean:
	rm -f *.o
cleanall:
	rm -f *.o $(EXECUTABLE_1) $(EXECUTABLE_2)
