//
//  KeyPointDetector.cpp
//  FaceDetector
//
//  Created by Fabian Töpfer on 03.02.21.
//  Copyright © 2021 baniaf. All rights reserved.
//

#include "KeyPointDetector.hpp"

KeyPointDetector::KeyPointDetector() {
    facemark_ = cv::face::FacemarkLBF::create();
    facemark_->loadModel("./lbfmodel.yaml");
};

std::vector<std::vector<cv::Point2f>>
KeyPointDetector::detect_key_points(
        const std::vector<cv::Rect> &face_rectangles,
        const cv::Mat &image) const
{

    cv::InputArray faces_as_input_array(face_rectangles);
    std::vector<std::vector<cv::Point2f> > key_points;
    facemark_->fit(image,
            faces_as_input_array,
            key_points);

    return key_points;
}
