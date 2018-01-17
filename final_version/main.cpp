
//opencv
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include "opencv2/bgsegm.hpp"
#include <opencv2/video.hpp>
#include "opencv2/opencv.hpp"
//C
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>
using namespace cv;
using namespace std;

Scalar green = Scalar(0,255,0);
Scalar red = Scalar(0,0,255);
Scalar blue = Scalar(255,255,0);
Scalar yellow = Scalar(0,255,255);

int keyboard; //input from keyboard

// Global variables
Mat frame; //current frame
Mat fgMaskMOG; //fg mask fg mask generated by MOG method
Mat drawing;
Mat output;

Ptr<BackgroundSubtractor> pMOG;


Mat erosion_src, dilation_src, erosion_dst, dilation_dst;
Mat dilation_element, erosion_element;
int dilation_type, erosion_type;

int erosion_elem = 0;
int erosion_size = 3;
int dilation_elem = 0;
int dilation_size = 0;

// MORPH_RECT = 0
// MORPH_ELLIPSE = 1
// MORPH_CROSS = 2
int morph_elem = 0;
// Kernel size
int morph_size = 6;
int morph_operator = 0;
Mat erode_element = getStructuringElement( morph_elem,
                         Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                         Point( erosion_size, erosion_size ) );
Mat dst;
int thresh = 0;
int thresh_max = 255;
int max_thresh = 255;

int columnsNumber = 640;
int maxLinePosition = 300;
int linePosition=75;

RNG rng(12345);
Mat threshold_output;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;

int poly = 3;
int maxPoly = 3;

int numberOfProducts = 0;
int frameNumber = 0;
double percentageAvg = 0;
double percentage = 50;
int totalPointsInArea = 0;
int approach=1;



/*
0: SQDIFF 
1: SQDIFF NORMED 
2: TM CCORR 
3: TM CCORR NORMED  
4: TM COEFF  
5: TM COEFF NORMED
*/
int match_method = 5;
int tmpCounterMatch = 0;
Mat spliter, resultMatching;
bool changeClientMarker = false;
Mat resultSpliterMatching;

/* Functions headers */
float euclideanDist(Point2f& p, Point2f& q);
Mat thresh_callback(Mat src, String mask_type, Mat frame);
Mat spliterMatching(Mat);
int processVideo(char* videoFilename);
void Erosion( int, void* );
void Dilation( int, void* );
struct product {
  bool tracked;
  Point2f center;
};

std::map<int, product> elements_map;

int main(int argc, char* argv[])
{
    //check for the input parameter correctness
    if(argc != 4) {
        cerr <<"Incorret input list" << endl;
        cerr <<"Try ./executable -vid (path to video file)" << endl;
        cerr <<"exiting..." << endl;
        return EXIT_FAILURE;
    }

    spliter = imread("slit.png");

    //create Background Subtractor objects
    pMOG = bgsegm::createBackgroundSubtractorMOG(); //MOG approach
    //pMOG2 = createBackgroundSubtractorMOG2();     //MOG2 approach

    /* 
    //--------------------- EROSION AND DILATION Trackbars ----------------------
    EROSION AND DILATION Trackbars
    // Create windows
    namedWindow( "Erosion Demo", WINDOW_AUTOSIZE );
    namedWindow( "Dilation Demo", WINDOW_AUTOSIZE );
    namedWindow( "morphologyEx", WINDOW_AUTOSIZE );

    // Create Erosion Trackbar
    createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo", &erosion_elem, max_elem,Erosion );
    createTrackbar( "Kernel size:\n 2n +1", "Erosion Demo",&erosion_size, max_kernel_size,Erosion );

    // Create Dilation Trackbar
    createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",&dilation_elem, max_elem,Dilation );
    createTrackbar( "Kernel size:\n 2n +1", "Dilation Demo",&dilation_size, max_kernel_size,Dilation );
    //-------------------------------------------------------------------------------
    */

    namedWindow( "Products Detector", WINDOW_AUTOSIZE );

    //--------------------- Create morphologyEx Trackbar - Uncomment to use  ----------------------
    //createTrackbar( "Morphological elem: 0:Rect  1:Cross  2:Ellipse", "Products Detector",&morph_elem, max_elem);
    //createTrackbar( "Morphological operator: ", "Products Detector",&morph_operator, max_operator);
    //createTrackbar( "Morphological kernel size:", "Products Detector",&morph_size, max_kernel_size);
    //createTrackbarr( "Min Threshold", "Products Detector",&thresh, max_thresh);
    //createTrackbar( "Max Threshold", "Products Detector",&thresh_max, max_thresh);
    //createTrackbar( "Line position", "Products Detector",&linePosition, maxLinePosition);
    createTrackbar( "Draw", "Products Detector",&poly, maxPoly);
    //---------------------------------------------------------------------------------------------
     
    char* p; 
    if(strcmp(argv[1], "-vid") == 0 && (strtol(argv[2], &p, 10) == 1 || strtol(argv[2], &p, 10) == 2)) 
    {   
        approach = strtol(argv[2], &p, 10);      
        //input data coming from a video
        processVideo(argv[3]);
        cout << numberOfProducts << endl;

    }
    else {
        //error in reading input parameters
        cerr <<"Please, check the input parameters." << endl;
        cerr <<"Exiting..." << endl;
        return EXIT_FAILURE;
    }
    //destroy GUI windows
    destroyAllWindows();
    return EXIT_SUCCESS;
}

