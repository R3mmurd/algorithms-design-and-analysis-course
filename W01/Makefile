CXX = clang++ -std=c++14

WARN = -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses -Wno-invalid-source-encoding

FLAGS = -D_GLIBCXX__PTHREADS $(WARN)

FLAGS_DEBUG = -O0 -g -DDEBUG $(FLAGS)

FLAGS_RELEASE = -Ofast $(FLAGS)

ALEPH = ~/Aleph-w

INCLUDE = -I $(ALEPH)

LIBS = -L $(ALEPH) -lAleph

array-inversions: array-inversions.C
	$(CXX) $(FLAGS_DEBUG) $(INCLUDE) $@.C -o $@ $(LIBS)

array-inversions-op: array-inversions.C
	$(CXX) $(FLAGS_RELEASE) $(INCLUDE) array-inversions.C -o $@ $(LIBS)

clean:
	$(RM) *~ array-inversions array-inversions-op
