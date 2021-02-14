//
//  FaceDetector.cpp
//  FaceDetector
//
//  Created by Fabian Töpfer on 02.02.21.
//  Copyright © 2021 baniaf. All rights reserved.
//

#include "FaceDetector.hpp"
#include <sstream>
#include <vector>
#include <string>
#include <opencv4/opencv2/opencv.hpp>
FaceDetector::FaceDetector() :
    m_confidence_threshold(0.5),
    m_input_image_height(300),
    m_input_image_width(300),
    m_scale_factor(1.0),
    m_mean_values({104., 177.0, 123.0}) {
        
    m_network = cv::dnn::readNetFromCaffe("./deploy.prototxt","./res10_300x300_ssd_iter_140000_fp16.caffemodel");
    
    
    if (m_network.empty()) {
        std::ostringstream ss;
        ss << "Failed to load network with the following settings:\n";
        throw std::invalid_argument(ss.str());
    }
}

std::vector<cv::Rect> FaceDetector::detect_face_rects(const cv::Mat &frame) {
    cv::Mat input_blob = cv::dnn::blobFromImage(frame,m_scale_factor,cv::Size(m_input_image_width, m_input_image_height),m_mean_values,false,false);

    m_network.setInput(input_blob, "data");
    cv::Mat detection = m_network.forward("detection_out");
        cv::Mat detection_matrix(detection.size[2],
                detection.size[3],
                CV_32F,
                detection.ptr<float>());
    
    std::vector<cv::Rect> faces;

    for (int i = 0; i < detection_matrix.rows; i++) {
        float confidence = detection_matrix.at<float>(i, 2);

        if (confidence < m_confidence_threshold) {
            continue;
        }
        int x_left_bottom = static_cast<int>(
                detection_matrix.at<float>(i, 3) * frame.cols);

        int y_left_bottom = static_cast<int>(
                detection_matrix.at<float>(i, 4) * frame.rows);

        int x_right_top = static_cast<int>(
                detection_matrix.at<float>(i, 5) * frame.cols);

        int y_right_top = static_cast<int>(
                detection_matrix.at<float>(i, 6) * frame.rows);

        faces.emplace_back(x_left_bottom,
                y_left_bottom,
                (x_right_top - x_left_bottom),
                (y_right_top - y_left_bottom));
    }

    return faces;
}
