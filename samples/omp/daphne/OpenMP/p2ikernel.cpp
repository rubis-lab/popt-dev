/**
 * Author:  Florian Stock, Technische Universität Darmstadt,
 * Embedded Systems & Applications Group 2018
 * Author:  Lukas Sommer, Technische Universität Darmstadt,
 * Embedded Systems & Applications Group 2018
 * License: Apache 2.0 (see attachached File)
 */
#include "benchmark.h"
#include "p2idatatypes.h"
#include "omp_log.hpp"
#include "seq_log.hpp"
#include <cmath>
#include <iostream>
#include <chrono>
#include <fstream>
#include <cstring>
#include <omp.h>
#include <unistd.h>
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
// maximum allowed deviation from the reference results
#define MAX_EPS 0.001

class points2image : public kernel {
private:
	// the number of testcases read
	int read_testcases = 0;
	// testcase and reference data streams
	std::ifstream input_file, output_file;
	// whether critical deviation from the reference data has been detected
	bool error_so_far = false;
	// deviation from the reference data
	double max_delta = 0.0;
	// the point clouds to process in one iteration
	PointCloud2* pointcloud2 = nullptr;
	// the associated camera extrinsic matrices
	Mat44* cameraExtrinsicMat = nullptr;
	// the associated camera intrinsic matrices
	Mat33* cameraMat = nullptr;
	// distance coefficients for the current iteration
	Vec5* distCoeff = nullptr;
	// image sizes for the current iteration
	ImageSize* imageSize = nullptr;
	// Algorithm results for the current iteration
	PointsImage* results = nullptr;
public:
	/*
	 * Initializes the kernel. Must be called before run().
	 */
	virtual void init();
	/**
	 * Performs the kernel operations on all input and output data.
	 * p: number of testcases to process in one step
	 */
	virtual void run(int p = 1, int popt = 1);
	/**
	 * Finally checks whether all input data has been processed successfully.
	 */
	virtual bool check_output();
	OmpLog ol;
protected:
	/**
	* Reads the next test cases.
	* count: the number of testcases to read
	* returns: the number of testcases actually read
	*/
	virtual int read_next_testcases(int count);
	/**
	 * Compares the results from the algorithm with the reference data.
	 * count: the number of testcases processed 
	 */
	virtual void check_next_outputs(int count);
	/**
	 * Reads the number of testcases in the data set.
	 */
	int read_number_testcases(std::ifstream& input_file);
};

/**
 * Parses the next point cloud from the input stream.
 */
void  parsePointCloud(std::ifstream& input_file, PointCloud2* pointcloud2) {
	try {
		input_file.read((char*)&(pointcloud2->height), sizeof(int32_t));
		input_file.read((char*)&(pointcloud2->width), sizeof(int32_t));
		input_file.read((char*)&(pointcloud2->point_step), sizeof(uint32_t));
		pointcloud2->data = new float[pointcloud2->height * pointcloud2->width * pointcloud2->point_step];
		input_file.read((char*)pointcloud2->data, pointcloud2->height * pointcloud2->width * pointcloud2->point_step);
    }  catch (std::ifstream::failure) {
		throw std::ios_base::failure("Error reading the next point cloud.");
    }
}
/**
 * Parses the next camera extrinsic matrix.
 */
void  parseCameraExtrinsicMat(std::ifstream& input_file, Mat44* cameraExtrinsicMat) {
	try {
		for (int h = 0; h < 4; h++)
			for (int w = 0; w < 4; w++)
				input_file.read((char*)&(cameraExtrinsicMat->data[h][w]),sizeof(double));
	} catch (std::ifstream::failure) {
		throw std::ios_base::failure("Error reading the next extrinsic matrix.");		
	}
}
/**
 * Parses the next camera matrix.
 */
void parseCameraMat(std::ifstream& input_file, Mat33* cameraMat ) {
	try {
	for (int h = 0; h < 3; h++)
		for (int w = 0; w < 3; w++)
			input_file.read((char*)&(cameraMat->data[h][w]), sizeof(double));
	} catch (std::ifstream::failure) {
		throw std::ios_base::failure("Error reading the next camera matrix.");
    }
}
/**
 * Parses the next distance coefficients.
 */
