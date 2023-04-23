#include <iostream>
extern "C" {
#include "graphio.h" 
}
#include "graph.h"
#include <sys/time.h>
#include <omp.h>
#include <sstream>

#define AM 1
#define AI (AM%2+1)%2

static double timer() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double) (tp.tv_sec) + tp.tv_usec * 1e-6);
}

int main(int argc, char* argv[])
{
    //��������� �������� ������: (��� �����)
    //std::stringstream convert{ argv[1] };
    //int th; convert >> th;
    int th;
    char* s1 = argv[1];

    //������������ �����
    crsGraph gr;
    init_graph(&gr);
    read_mtx_to_crs(&gr, s1);
   
    cout << "\tA graph with " << gr.V << " vertices and " << gr.nz / 2 << " edges is loaded\n\n";
    sort_adj(&gr);

    //������������� ���.�������� ��� k-truss
    int* EdgeSupport = new int[gr.nz / 2];      // ��������� ����� 
    Edge* edTo = new Edge[gr.nz / 2];           // ������ �����
    int* eid = new int[gr.nz];                  // id ����� ��� ������
    for (long i = 0; i < gr.nz / 2; i++) {
        EdgeSupport[i] = 0;
    }
    getEid(&gr, eid, edTo);

    int q[5] = { 1,2,4,8,16 };
    int q0 = 0;
    while (q0 < 5)
    { th = q[q0];
	
    if (th == 1) 
    { //��������������� ��������

        cout << "\tSERIAL:\n";
        //������� ���������
        double triTime = 0;
	double start =  timer();
#if AM
        SupAM(&gr, eid, EdgeSupport);         //���������� ���������  
#endif
#if AI
        SupAI(&gr, edTo, EdgeSupport);        //����������� ���������
#endif
        triTime = timer() - start ;
        cout << "The time support:\t" << (double)triTime << "\n";

        //������� k-truss
        triTime = 0;
	start =  timer();
        K_Truss(&gr, EdgeSupport, edTo, eid);
        triTime = timer() - start ;
        cout << "The time K-truss:\t" << (double)triTime << "\n\n";

        //���������
        Print_res(gr.nz / 2, EdgeSupport);
    }
    else
    { //������������ ��������

        for (long i = 0; i < gr.nz / 2; i++) {
            EdgeSupport[i] = 0;
        }

        cout << "\tPARALLEL " << th << " thread:\n";
        //������� ���������
#pragma omp barrier
        double itime = omp_get_wtime();
        SupP(&gr, eid, EdgeSupport, th);
        double ftime = omp_get_wtime();
        double exec_time = ftime - itime;
        cout << "The time support:\t" << exec_time << "\n";
        //������� k-truss
#pragma omp barrier
        double itime1 = omp_get_wtime();
        PK_Truss(&gr, EdgeSupport, edTo, eid);
        double ftime1 = omp_get_wtime();
        double exec_time1 = ftime1 - itime1;
        cout << "The time K-truss:\t" << exec_time1 << "\n\n";

        //���������
        Print_res(gr.nz / 2, EdgeSupport);

    }

        q0++;
    }
    return 0;
}