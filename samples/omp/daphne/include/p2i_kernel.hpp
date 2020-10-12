// #ifndef __P2IKERNEL__
// #define __P2IKERNEL__

// #include "benchmark.h"
// #include "p2i_datatypes.h"
// #include <math.h>
// #include <iostream>
// #include <fstream>
// #include <cstring>
// #include <omp.h>
// //#include "../include/meassurement_AverageOnly.h"

// #define MAX_EPS 0.001

// class points2image : public kernel {
// private:
// 	int deviceId = 0;
// private:
// 	// the number of testcases read
// 	int read_testcases = 0;
// 	// testcase and reference data streams
// 	std::ifstream input_file, output_file;
// 	// whether critical deviation from the reference data has been detected
// 	bool error_so_far = false;
// 	// deviation from the reference data
// 	double max_delta = 0.0;
// 	// the point clouds to process in one iteration
// 	PointCloud2* pointcloud2 = nullptr;
// 	// the associated camera extrinsic matrices
// 	Mat44* cameraExtrinsicMat = nullptr;
// 	// the associated camera intrinsic matrices
// 	Mat33* cameraMat = nullptr;
// 	// distance coefficients for the current iteration
// 	Vec5* distCoeff = nullptr;
// 	// image sizes for the current iteration
// 	ImageSize* imageSize = nullptr;
// 	// Algorithm results for the current iteration
// 	PointsImage* results = nullptr;
// public:
// 	/*
// 	 * Initializes the kernel. Must be called before run().
// 	 */
// 	virtual void init();
// 	/**
// 	 * Performs the kernel operations on all input and output data.
// 	 * p: number of testcases to process in one step
// 	 */
// 	virtual void run(int p = 1);
// 	/**
// 	 * Finally checks whether all input data has been processed successfully.
// 	 */
// 	virtual bool check_output();

// protected:
// 	/**
// 	* Reads the next test cases.
// 	* count: the number of testcases to read
// 	* returns: the number of testcases actually read
// 	*/
// 	virtual int read_next_testcases(int count);
// 	/**
// 	 * Compares the results from the algorithm with the reference data.
// 	 * count: the number of testcases processed
// 	 */
// 	virtual void check_next_outputs(int count);
// 	/**
// 	 * Reads the number of testcases in the data set.
// 	 */
// 	int read_number_testcases(std::ifstream& input_file);
// };

// #endif