void  parseDistCoeff(std::ifstream& input_file, Vec5* distCoeff) {
	try {
		for (int w = 0; w < 5; w++)
			input_file.read((char*)&(distCoeff->data[w]), sizeof(double));
	} catch (std::ifstream::failure) {
		throw std::ios_base::failure("Error reading the next set of distance coefficients.");
	}
}
/**
 * Parses the next image sizes.
 */
void  parseImageSize(std::ifstream& input_file, ImageSize* imageSize) {
	try {
		input_file.read((char*)&(imageSize->width), sizeof(int32_t));
		input_file.read((char*)&(imageSize->height), sizeof(int32_t));
	} catch (std::ifstream::failure) {
		throw std::ios_base::failure("Error reading the next image size.");
	}
}
/**
 * Parses the next reference image.
 */
void parsePointsImage(std::ifstream& output_file, PointsImage* goldenResult) {
	try {
		// read data of static size
		output_file.read((char*)&(goldenResult->image_width), sizeof(int32_t));
		output_file.read((char*)&(goldenResult->image_height), sizeof(int32_t));
		output_file.read((char*)&(goldenResult->max_y), sizeof(int32_t));
		output_file.read((char*)&(goldenResult->min_y), sizeof(int32_t));
		int pos = 0;
		int elements = goldenResult->image_height * goldenResult->image_width;
		goldenResult->intensity = new float[elements];
		goldenResult->distance = new float[elements];
		goldenResult->min_height = new float[elements];
		goldenResult->max_height = new float[elements];
		// read data of variable size
		for (int h = 0; h < goldenResult->image_height; h++)
			for (int w = 0; w < goldenResult->image_width; w++)
			{
				output_file.read((char*)&(goldenResult->intensity[pos]), sizeof(float));
				output_file.read((char*)&(goldenResult->distance[pos]), sizeof(float));
				output_file.read((char*)&(goldenResult->min_height[pos]), sizeof(float));
				output_file.read((char*)&(goldenResult->max_height[pos]), sizeof(float));
				pos++;
			}
	} catch (std::ios_base::failure) {
		throw std::ios_base::failure("Error reading the next reference image.");
	}
}

int points2image::read_next_testcases(int count)
{
	// free the memory that has been allocated in the previous iteration
	// and allocate new for the currently required data sizes
	if (pointcloud2) 
		for (int m = 0; m < count; ++m)
			delete [] pointcloud2[m].data;
	delete [] pointcloud2;
	pointcloud2 = new PointCloud2[count];
	delete [] cameraExtrinsicMat;
	cameraExtrinsicMat = new Mat44[count];
	delete [] cameraMat;
	cameraMat = new Mat33[count];
	delete [] distCoeff;
	distCoeff = new Vec5[count];
	delete [] imageSize;
	imageSize = new ImageSize[count];
	if (results)
	for (int m = 0; m < count; ++m)
	{
		delete [] results[m].intensity;
		delete [] results[m].distance;
		delete [] results[m].min_height;
		delete [] results[m].max_height;
	}
	delete [] results;
	results = new PointsImage[count];
	
	// iteratively read the data for the test cases
	int i;
	for (i = 0; (i < count) && (read_testcases < testcases); i++,read_testcases++)
	{
		try {
			parsePointCloud(input_file, pointcloud2 + i);
			parseCameraExtrinsicMat(input_file, cameraExtrinsicMat + i);
			parseCameraMat(input_file, cameraMat + i);
			parseDistCoeff(input_file, distCoeff + i);
			parseImageSize(input_file, imageSize + i);
		} catch (std::ios_base::failure& e) {
			std::cerr << e.what() << std::endl;
			exit(-3);
		}
	}
	return i;
}
int points2image::read_number_testcases(std::ifstream& input_file)
{
	// reads the number of testcases in the data stream
	int32_t number;
	try {
		input_file.read((char*)&(number), sizeof(int32_t));
	} catch (std::ifstream::failure) {
		throw std::ios_base::failure("Error reading the number of testcases.");
	}

	return number;
}

