#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <iostream>
#include <highgui.h>
#include <opencv2/aruco.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    // read param
    std::string filename = "../default.yaml";
    cv::FileStorage fs(filename, FileStorage::READ);
    if (!fs.isOpened()) 
    {
        cout << "failed to open file " << filename << endl;
        return false;
    }
    double fx, fy, cx, cy, k1, k2, p1, p2, k3;
    int rows, cols;
    fs["fx"] >> fx;
    fs["fy"] >> fy;
    fs["cx"] >> cx;
    fs["cy"] >> cy;
    fs["k1"] >> k1;
    fs["k2"] >> k2;
    fs["p1"] >> p1;
    fs["p2"] >> p2;
    fs["k3"] >> k3;    
    fs["rows"] >> rows;    
    fs["cols"] >> cols;    
    cv::Mat cameraMatrix = (cv::Mat_<float>(3, 3) << fx, 0, cx, 0, fy, cy, 0, 0, 1);
    cv::Mat distCoeffs = (cv::Mat_<float>(5, 1) << k1, k2, p1, p2, k3);
    cv::Size imgSize(rows, cols);

    std::cout<<"cameraMatrixK: "<<cameraMatrix<<std::endl;

    VideoCapture capture("../aruco_slam_data.mp4");
    if(!capture.isOpened())
    {
        cout<<"Movie open Error"<<endl;
        return -1;
    }
    double rate=capture.get(CV_CAP_PROP_FPS);
    cout<<"帧率为:"<<" "<<rate<<endl;
    cout<<"总帧数为:"<<" "<<capture.get(CV_CAP_PROP_FRAME_COUNT)<<endl;
    Mat frame;
    double position=0.0;
    capture.set(CV_CAP_PROP_POS_FRAMES,position);

   cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::generateCustomDictionary(30, 4);

   while (capture.grab()) {
       cv::Mat image, imageCopy;
        if(!capture.read(image))
            break;
       image.copyTo(imageCopy);
       std::vector<int> ids;
       std::vector<std::vector<cv::Point2f>> corners;

       cv::aruco::detectMarkers(image, dictionary, corners, ids);
       // if at least one marker detected
       if (ids.size() > 0) {
           cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
           std::vector<cv::Vec3d> rvecs, tvecs;
           cv::aruco::estimatePoseSingleMarkers(corners, 0.14, cameraMatrix, distCoeffs, rvecs, tvecs);
           cout<<"R :"<<rvecs[0]<<endl;
           cout<<"T :"<<tvecs[0]<<endl;
           // draw axis for each marker
           for(int i=0; i<ids.size(); i++)
               cv::aruco::drawAxis(imageCopy, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);
       }else{
           std::cout<<"No marker detected!\n";
       }
       cv::imshow("out", imageCopy);
       cv::waitKey(50);
       //if (key == 27)1
       // break;
   }
return 0;
}
