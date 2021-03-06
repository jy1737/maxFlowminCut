
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include "ibfs.h"


struct timeb t_start, t_current;
#define CLOCK_START (ftime(&t_start))
#define CLOCK_STOP (ftime(&t_current))
#define CLOCK_GET_SECS ( (t_current.time - t_start.time) +		\
		((double)(t_current.millitm - t_start.millitm)) / 1000.)


int main(int argc, char **argv)
{
	if (argc <= 1)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	IBFSGraph *g = new IBFSGraph(IBFSGraph::IB_INIT_FAST);
	for (int iteration=0; (iteration == 0 || g->getFileHasMore()); iteration++)
	{
		double time=0;
		//fprintf(stdout, "c **** iteration %d ****\n", iteration);
		//fflush(stdout);
		//fprintf(stdout, "c parsing %s...\n", argv[1]);
		//fflush(stdout);
		CLOCK_START;
		if (!(g->readFromFileCompile(argv[1]))) {
			return 1;
		}
		CLOCK_STOP;
		double readtime = CLOCK_GET_SECS;
		//fprintf(stdout, "c trivial_flow = %d \n", g->getFlow());
		//fflush(stdout);

		// init
		if (iteration == 0) {
			CLOCK_START;
			g->initGraph();
			CLOCK_STOP;
			time += CLOCK_GET_SECS;
			//fprintf(stdout, "c n = %d\n", g->getNumNodes());
			//fprintf(stdout, "c avg_degree = %.2f\n", g->getNumArcs() / (double)g->getNumNodes());
		}

		//fprintf(stdout, "c running max flow...\n");
		//fflush(stdout);
		CLOCK_START;
		g->computeMaxFlow(g->getFileHasMore());
		CLOCK_STOP;
		time += CLOCK_GET_SECS;
		fprintf(stdout, "Max flow = %d \n", g->getFlow());
		fprintf(stdout, "CPU Load Time: %f ms\n", 1000*readtime);
		//fflush(stdout);
		fprintf(stdout, "IBFS Compute Time: %f ms\n", 1000*time);
		fprintf(stdout, "Total Execution Time: %f ms\n", 1000*readtime + 1000*time);
		fflush(stdout);
	}
	delete g;


	return 0;
}
