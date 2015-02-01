#include<iostream>  
#include <opencv2/core/core.hpp>    
#include <opencv2/highgui/highgui.hpp>    
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;  
using namespace cv;

//use bubble sort to calculate the median value of the matrix
uchar medValue(uchar* array, int length){
    uchar* temp=array;
	uchar  data=0;
	for(int i=0;i<length;i++){
		temp=array;
		for(int j=0;j<length-i;j++){
		   if(*temp>*(temp+1))
		   { 
			   data=*temp;
			   *temp=*(temp+1);
			   *(temp+1)=data;
			   temp++;
		   }
		   else temp++;
		}
	}
	return *(array+(length-1)/2);
}

//convert BGR color to gray color
void toGray(cv::Mat &image,cv::Mat &gray){
    int nl=image.rows;
	int nc=image.cols;
	for(int j=0;j<nl;j++){
	   uchar* data=image.ptr<uchar>(j);
	   uchar* data2=gray.ptr<uchar>(j);
	   for(int i=0;i<nc;i++){
	    data2[i]=(11*data[3*i+0]+59*data[3*i+1]+30*data[3*i+2])/100;       //only use mul to reduce the amount of computation
	   }
	}
}

/*medianBlur realized by myself
**
**to reduce some salt and pepper noise, ksize is 7
*/
void medianBlur(cv::Mat &image,cv::Mat &result){
	int nl=image.rows;
	int nc=image.cols;
    uchar* windowdata=new uchar[7*7];
	memset(windowdata,0,7*7*sizeof(uchar)); //set to 0
    uchar* temp=windowdata;

	int size=3; //(7-1)/2

	for(int j=size;j<nl-size;j++){
	   for(int i=size;i<nc-size;i++){
		   temp=windowdata;
		   for(int m=-size;m<=size;m++){
			   uchar* data=image.ptr<uchar>(j+m);
			   for(int n=-size;n<=size;n++){
	              *temp++=data[i+n];
			   }
		   }
           uchar* data2=result.ptr<uchar>(j);
		   data2[i]=medValue(windowdata,7*7);
	   }
	}
}

/*laplacianfilter realized by myself
**
**to get the edge of the gray image, size is 5
*/
void Laplacian(cv::Mat &image,cv::Mat &result){
	Mat kernel=(Mat_<double>(5,5) << 0,0,-1,0,0,0,-1,-2,-1,0,-1,-2,17,-2,-1,0,-1,-2,-1,0,0,0,-1,0,0);
    filter2D(image,result,CV_8U,kernel);
    int nl=image.rows;
	int nc=image.cols;

	for(int j=2;j<nl-2;j++){
	   uchar* previous2=image.ptr<uchar>(j-2);
	   uchar* previous1=image.ptr<uchar>(j-1);
	   uchar* current=image.ptr<uchar>(j);
	   uchar* next1=image.ptr<uchar>(j+1);
       uchar* next2=image.ptr<uchar>(j+2);
	   uchar* output=result.ptr<uchar>(j);
	   for(int i=2;i<nc-2;i++){
		   *output++=cv::saturate_cast<uchar>(
			   previous2[i-2]*kernel.at<double>(0,0)+previous2[i-1]*kernel.at<double>(0,1)+previous2[i]*kernel.at<double>(0,2)+previous2[i+1]*kernel.at<double>(0,3)+previous2[i+2]*kernel.at<double>(0,4)+
			   previous1[i-2]*kernel.at<double>(1,0)+previous1[i-1]*kernel.at<double>(1,1)+previous1[i]*kernel.at<double>(1,2)+previous1[i+1]*kernel.at<double>(1,3)+previous1[i+2]*kernel.at<double>(1,4)+
			   current[i-2]*kernel.at<double>(2,0)+current[i-1]*kernel.at<double>(2,1)+current[i]*kernel.at<double>(2,2)+current[i+1]*kernel.at<double>(2,3)+current[i+2]*kernel.at<double>(2,4)+
			   next1[i-2]*kernel.at<double>(3,0)+next1[i-1]*kernel.at<double>(3,1)+next1[i]*kernel.at<double>(3,2)+next1[i+1]*kernel.at<double>(3,3)+next1[i+2]*kernel.at<double>(3,4)+
			   next2[i-2]*kernel.at<double>(4,0)+next2[i-1]*kernel.at<double>(4,1)+next2[i]*kernel.at<double>(4,2)+next2[i+1]*kernel.at<double>(4,3)+next2[i+2]*kernel.at<double>(4,4));
	   }
	}
    result.row(0).setTo(cv::Scalar(0));
    result.row(1).setTo(cv::Scalar(0));
    result.row(result.rows-2).setTo(cv::Scalar(0));
    result.row(result.rows-1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
    result.col(1).setTo(cv::Scalar(0));
    result.col(result.cols-2).setTo(cv::Scalar(0));
    result.col(result.cols-1).setTo(cv::Scalar(0));
}


int main(int argc, char* argv[]){
	Mat image=cv::imread("yu aoi.jpg");
	Mat gray=Mat(image.size(),CV_8U);
	Mat edge=Mat(image.size(),CV_8U);
	toGray(image,gray);
	medianBlur(gray,gray);
	Laplacian(gray, edge);
	cv::namedWindow("image");
    cv::imshow("origin",image);
	cv::imshow("image",edge);
	cv::imwrite("grayscale oil painting.jpg",edge);
	waitKey(0);
}