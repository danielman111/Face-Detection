#include "../include/FaceDetection.h"

#include <iostream>


FaceDetection::FaceDetection()
{
}

//merge's the original image with the destination image, starting at xLocation on the X axis
void FaceDetection::MergeImage(const cv::Mat& original, cv::Mat& destination, int xLocation)
{
    if (original.size().height > destination.size().height)
        throw ("original image is higher than destination image");
    cv::Rect roi(xLocation, 0, original.size().width, original.size().height); //creates a sqare of the original image size
    cv::Mat imageROI= destination(roi);// marks the area where the original image will be added to the destination
    original.copyTo(imageROI);//merge the original image with the destination image based on the ROI created
}


//returns a pointer to a vector of int's, where, for every detected costumer, inserts his place in the costumers vector, to the returned vector
std::vector<int>* FaceDetection::Detect(const std::string& ImageSent, const Customers& customers)
{
	std::vector<int> *custsDetected= new std::vector<int>;
	cv::CascadeClassifier face_cascade("/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml");
	std::string image= "customers/" + ImageSent;
	cv::Mat OriginalImage = cv::imread(image, CV_LOAD_IMAGE_GRAYSCALE);
	std::vector<cv::Rect> faces;
	face_cascade.detectMultiScale(OriginalImage, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE);
	for (int i= 0; i < customers.GetSize(); i++){
		std::string custName= (customers.GetCustomerAt(i))->getName();
		std::string picPath= "faces/" + custName + "/" + custName + ".tiff";
		cv::Mat custFace= cv::imread(picPath, CV_LOAD_IMAGE_GRAYSCALE);
		int size= faces.size();
		for (int j= 0; j < size; j++){
			cv::Mat faceFound= OriginalImage(faces[j]);
			if (custFace.size() == faceFound.size()) {
					if (cv::countNonZero(custFace != faceFound) == 0)
						custsDetected->push_back(i);
				}
		}
	}
	return custsDetected;
}

//with the given Customers, returns the size of the smallest image of a costumer.
cv::Size* FaceDetection::FindSmallest(const Customers& customers)
{
	int smallest= 99999;
	cv::Size *min= new cv::Size();
	for (int i= 0; i < customers.GetSize(); i++){
		std::string custName= (customers.GetCustomerAt(i))->getName();
		std::string imagePath= "faces/" + custName + "/" + custName + ".tiff";
		cv::Mat curImage= cv::imread(imagePath);
		int curHeight= curImage.cols;
		if (curHeight < smallest){
			smallest= curHeight;
			*min= curImage.size();
		}
	}
	return min;
}

//creates a collage of all the customers who registered the coffee shop
void FaceDetection::CreateCollage(const Customers& customers)
{
	cv::Mat finalImage;
	cv::Mat temp;
	cv::Size *min= FindSmallest(customers);//we creates the collage with the measure, of the smallest image height
	for (int i= 0; i < customers.GetSize(); i++){
		Customer *curCust= customers.GetCustomerAt(i);
		std::string custName= curCust->getName();
		std::string imagePath= "faces/" + custName + "/" + custName + ".tiff";
		cv::Mat curImage= cv::imread(imagePath);
		if (0 == i){//the first image added to the collage
			finalImage= curImage;
			cv::resize(finalImage, finalImage, *min);
		}
		else {//one or more images are already in the collage
			cv::resize(curImage, curImage, *min);
			temp= cv::Mat((*min).height, ((*min).width)*(i+1), CV_8UC3);//creates a blank image with the size of the current collage and the added image
			MergeImage(finalImage, temp, 0);//insert the current collage to the blank image, starting at the leftmostmost area
			MergeImage(curImage, temp, (temp.size().width-curImage.size().width));//added the image to the collage
			finalImage= temp;
		}
	}
	cv::imwrite( "collage.tiff", finalImage);
	delete min;
}

//destructor
FaceDetection::~FaceDetection()
{
}

