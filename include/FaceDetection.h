#ifndef FACEDETECTION_H_
#define FACEDETECTION_H_

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "../include/Customers.h"
#include "../include/Customer.h"
#include <string>
#include <vector>
//#include <Customers.h>

class FaceDetection {
public:
	FaceDetection();
	std::vector<int>* Detect(const std::string& ImageSent, const Customers& customers);
	cv::Size* FindSmallest(const Customers& customers);
	void CreateCollage(const Customers& customers);
	virtual ~FaceDetection();

private:
	void MergeImage(const cv::Mat& original, cv::Mat& destination, int xLocation);
};

#endif /* FACEDETECTION_H_ */