void points2image::init() {
	std::cout << "init\n";
	
	// open testcase and reference data streams
	input_file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
	output_file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
	try {
		input_file.open("../../../data/p2i_input.dat", std::ios::binary);
	} catch (std::ifstream::failure) {
		std::cerr << "Error opening the input data file" << std::endl;
		exit(-2);
	}
	try {
		output_file.open("../../../data/p2i_output.dat", std::ios::binary);
	} catch (std::ifstream::failure) {
		std::cerr << "Error opening the output data file" << std::endl;
		exit(-2);
	}
	try {
	// consume the total number of testcases
		testcases = read_number_testcases(input_file);
	} catch (std::ios_base::failure& e) {
		std::cerr << e.what() << std::endl;
		exit(-3);
	}
	
	// prepare the first iteration
	error_so_far = false;
	max_delta = 0.0;
	pointcloud2 = nullptr;
	cameraExtrinsicMat = nullptr;
	cameraMat = nullptr;
	distCoeff = nullptr;
	imageSize = nullptr;
	results = nullptr;

	std::cout << "done\n" << std::endl;
}

/**
 * This code is extracted from Autoware, file:
 * ~/Autoware/ros/src/sensing/fusion/packages/points2image/lib/points_image/points_image.cpp
 * It uses the test data that has been read before and applies the linked algorithm.
 * pointcloud2: cloud of points to transform
 * cameraExtrinsicMat: camera matrix used for transformation
 * cameraMat: camera matrix used for transformation
 * distCoeff: distance coefficients for cloud transformation
 * imageSize: the size of the resulting image
 * returns: the two dimensional image of transformed points
 */
