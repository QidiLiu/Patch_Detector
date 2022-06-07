#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>

/*
===============================================================================
||   Authors   | 劉啟迪(Qidi Liu)
||-------------|---------------------------------------------------------------
||   License   | Private
||-------------|---------------------------------------------------------------
|| Description | 辨識、跟蹤影片中的沉積塊（Patch）並輸出相關信息
===============================================================================
*/

int main(int argc, char*argv[])
{
    cv::String _input_video = "test.avi";
    cv::VideoCapture _cap(_input_video);
    cv::Mat _frame;
    cv::Mat _gray_frame;
    cv::Mat _binary_frame;
    bool _is_first_frame = true;
    double _otsus_threshold;
    cv::Mat _morphology_opened_frame;
    int _morphology_open_ksize = 3;
    cv::Mat _morphology_open_kernel = cv::getStructuringElement(
        cv::MORPH_RECT,
        cv::Size(_morphology_open_ksize, _morphology_open_ksize)
    );
    
    while (true)
    {
        _cap >> _frame;
        if (_frame.empty())
            break;
        cv::cvtColor(_frame, _gray_frame, cv::COLOR_BGR2GRAY);
        //if (_is_first_frame)
        //{
        //    _binary_frame = _gray_frame;
        //    _otsus_threshold = cv::threshold(_gray_frame, _binary_frame, 0, 255, cv::THRESH_OTSU);
        //    _is_first_frame = false;
        //}
        //else
        //    cv::threshold(_gray_frame, _binary_frame, _otsus_threshold, 255, cv::THRESH_BINARY);
        cv::threshold(_gray_frame, _binary_frame, 0, 255, cv::THRESH_OTSU|cv::THRESH_BINARY_INV);
        cv::morphologyEx(
            _binary_frame,
            _morphology_opened_frame,
            cv::MORPH_OPEN,
            _morphology_open_kernel
        );
        cv::namedWindow("Patch Detector");
        cv::imshow("Patch Detector", _morphology_opened_frame);
        if (cv::waitKey(0) == 27)
            break;
    }
    
    return 0;
}