/**********************************************************************
   File    task_1_answer.cpp
   Author  umeda hiroki (22w)
   Environment    ROS_noetic
   OS       Ubuntu 20.04
   StartDay 2023/04/
**********************************************************************/


/**********************************************************************
   Include Libraries
**********************************************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


/**********************************************************************
   Declare variables
**********************************************************************/


/**********************************************************************
   Globle
**********************************************************************/



/**********************************************************************
   Proto_type_Declare functions
**********************************************************************/



/**********************************************************************
   Main
**********************************************************************/
int main(int argc, char** argv){

  /* imageという変数を作る */
  cv::Mat image;


  /* sample.pngを読み込む(pathは各自の環境に合わせてください) */
  image = cv::imread("../image_data/sample.png",cv::IMREAD_COLOR);


  /* 生データを表示してみよう */
  cv::namedWindow("display_color",cv::WINDOW_AUTOSIZE);
  cv::imshow("display_color",image);

  /* グレースケール変換をしてみよう */
  cv::Mat gray_image;
  cv::namedWindow("display_gray",cv::WINDOW_AUTOSIZE);
  cvtColor(image, gray_image, cv::COLOR_RGB2GRAY);
  cv::imshow("display_gray", gray_image);

  /* 二値化をしてみよう */
  cv::Mat nichi_image;
  cv::namedWindow("display_nichi", cv::WINDOW_AUTOSIZE);
  threshold(gray_image, nichi_image, 100, 255, cv::THRESH_BINARY);
  cv::imshow("display_nichi", nichi_image);

  /* エッジ検出をしてみよう */
  cv::Mat edge_image;
  cv::namedWindow("display_edge", cv::WINDOW_AUTOSIZE);
  cv::Canny(image,edge_image,100,200);
  cv::imshow("display_edge", edge_image);

  /* 画像の大きさを取得してみよう(行と列) */
  std::cout << image.cols << std::endl;
  std::cout << image.rows << std::endl;

  /* ちょっと応用　緑色抽出*/
  cv::Mat hsv_image;
  cv::Mat mask_green;
  cv::Mat output_hsv;
  cv::namedWindow("display_hsv",cv::WINDOW_AUTOSIZE);
  cvtColor(image,hsv_image,cv::COLOR_BGR2HSV);
  // cv::imshow("display_hsv",hsv_image);
  int green_hue_max = 75;
  int green_hue_min = 70;
  int saturation_max = 255;
  int saturation_min = 100;
  int value_max = 255;
  int value_min = 100;
  cv::Scalar green_max = cv::Scalar(green_hue_max, saturation_max, value_max);
  cv::Scalar green_min = cv::Scalar(green_hue_min, saturation_min, value_min);
  inRange(hsv_image, green_min, green_max, mask_green);
  image.copyTo(output_hsv,mask_green);
  cv::imshow("display_hsv", output_hsv);

  cv::waitKey(0);
  return 0;
}