PointsImage pointcloud2_to_image(
	const PointCloud2& pointcloud2,
	const Mat44& cameraExtrinsicMat,
	const Mat33& cameraMat, const Vec5& distCoeff,
	const ImageSize& imageSize, int read_testcases, int popt)
{
	// logging
	std::string seq_logger_name = "p2i_tot_" + std::to_string(read_testcases) + "_logger";
	std::string seq_logger_out_path = "p2i_tot_" + std::to_string(read_testcases) + ".out";

	SeqLog sl = SeqLog(seq_logger_name, seq_logger_out_path);
	std::vector<seq_data> seq_data_vec;
	std::string omp_logger_name = "p2i_omp_" + std::to_string(popt) + "_" + std::to_string(read_testcases) + "_logger";
	std::string omp_logger_out_path = "p2i_omp_" + std::to_string(popt) + "_" + std::to_string(read_testcases) + ".out";
	OmpLog ol = OmpLog(omp_logger_name, omp_logger_out_path);
	std::vector<std::vector<omp_data>> omp_data_vec;
	for(unsigned int i = 0; i < 4; i++) {
		std::vector<omp_data> t1;
		omp_data_vec.push_back(t1);
	}

	double seq_start_time = omp_get_wtime();
	double omp_tot = 0.0;
	
	// initialize the resulting image data structure
	int w = imageSize.width;
	int h = imageSize.height;
	PointsImage msg;
	msg.intensity = new float[w*h];
	std::memset(msg.intensity, 0, sizeof(float)*w*h);
	msg.distance = new float[w*h];
	std::memset(msg.distance, 0, sizeof(float)*w*h);
	msg.min_height = new float[w*h];
	std::memset(msg.min_height, 0, sizeof(float)*w*h);
	msg.max_height = new float[w*h];
	std::memset(msg.max_height, 0, sizeof(float)*w*h);
	msg.max_y = -1;
	msg.min_y = h;
	msg.image_height = imageSize.height;
	msg.image_width = imageSize.width;
	int32_t max_y = -1;
	int32_t min_y = h;
	
	// prepare cloud data pointer to read the data correctly
	uintptr_t cp = (uintptr_t)pointcloud2.data;
	
	// preprocess the given matrices
	// transposed 3x3 camera extrinsic matrix
	Mat33 invR;
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			invR.data[row][col] = cameraExtrinsicMat.data[col][row];
	// translation vector: (transposed camera extrinsic matrix)*(fourth column of camera extrinsic matrix)
	Mat13 invT;
	for (int row = 0; row < 3; row++) {
		invT.data[row] = 0.0;
		for (int col = 0; col < 3; col++)
			invT.data[row] -= invR.data[row][col] * cameraExtrinsicMat.data[col][3];
	}
	// apply the algorithm for each point in the cloud
	//numpopt	
	double id1 = 0.0, id2 = 0.0, id3 = 0.0, id4 = 0.0;
	omp_set_dynamic(0);
	#pragma omp parallel num_threads(popt) 
	{
		// #pragma omp parallel for collapse(2) num_threads(popt) schedule(dynamic) nowait
		//#pragma omp for collapse(2) schedule(dynamic) nowait
		for (uint32_t y = 0; y < pointcloud2.height; ++y) {
		// reduction(max : max_y) reduction(min : min_y)
			double omp_start_time = omp_get_wtime();
			#pragma omp for schedule(dynamic) nowait
			for (uint32_t x = 0; x < pointcloud2.width; ++x) {
				float* fp = (float *)(cp + (x + y*pointcloud2.width) * pointcloud2.point_step);
				double intensity = fp[4];
				// apply the transformations
				Mat13 point, point2;
				point2.data[0] = double(fp[0]);
				point2.data[1] = double(fp[1]);
				point2.data[2] = double(fp[2]);
				//point = point * invR.t() + invT.t();
				for (int row = 0; row < 3; row++) {
					point.data[row] = invT.data[row];
					for (int col = 0; col < 3; col++) 
					point.data[row] += point2.data[col] * invR.data[row][col];
				}
				
				if (point.data[2] <= 2.5) {
						continue;
				}

				double tmpx = point.data[0] / point.data[2];
				double tmpy = point.data[1]/ point.data[2];
				double r2 = tmpx * tmpx + tmpy * tmpy;
				double tmpdist = 1 + distCoeff.data[0] * r2
						+ distCoeff.data[1] * r2 * r2
						+ distCoeff.data[4] * r2 * r2 * r2;

				Point2d imagepoint;
				imagepoint.x = tmpx * tmpdist
						+ 2 * distCoeff.data[2] * tmpx * tmpy
						+ distCoeff.data[3] * (r2 + 2 * tmpx * tmpx);
				imagepoint.y = tmpy * tmpdist
						+ distCoeff.data[2] * (r2 + 2 * tmpy * tmpy)
						+ 2 * distCoeff.data[3] * tmpx * tmpy;
				imagepoint.x = cameraMat.data[0][0] * imagepoint.x + cameraMat.data[0][2];
				imagepoint.y = cameraMat.data[1][1] * imagepoint.y + cameraMat.data[1][2];
				int px = int(imagepoint.x + 0.5);
				int py = int(imagepoint.y + 0.5);
				// continue with points inside image bounds
				if(0 <= px && px < w && 0 <= py && py < h)
				{
					int pid = py * w + px;
					// #pragma omp critical
					// {
						if(msg.distance[pid] == 0 ||
							msg.distance[pid] > (point.data[2] * 100.0))
						{
							msg.distance[pid] = float(point.data[2] * 100);
							msg.intensity[pid] = float(intensity);

							max_y = py > max_y ? py : max_y;
							min_y = py < min_y ? py : min_y;

						}
					// }
					// #pragma omp critical
					// {
						if (0 == y && pointcloud2.height == 2)//process simultaneously min and max during the first layer
						{
							float* fp2 = (float *)(cp + (x + (y+1)*pointcloud2.width) * pointcloud2.point_step);
							msg.min_height[pid] = fp[2];
							msg.max_height[pid] = fp2[2];
						}
						else
						{
							msg.min_height[pid] = -1.25;
							msg.max_height[pid] = 0;
						}
					// }
				}
				struct omp_data omp_data;
				int tid = gettid();
				double omp_end_time = omp_get_wtime();
				omp_data.start_t = omp_start_time;
				omp_data.end_t = omp_end_time;
				omp_data.exec_t = (omp_end_time - omp_start_time);
				omp_tot += omp_end_time - omp_start_time;
				omp_data.tid = tid;
				omp_data.iter = read_testcases;
				omp_data.test_case = read_testcases;
				int omp_id = omp_get_thread_num();
				omp_data_vec.at(omp_id).push_back(omp_data);
			}
		}
	}
	

	msg.max_y = max_y;
	msg.min_y = min_y;
	double seq_end_time = omp_get_wtime();
	struct seq_data seq_data;
	seq_data.start_t = seq_start_time;
	seq_data.end_t = seq_end_time;
	seq_data.exec_t = (seq_end_time - seq_start_time);
	seq_data.tid = gettid();
	seq_data.test_case = read_testcases;
	seq_data_vec.push_back(seq_data);
	sl.log_to_file(seq_data_vec);
	ol.log_to_file(omp_data_vec);
	std::cout << "omp_tot: " << omp_tot << std::endl;
	return msg;
}

