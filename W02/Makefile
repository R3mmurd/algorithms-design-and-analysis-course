CXX = clang++ -std=c++14

WARN = -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses -Wno-invalid-source-encoding

FLAGS = -D_GLIBCXX__PTHREADS $(WARN)

FLAGS_DEBUG = -O0 -g -DDEBUG $(FLAGS)

FLAGS_RELEASE = -Ofast $(FLAGS)

ALEPH = ~/Aleph-w

INCLUDE = -I. -I $(ALEPH)

LIBS = -L $(ALEPH) -lAleph

qs: qs.C
	$(CXX) $(FLAGS_DEBUG) $(INCLUDE) $@.C -o $@ $(LIBS)

qs-op: qs.C
	$(CXX) $(FLAGS_RELEASE) $(INCLUDE) qs.C -o $@ $(LIBS)

clean:
	$(RM) *~ qs qs-op
