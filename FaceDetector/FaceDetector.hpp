//
//  FaceDetector.hpp
//  FaceDetector
//
//  Created by Fabian Töpfer on 02.02.21.
//  Copyright © 2021 baniaf. All rights reserved.
//

#ifndef FaceDetector_hpp
#define FaceDetector_hpp

#include <stdio.h>
#include <opencv4/opencv2/dnn.hpp>

class FaceDetector{
public:
    explicit FaceDetector();
    
    std::vector<cv::Rect> detect_face_rects(const cv::Mat &frame);
    
private:
    cv::dnn::Net m_network;

    const int m_input_image_width;
    const int m_input_image_height;
    const double m_scale_factor;
    const cv::Scalar m_mean_values;
    const float m_confidence_threshold;
};

#endif /* FaceDetector_hpp */
