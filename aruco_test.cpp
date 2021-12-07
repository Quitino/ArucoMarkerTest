#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/aruco.hpp>
// #include <aruco/include/opencv2/aruco.hpp>

// bool readDetectorParameters(std::string filename, cv::Ptr<cv::aruco::DetectorParameters> &params) {
//     cv::FileStorage fs(filename, cv::FileStorage::READ);
//     if(!fs.isOpened())
//         return false;
//     fs["adaptiveThreshWinSizeMin"] >> params->adaptiveThreshWinSizeMin;
//     fs["adaptiveThreshWinSizeMax"] >> params->adaptiveThreshWinSizeMax;
//     fs["adaptiveThreshWinSizeStep"] >> params->adaptiveThreshWinSizeStep;
//     fs["adaptiveThreshConstant"] >> params->adaptiveThreshConstant;
//     fs["minMarkerPerimeterRate"] >> params->minMarkerPerimeterRate;
//     fs["maxMarkerPerimeterRate"] >> params->maxMarkerPerimeterRate;
//     fs["polygonalApproxAccuracyRate"] >> params->polygonalApproxAccuracyRate;
//     fs["minCornerDistanceRate"] >> params->minCornerDistanceRate;
//     fs["minDistanceToBorder"] >> params->minDistanceToBorder;
//     fs["minMarkerDistanceRate"] >> params->minMarkerDistanceRate;
//     fs["cornerRefinementMethod"] >> params->cornerRefinementMethod;
//     fs["cornerRefinementWinSize"] >> params->cornerRefinementWinSize;
//     fs["cornerRefinementMaxIterations"] >> params->cornerRefinementMaxIterations;
//     fs["cornerRefinementMinAccuracy"] >> params->cornerRefinementMinAccuracy;
//     fs["markerBorderBits"] >> params->markerBorderBits;
//     fs["perspectiveRemovePixelPerCell"] >> params->perspectiveRemovePixelPerCell;
//     fs["perspectiveRemoveIgnoredMarginPerCell"] >> params->perspectiveRemoveIgnoredMarginPerCell;
//     fs["maxErroneousBitsInBorderRate"] >> params->maxErroneousBitsInBorderRate;
//     fs["minOtsuStdDev"] >> params->minOtsuStdDev;
//     fs["errorCorrectionRate"] >> params->errorCorrectionRate;
//     return true;
// }

int main(int argc, char *argv[])
{
    
    // read param
    // std::string filename = "../default.yaml";
    std::string filename = "/home/q/develop/DemoSet/ArucoMarkerTest/default.yaml";
    cv::FileStorage fs(filename, cv::FileStorage::READ);
    if (!fs.isOpened()) 
    {
        std::cout << "failed to open file " << filename << std::endl;
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

    // read video
    std::string videoName = "/home/q/develop/DemoSet/ArucoMarkerTest/aruco_slam_data.mp4";
    // std::string videoName = "../aruco_slam_data.mp4";
    cv::VideoCapture capture(videoName);
    if(!capture.isOpened())
    {
        std::cout<<"Movie open Error"<<std::endl;
        return -1;
    }
    double rate=capture.get(CV_CAP_PROP_FPS);
    std::cout<<"FRAME_RATE:"<<" "<<rate<<std::endl;
    std::cout<<"FRAME_COUNT:"<<" "<<capture.get(CV_CAP_PROP_FRAME_COUNT)<<std::endl;
    cv::Mat frame;
    double position=0.0;
    capture.set(CV_CAP_PROP_POS_FRAMES,position);

    // for aruco
    // cv::Ptr<cv::aruco::DetectorParameters> detectorParams = cv::aruco::DetectorParameters::create();
    // bool readOk = readDetectorParameters( filename, detectorParams);
    // if(!readOk) {
    //     std::cerr << "Invalid detector parameters file" << std::endl;
    //     return 0;
    // }
    // override cornerRefinementMethod read from config file
    // detectorParams->cornerRefinementMethod = 1;
    // std::cout << "Corner refinement method (0: None, 1: Subpixel, 2:contour, 3: AprilTag 2): " << detectorParams->cornerRefinementMethod << std::endl;
    // cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::generateCustomDictionary(30, 4);
    // cv::Ptr<cv::aruco::Dictionary> dictionary =  cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
    cv::aruco::Dictionary dictionary =  cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
    // cv::aruco::Dictionary dictionary =  cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
    long int count = 0;
    while (capture.grab()) {
        count ++;
        cv::Mat image, imageCopy;
        if(!capture.read(image))
            break;
        image.copyTo(imageCopy);
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f>> corners;

        // cv::aruco::detectMarkers(image, dictionary, corners, ids, detectorParams);
        cv::aruco::detectMarkers(image, dictionary, corners, ids);
        // if at least one marker detected
        if (ids.size() > 0) {
            cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
            std::vector<cv::Vec3d> rvecs, tvecs;
            cv::aruco::estimatePoseSingleMarkers(corners, 0.14, cameraMatrix, distCoeffs, rvecs, tvecs);
            std::cout<<"R :"<<rvecs[0]<<std::endl;
            std::cout<<"T :"<<tvecs[0]<<std::endl;
            // draw axis for each marker
            for(int i=0; i<ids.size(); i++)
                cv::aruco::drawAxis(imageCopy, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.1);
        }else{
            if( count%40 == 0)
            std::cout<<"No marker detected!\n";
        }
        cv::imshow("out", imageCopy);
        cv::waitKey(50);
        //if (key == 27)1
        // break;
    }
return 0;
}
