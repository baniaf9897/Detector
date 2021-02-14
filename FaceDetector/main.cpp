//
//  main.cpp
//  FaceDetector
//
//  Created by Fabian Töpfer on 02.02.21.
//  Copyright © 2021 baniaf. All rights reserved.
//

#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/video/tracking.hpp>


#include <iostream>
#include <opencv2/face.hpp>


#include "FaceDetector.hpp"
#include "ObjectDetector.hpp"
#include "KeyPointDetector.hpp"


#include <dlib/dnn.h>

using namespace dlib;

using namespace std;
using namespace cv;


int main(int argc, const char * argv[]) {

    namedWindow("Detection");
    namedWindow("ObjectTracking");
    namedWindow("ObjectDetection");
    VideoCapture camera("./vid.mp4");
    
    
    FaceDetector detector;
    ObjectDetector objDetector;
    KeyPointDetector keypoint_detector;
    
   
    
    Ptr<Tracker> tracker = TrackerKCF::create();
    

    if(!camera.isOpened()){
           printf("Error cannot open camera");
           return 1;
    };
    
    cv::UMat frame;
    cv::UMat initFrame;
    
//
//    Rect2i roi;
//
//    Mat trackingFrame;
//
//    camera >> trackingFrame;
////
//    roi = selectROI("ObjectTracking",trackingFrame);
//    tracker->init(trackingFrame,roi);
    
//    camera >> initFrame;
//    std::vector<cv::Rect> initRects;
//    initRects.clear();
//    std::vector<Ptr<Tracker>> trackers;
//    trackers.clear();
//
//
//    while(initRects.empty()){
//        initRects = objDetector.detect_object_rects(initFrame);
//
//        for(int i = 0; i < initRects.size(); i++){
//            Ptr<Tracker> tracker = cv::TrackerKCF::create();
//           tracker->init(initFrame,initRects[i]);
//           trackers.push_back(tracker);
//        };
//    }
    
    //std::cout<<"Initial Objects: " <<initRects.size()<<std::endl;
        
    do{
        camera >> frame;
//
//
//        ****************** object tracker  **********************
//        camera >> trackingFrame;
//        tracker->update(trackingFrame,roi);
//        cv::rectangle( trackingFrame, roi, Scalar( 255, 0, 0 ), 2, 1 );
//        imshow("ObjectTracking",trackingFrame);
        
        
//        ****************** facial landmarks **********************

//        auto rects = detector.detect_face_rects(frame);
//        auto keypoint_faces = keypoint_detector
//                       .detect_key_points(rects, frame);
//
//        cv::Scalar color(0, 105, 205);
//
//        for (const auto &face :keypoint_faces) {
//            for (const cv::Point2f &keypoint : face) {
//                cv::circle(frame, keypoint,
//                           2, color, -1);
//            }
//        }
//
       
       std::vector<cv::Rect> objRects = objDetector.detect_object_rects(frame);
//        
//        for(int i = 0; i < trackers.size(); i++){
//            trackers[i]->update(frame, initRects[i]);
//            cv::rectangle( frame, initRects[i], Scalar( 0, 0, 0 ), 2, 1 );
//        };

//        rectangle( frame, roi, Scalar( 255, 0, 0 ), 2, 1 );

//        ****************** going straight for face **********************

        
        
//        std::vector<cv::Rect> faces;
//        cv::face::CParams params("./lbpcascade_frontalface.xml");
//        cv::face::getFaces(frame, faces, &params);
//        for(int j=0;j<faces.size();j++){
//            cv::rectangle(frame, faces[j], cv::Scalar(255,0,255));
//        }
//

        imshow("Detection", frame);

       }while(waitKey(30) < 27);

    return 0;
}
