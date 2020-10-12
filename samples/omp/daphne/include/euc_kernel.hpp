#ifndef __EUCKERNEL__
#define __EUCKERNEL__
/**
 * Author:  Florian Stock, Technische Universität Darmstadt,
 * Embedded Systems & Applications Group 2018
 * License: Apache 2.0 (see attachached File)
 */
#include "benchmark.h"
#include <iostream>
#include <fstream>
#include "euc_datatypes.h"
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include <omp.h>

// algorithm parameters
const int _cluster_size_min = 20;
const int _cluster_size_max = 100000;
const bool _pose_estimation = true;

// maximum allowed deviation from the reference data
#define MAX_EPS 0.001
// number of threads
#define THREADS 512

class euclidean_clustering : public kernel {
private:
	/**
	 * Reads the number of testcases in the data set.
	 */
	int read_number_testcases(std::ifstream& input_file);
	// input point cloud
	PointCloud *in_cloud_ptr = nullptr;
	// colored point cloud
	PointCloudRGB *out_cloud_ptr = nullptr;
	// bounding boxes of the input cloud
	BoundingboxArray *out_boundingbox_array = nullptr;
	// detected centroids
	Centroid *out_centroids = nullptr;
	int * cloud_size;
	// the number of testcases that have been read
	int read_testcases = 0;
	// testcase and reference data streams
	std::ifstream input_file, output_file;
	// indicates an size related error
	bool error_so_far = false;
	// the measured maximum deviation from the reference data
 	double max_delta = 0.0;
public:
	virtual void init();
	virtual void run(int p = 1);
	virtual bool check_output();
protected:
	void clusterAndColor(const PointCloud in_cloud_ptr,
		int cloud_size,
		PointCloudRGB *out_cloud_ptr,
		BoundingboxArray *in_out_boundingbox_array,
		Centroid *in_out_centroids,
		double in_max_cluster_distance);
	/**
	* Cluster the point cloud according to the pairwise point distances.
	* Clustering of the same input data is performed multiple times with different thresholds
	* so that points farther away in the cloud also get assigned to a cluster.
	*/
	void segmentByDistance(const PointCloud in_cloud_ptr,
		int cloud_size,
		PointCloudRGB *out_cloud_ptr,
		BoundingboxArray *in_out_boundingbox_array,
		Centroid *in_out_centroids,
		double in_max_cluster_distance);
	/**
	 * Reads the next testcases.
	 * count: number of testcases to read
	 * return: the number of testcases actually read
	 */
	virtual int read_next_testcases(int count);
	/**
	 * Reads and compares algorithm outputs with the reference result.
	 * count: the number of outputs to compare
	 */
	virtual void check_next_outputs(int count);
};

#endif