void points2image::run(int p, int popt) {
	// pause while reading and comparing data
	// only run the timer when the algorithm is active
	// pause_func();
	while (read_testcases < testcases)
	{
		int count = read_next_testcases(p);
		
		for (int i = 0; i < count; i++)
		{
			//omp logging -> for each iteration of pointcloud2_to_image
			results[i] = pointcloud2_to_image(pointcloud2[i],
								cameraExtrinsicMat[i],
								cameraMat[i], distCoeff[i],
								imageSize[i], read_testcases, popt);
		}
		check_next_outputs(count);
	}
}

void points2image::check_next_outputs(int count)
{
	PointsImage reference;
	// parse the next reference image
	// and compare it to the data generated by the algorithm
	for (int i = 0; i < count; i++)
	{
		try {
			parsePointsImage(output_file, &reference);
		} catch (std::ios_base::failure& e) {
			std::cerr << e.what() << std::endl;
			exit(-3);
		}
		// detect image size deviation
		if ((results[i].image_height != reference.image_height)
			|| (results[i].image_width != reference.image_width))
		{
			error_so_far = true;
		}
		// detect image extend deviation
		if ((results[i].min_y != reference.min_y)
			|| (results[i].max_y != reference.max_y))
		{
			error_so_far = true;
		}
		// compare all pixels
		int pos = 0;
		for (int h = 0; h < reference.image_height; h++)
			for (int w = 0; w < reference.image_width; w++)
			{
				// compare members individually and detect deviations
				if (std::fabs(reference.intensity[pos] - results[i].intensity[pos]) > max_delta)
					max_delta = fabs(reference.intensity[pos] - results[i].intensity[pos]);
				if (std::fabs(reference.distance[pos] - results[i].distance[pos]) > max_delta)
					max_delta = fabs(reference.distance[pos] - results[i].distance[pos]);
				if (std::fabs(reference.min_height[pos] - results[i].min_height[pos]) > max_delta)
					max_delta = fabs(reference.min_height[pos] - results[i].min_height[pos]);
				if (std::fabs(reference.max_height[pos] - results[i].max_height[pos]) > max_delta)
					max_delta = fabs(reference.max_height[pos] - results[i].max_height[pos]);
				pos++;
			}
		// free the memory allocated by the reference image read above
		delete [] reference.intensity;
		delete [] reference.distance;
		delete [] reference.min_height;
		delete [] reference.max_height;
	}
}

bool points2image::check_output() {
	std::cout << "checking output \n";
	// complement to init()
	input_file.close();
	output_file.close();
	std::cout << "max delta: " << max_delta << "\n";
	if ((max_delta > MAX_EPS) || error_so_far) {
		return false;
	} else {
		return true;
	}
}
// set the external kernel instance used in main()
points2image c = points2image();
kernel& p2iKernel = c;