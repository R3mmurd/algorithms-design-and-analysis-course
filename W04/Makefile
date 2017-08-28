CXX = clang++ -std=c++14

WARN = -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses -Wno-invalid-source-encoding

FLAGS = -D_GLIBCXX__PTHREADS $(WARN)

FLAGS_DEBUG = -O0 -g -DDEBUG $(FLAGS)

FLAGS_RELEASE = -Ofast $(FLAGS)

ALEPH = ~/Aleph-w

INCLUDE = -I. -I $(ALEPH)

LIBS = -L $(ALEPH) -lAleph -lgsl -lgslcblas

test-bfs: test-bfs.C bfs.H
	$(CXX) $(FLAGS_DEBUG) $(INCLUDE) $@.C -o $@ $(LIBS)

test-bfs-op: test-bfs.C bfs.H
	$(CXX) $(FLAGS_RELEASE) $(INCLUDE) test-bfs.C -o $@ $(LIBS)

test-dfs: test-dfs.C dfs.H
	$(CXX) $(FLAGS_DEBUG) $(INCLUDE) $@.C -o $@ $(LIBS)

test-dfs-op: test-dfs.C dfs.H
	$(CXX) $(FLAGS_RELEASE) $(INCLUDE) test-dfs.C -o $@ $(LIBS)

scc: scc.C
	$(CXX) $(FLAGS_DEBUG) $(INCLUDE) $@.C -o $@ $(LIBS)

scc-op: scc.C
	$(CXX) $(FLAGS_RELEASE) $(INCLUDE) scc.C -o $@ $(LIBS)

clean:
	$(RM) *~ test-bfs test-bfs-op test-dfs test-dfs-op scc scc-op
