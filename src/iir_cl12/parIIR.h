#ifndef PARIIR_H
#define PARIIR_H

#include <clUtil.h>

#define ROWS 256  // num of parallel subfilters

using namespace clHelper;

class ParIIR
{
	// Helper objects
	clRuntime *runtime;
	clFile    *file;

	// svm granuality
	bool svmCoarseGrainAvail;
	bool svmFineGrainAvail;

	// OpenCL resources, auto release 
	cl_platform_id   platform;
	cl_device_id     device;
	cl_context       context;
	cl_program       program;
	cl_command_queue cmdQueue;

	// Parameters
	int len;
    int channels;
	float c;

	float *h_X;
	float *h_Y;

	cl_float2 *nsec;
	cl_float2 *dsec;

	// CPU output for comparison
	float *cpu_y;

	// Memory objects
	//cl_mem d_Mat; // Lenx16x2 :  need 32 intermediate data to merge into 1 final data
	cl_mem d_X;
	cl_mem d_Y;
	cl_mem d_nsec;
	cl_mem d_dsec;

	// User defined kernels
	cl_kernel        kernel_pariir;

	//-------------------------------------------------------------------------------------------//
	// Initialize functions
	//-------------------------------------------------------------------------------------------//
	void Init();
	void InitParam();
	void InitCL();
	void InitKernels();
	void InitBuffers();

	//-------------------------------------------------------------------------------------------//
	// Clear functions
	//-------------------------------------------------------------------------------------------//
	void CleanUp();
	void CleanUpBuffers();
	void CleanUpKernels();

	// Run kernels
	void multichannel_pariir();

	// check the results
	void compare();

public:
	ParIIR(int len);
	~ParIIR();

	void Run();
};

#endif
