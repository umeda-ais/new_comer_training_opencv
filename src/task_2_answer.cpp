/**********************************************************************
   File    task_2.cpp
   Author  abe taiki (19w)
   Environment    ROS_inigo
   OS       Ubuntu 14.04
   StartDay 2019/4/11
**********************************************************************/


/**********************************************************************
   Include Libraries
**********************************************************************/
#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>


/**********************************************************************
   Declare variables
**********************************************************************/


/**********************************************************************
   Globle
**********************************************************************/
cv::Mat color_raw;
cv::Mat display_color;


/**********************************************************************
   Proto_type_Declare functions
**********************************************************************/
void imageCb(const sensor_msgs::ImageConstPtr& rgb_image);
void image_processing(const cv::Mat color_raw);


/**********************************************************************
   Main
**********************************************************************/
int main(int argc, char** argv){

  /* ros関連 */
  ros::init(argc, argv, "image_reading");
  ros::NodeHandle nh;

  /* xtion_データのサブスクライバ */
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub_rgb_image;
  sub_rgb_image = it.subscribe("/camera/rgb/image_raw",1,imageCb);//openni2を使用するとき
  sub_rgb_image = it.subscribe("/usb_cam/image_raw",1,imageCb);//usb_camを使用するとき

  cv::namedWindow("display_gray",cv::WINDOW_AUTOSIZE);

  ros::spin();
  return 0;
}


/**********************************************************************
   rosカメラデータをOpenCVで使えるデータに変換する関数
**********************************************************************/
void imageCb(const sensor_msgs::ImageConstPtr& rgb_image){

  /*--- カメラのデータをopencvで扱える型に変更 ---*/
  cv_bridge::CvImagePtr cv_rgb;
  try{
    cv_rgb = cv_bridge::toCvCopy(rgb_image, sensor_msgs::image_encodings::BGR8);
  } catch(cv_bridge::Exception& e){
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  color_raw  = cv_rgb->image;
  display_color = color_raw.clone();

  image_processing(color_raw);  //画像処理関数(課題２)
}



/**********************************************************************
  画像処理関数(課題２) : グレースケール変換をして表示してみよう(やり方は課題１とほぼ同じだよ
**********************************************************************/
void image_processing(const cv::Mat color_image){
  cv::Mat display_color;
  display_color = color_image.clone();

  cv::Mat gray_image;
  cvtColor(display_color, gray_image, CV_RGB2GRAY);
  cv::imshow("display_gray", gray_image);
  cv::waitKey(10);

}