/**  @function processVideo  */
int processVideo(char* videoFilename) {
    bool playVideo = true;
    char key;
    //create the capture object
    VideoCapture capture(videoFilename);
    if(!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open video file: " << videoFilename << endl;
        exit(EXIT_FAILURE);
    }

    //read input data. ESC or 'q' for quitting
    while( (char)keyboard != 'q' && (char)keyboard != 27){
        //read the current frame
        if(!capture.read(frame)) {
            cerr << "Unable to read next frame." << endl;
            cerr << "Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        resultSpliterMatching = spliterMatching(frame);

        frameNumber ++;

        //update the background model
        Mat closing_output;
        cvtColor(frame, closing_output, CV_RGB2GRAY);

        pMOG->apply(closing_output, fgMaskMOG, 0);

        erode( fgMaskMOG, closing_output, erode_element);
        dilate( closing_output, fgMaskMOG, erode_element);


        if(!fgMaskMOG.empty())
        {  
          drawing = thresh_callback(fgMaskMOG, "mog1", frame);
          namedWindow( "Original Video", WINDOW_AUTOSIZE );
          imshow("Original Video", frame);

          // Add product rectangles detected to original frame
          add(drawing,frame,drawing);
          // Add product change cleint info to original frame
          add(drawing, resultSpliterMatching,drawing);

          if(frameNumber == 0)
          {
            percentage = 50;
          }
          else if(frameNumber % 20 == 0)
          {
            if(percentageAvg*0.0!=0.0)
              percentageAvg = frame.cols/2;

            percentage = (percentageAvg/frame.cols)*100;
            putText(drawing, "UPDATE Direction", cv::Point(frame.cols-150, 20), FONT_HERSHEY_SIMPLEX, 0.7 , red);
            percentageAvg = 0;
          }

          char str1[20];
          char str2[20];
          char str3[20];
          sprintf(str1,"Antennas target direction: %.1f", percentage);
          sprintf(str2,"Products already detected: %d", numberOfProducts);
          
          if(changeClientMarker)
            sprintf(str3,"Change client: True");
          else
            sprintf(str3,"Change client: False");

          putText(drawing, str1, cv::Point(15, 20), FONT_HERSHEY_SIMPLEX, 0.7 , red);
          putText(drawing, str2, cv::Point(15, 40), FONT_HERSHEY_SIMPLEX, 0.7 , red);
          putText(drawing, str3, cv::Point(15, 60), FONT_HERSHEY_SIMPLEX, 0.7 , yellow);

          imshow("Products Detector", drawing);

          if(playVideo){
            key = waitKey(60);
          }else{
            key = waitKey(0);
          }
        }
        if(key == 'p')
          playVideo = !playVideo;  
    }
    //delete capture object
    capture.release();
    return EXIT_SUCCESS;
}

float euclideanDist(Point2f& p, Point2f& q) {
    Point diff = p - q;
    return cv::sqrt(diff.x*diff.x + diff.y*diff.y);
}

/** @function thresh_callback */
Mat thresh_callback(Mat src, String mask_type, Mat frame)
{   
 
  Mat canny_output;

  Canny(src, canny_output, 180, 200, 3, true);

  blur(canny_output, canny_output, Size(11,11));
  

  findContours( canny_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  for (vector<vector<Point> >::iterator it = contours.begin(); it!=contours.end(); )
  {
    if (it->size()< 80)
        it=contours.erase(it);
    else
        ++it;
  }

  Mat mask = Mat::zeros(canny_output.rows, canny_output.cols, CV_8UC1);

  // Get the moments
  vector<Moments> mu(contours.size() );
  for( int i = 0; i < contours.size(); i++ )
  { 
      mu[i] = moments( contours[i], false ); 
  }

  //  Get the mass centers:
  vector<Point2f> mc( contours.size() );

  for( int i = 0; i < contours.size(); i++ )
  {
    mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
  }

  // Find the rotated rectangles and ellipses for each contour
  vector<RotatedRect> minRect( contours.size() );
  vector<RotatedRect> minEllipse( contours.size() );
  vector<Point> approxShape;

  //First Approach -> minAreaRect
  for( int i = 0; i < contours.size(); i++ )
  { 
       if( contours[i].size() > 90 )
       { 
          minRect[i] = minAreaRect( Mat(contours[i]) );
          minEllipse[i] = fitEllipse( Mat(contours[i]) ); 
       }
  }

  // Draw contours + rotated rects + ellipses
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  line(drawing, Point(0, maxLinePosition-linePosition), Point(drawing.cols, maxLinePosition-linePosition), green, 3);

  line(drawing, Point(0, maxLinePosition*0.6), Point(drawing.cols, maxLinePosition*0.6), red, 3);
  line(drawing, Point(0, maxLinePosition*0.9), Point(drawing.cols, maxLinePosition*0.9), red, 3);

  totalPointsInArea = 0;
  percentageAvg = 0;

  if(approach == 1 ){

    for( int i = 0; i< contours.size(); i++ ){
      
      if(mc[i].y > maxLinePosition*0.6 && mc[i].y < maxLinePosition*0.9)
      {
        totalPointsInArea ++;
        percentageAvg += mc[i].x;
      }

      if(poly == 0)
      {
        
        drawContours( drawing, contours, i, blue, CV_FILLED, 8, hierarchy, 0, Point() );

        if (minEllipse[i].center.y < ((maxLinePosition-linePosition) + 1) && minEllipse[i].center.y > ((maxLinePosition-linePosition) - 1))
        {
          circle(drawing,minEllipse[i].center,10,red, CV_FILLED);
          numberOfProducts ++;
        }  
        else
        {
           circle(drawing,minEllipse[i].center,5,green);
        }
      }
      else if(poly == 1)
      {
          // ellipse
          ellipse( drawing, minEllipse[i], green, 2, 8 );

          if (minEllipse[i].center.y < ((maxLinePosition-linePosition) + 1) && minEllipse[i].center.y > ((maxLinePosition-linePosition) - 1))
          {
            circle(drawing,minEllipse[i].center,10,red, CV_FILLED);
            numberOfProducts ++;
          }  
          else
          {
             circle(drawing,minEllipse[i].center,5,green);
          }
      } 
      else if(poly == 2)
      {
          // rotated rectangle    
          Point2f rect_points[4]; 
          minRect[i].points( rect_points);

          bool draw = true;
          for( int j = 0; j < 4; j++ )
          {
            if(norm(rect_points[j] - rect_points[(j+1)%4]) < 50 )
            {
              draw = false;
              break;
            }
          }

          if(draw)
          {
            for( int j = 0; j < 4; j++ )
            {
              line( drawing, rect_points[j], rect_points[(j+1)%4], blue, 2, 8 );
            }
          }
      }
      else
      {
         

          Point2f rect_points[4]; 
          minRect[i].points( rect_points);

          bool draw = true;
          for( int j = 0; j < 4; j++)
          {
            if(norm(rect_points[j] - rect_points[(j+1)%4]) <= 55 )
            {
              draw = false;
              break;
            }
          }

          if(draw)
          {
            if (mc[i].y < ((maxLinePosition-linePosition) + 1.7) && mc[i].y > ((maxLinePosition-linePosition) - 1.7))
            {
              circle( drawing, mc[i],30, green, -1, 8, 0 );
              numberOfProducts ++;
            }  
            else
            {
              circle( drawing, mc[i],10, red, -1, 8, 0 );
            }

            for( int j = 0; j < 4; j++ )
            {
              line( drawing, rect_points[j], rect_points[(j+1)%4], blue, 2, 8 );
            }
          }
      }
    }
  }else if(approach == 2){
    Point2f new_point;
    Point2f latest_point;
    float euclidean_dist;
    if(elements_map.empty()){
      for( int i = 0; i<mc.size(); i++){
        elements_map[i].center = mc[i];
        elements_map[i].tracked = true; 
      }
    }else{
       for(int i = 0; i<mc.size(); i++){
          if(elements_map.count(i)){
            new_point = Point2f(mc[i].x, mc[i].y);
            for(int j=0; j<elements_map.size(); j++){
                latest_point = elements_map[i].center;
                euclidean_dist = euclideanDist(new_point, latest_point);
                if(euclidean_dist < 250){
                  elements_map[i].center = mc[i];
                }
            }
          }else{
            elements_map[i].center = mc[i];
            elements_map[i].tracked = true; 

          }
          
        }
      }
    
    if(elements_map.size() != 0){

      for( int i = 0; i< elements_map.size(); i++ )
      {
          Scalar green = Scalar(0,255,0);
          Scalar red = Scalar(0,0,255);
          Scalar blue = Scalar(255,255,0);
          
          if(elements_map[i].center.y > maxLinePosition*0.6 && elements_map[i].center.y < maxLinePosition*0.9)
          {
            totalPointsInArea ++;
            percentageAvg += elements_map[i].center.x;
          }

          if (elements_map[i].center.y < (maxLinePosition-linePosition) && elements_map[i].tracked )
          {
           
            numberOfProducts ++;
            elements_map[i].tracked = false;
            
          }  
          
      }
    }
    for( int i = 0; i< contours.size(); i++ ){

      Point2f rect_points[4]; 
      minRect[i].points( rect_points);

      bool draw = true;
      for( int j = 0; j < 4; j++)
      {
        if(norm(rect_points[j] - rect_points[(j+1)%4]) <= 55 )
        {
          draw = false;
          break;
        }
      }

      if(draw)
      {
        if (mc[i].y < ((maxLinePosition-linePosition) + 1.7) && mc[i].y > ((maxLinePosition-linePosition) - 1.7))
        {
          circle( drawing, mc[i],30, green, -1, 8, 0 );
        }  
        else
        {
          circle( drawing, mc[i],10, red, -1, 8, 0 );
        }

        for( int j = 0; j < 4; j++ )
        {
          line( drawing, rect_points[j], rect_points[(j+1)%4], blue, 2, 8 );
        }
      }
    }
  }

  percentageAvg = percentageAvg/totalPointsInArea;

  return drawing;
}

/**  @function spliterMatching  */
Mat spliterMatching(Mat frame)
{
  Mat img_display;
  img_display = frame;

  // Create the result matrix
  int result_cols =  frame.cols - spliter.cols + 1;
  int result_rows = frame.rows - spliter.rows + 1;
  resultMatching.create( result_cols, result_rows, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( frame, spliter, resultMatching, match_method );
  normalize( resultMatching, resultMatching, 0, 1, NORM_MINMAX, -1, Mat() );

  double minVal; 
  double maxVal; 
  Point minLoc; 
  Point maxLoc;
  Point matchLoc;

  // Localizing the best match with minMaxLoc
  minMaxLoc( resultMatching, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

  if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }
  
  Mat tmp = Mat::zeros( img_display.size(), CV_8UC3 );

  if(matchLoc.y > 360)
  {
    tmpCounterMatch ++;
  }
  else
    tmpCounterMatch = 0;

  if(tmpCounterMatch > 8)
  {
    changeClientMarker = true;
    rectangle( tmp, matchLoc, Point( matchLoc.x + spliter.cols , matchLoc.y + spliter.rows ), yellow, 2, 8, 0 );
  }

  return tmp;
}