
//opencv
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include "opencv2/bgsegm.hpp"
#include <opencv2/video.hpp>
//C
#include <stdio.h>
//C++
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;
// Global variables
Mat frame, firstFrame; //current frame
Mat fgMaskMOG2; //fg mask fg mask generated by MOG2 method

Ptr<BackgroundSubtractor> pMOG;
Ptr<BackgroundSubtractor> pMOG2; //MOG2 Background subtractor
int keyboard; //input from keyboard
void help();
void processVideo(char* videoFilename);
Mat thresh_callback(Mat src);
void help()
{
    cout
    << "--------------------------------------------------------------------------" << endl
    << "This program shows how to use background subtraction methods provided by "  << endl
    << " OpenCV. You can process both videos (-vid) and images (-img)."             << endl
                                                                                    << endl
    << "Usage:"                                                                     << endl
    << "./bs {-vid <video filename>}"                         << endl
    << "--------------------------------------------------------------------------" << endl
    << endl;
}
int main(int argc, char* argv[])
{
    //print help information
    help();
    //check for the input parameter correctness
    if(argc != 3) {
        cerr <<"Incorret input list" << endl;
        cerr <<"exiting..." << endl;
        return EXIT_FAILURE;
    }
    //create GUI windows
    namedWindow("Frame");
    namedWindow("FG Mask MOG 2");
    //create Background Subtractor objects
    pMOG = bgsegm::createBackgroundSubtractorMOG(); //MOG approach
    pMOG2 = createBackgroundSubtractorMOG2(); //MOG2 approach

    if(strcmp(argv[1], "-vid") == 0) {
        //input data coming from a video
        processVideo(argv[2]);
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
void processVideo(char* videoFilename) {
    //create the capture object
    VideoCapture capture(videoFilename);
    if(!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open video file: " << videoFilename << endl;
        exit(EXIT_FAILURE);
    }

    //read input data. ESC or 'q' for quitting
    while( (char)keyboard != 'q' && (char)keyboard != 27 ){
        //read the current frame
        if(!capture.read(frame)) {
            cerr << "Unable to read next frame." << endl;
            cerr << "Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        cv::resize(frame, frame, cv::Size(), 0.25, 0.25);

        //if the first frame is empty, initialize it
        if(firstFrame.empty())
        {
          firstFrame = frame;
          //imshow("First Frame", firstFrame); 
        }

        /*
        Teste de backgroud bubtraction

        //resize the frame, convert it to grayscale, and blur it
        Mat gray;
        cvtColor(frame, gray, CV_RGB2GRAY);
        Mat firstFrameGray;
        cvtColor(firstFrame, firstFrameGray, CV_RGB2GRAY);

        GaussianBlur(gray, gray, Size(21,21), 1, 1);
        //imshow("Gray", gray);


        Mat diffGray;
        absdiff(gray, firstFrameGray, diffGray);

        threshold( diffGray, diffGray, 25, 255, THRESH_BINARY);

        int erosion_elem = 0;
        int erosion_size = 0;
        int dilation_elem = 0;
        int dilation_size = 2;
        int const max_elem = 2;
        int const max_kernel_size = 21;
        
        Mat element = getStructuringElement( MORPH_RECT,
                                             Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                             Point( dilation_size, dilation_size ) );
        dilate( diffGray, diffGray, element );

        imshow("Diff gray", diffGray);

        */







        //Resize image to 1/4
        Mat originalFrame = frame;

        //update the background model
        pMOG->apply(frame, fgMaskMOG2);

        //pMOG2->apply(frame, fgMaskMOG2);

        
        //cv::threshold(frame,frame,1,100,cv::THRESH_BINARY);

        //get the frame number and write it on the current frame
        stringstream ss;
        rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
                  cv::Scalar(255,255,255), -1);
        ss << capture.get(CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        putText(originalFrame, frameNumberString.c_str(), cv::Point(15, 15),
                FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
        //show the current frame and the fg masks
        //imshow("Frame", frame);
        
        //imshow("Original", originalFrame);

        if(!fgMaskMOG2.empty())
        {
        	Mat drawing = thresh_callback(fgMaskMOG2);
        	Mat output;

        	/*
        	double alpha = 0.5; 
        	double beta;
        	beta = ( 1.0 - alpha );
        	//cvtColor(drawing, drawing, CV_GRAY2RGB);
        	
        	//imshow("Original", originalFrame);

			   //addWeighted( drawing, alpha, originalFrame, beta, 0.0, output);
			   */

			add(drawing,originalFrame,output);
      imshow("Products Detector", output);

    	}

        //get the input from the keyboard
        keyboard = waitKey( 30 );
    }
    //delete capture object
    capture.release();
}
/** @function thresh_callback */
Mat thresh_callback(Mat src)
{	

	/*

	Mat mSource_Gray,mThreshold;
	cvtColor(src,mSource_Gray, COLOR_BGR2GRAY);
	//threshold(mSource_Gray,mThreshold,254,255,THRESH_BINARY_INV);

	Mat drawing;
	//findNonZero(mThreshold,drawing);
	//Rect Min_Rect=boundingRect(drawing);
	*/


  int thresh = 0;
  int max_thresh = 255;
  RNG rng(12345);
  Mat threshold_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  //createTrackbar( "Min Threshold:", "Threshold", &thresh, thresh*3, 3 );

  /// Detect edges using Threshold
  threshold( src, threshold_output, thresh, 255, THRESH_BINARY);

  //cvtColor(src, threshold_output, CV_BGR2GRAY);
  //GaussianBlur(src, threshold_output, Size(3,3), 1.5, 1.5);
  //imshow("GaussianBlur", threshold_output);

  //blur( src, threshold_output, Size(7,7) );
  imshow("Blur", threshold_output);
  
  
  //Canny(threshold_output, threshold_output, thresh, max_thresh, 7);
  
  //return threshold_output;

  /// Find contours
  findContours( threshold_output, contours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE, Point(0, 0) );

  vector<RotatedRect> minRect( contours.size() );

  vector<vector<Point> > contours_poly( contours.size() );
  vector<Rect> boundRect( contours.size() );

  imshow("Threshold", threshold_output);

  for( int i = 0; i < contours.size(); i++ )
     {
     //minRect[i] = minAreaRect( Mat(contours[i]) ); 
     
       approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
       boundRect[i] = boundingRect( Mat(contours_poly[i]) );
       /*
        cv::Point2f c;
        float r;
        cv::minEnclosingCircle( contours[i], c, r);
     
        if (!enableRadiusCulling || r >= minTargetRadius)
        {
            center.push_back(c);
            radius.push_back(r);
        }    
        */ 
     }

/*
     /// Draw contours + rotated rects + ellipses
  Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar(0,255,0);
       // contour
       //drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       // rotated rectangle
     	
       Point2f rect_points[4]; minRect[i].points( rect_points );

       for( int j = 0; j < 4; j++ )
       {	
		 Point diff = rect_points[j] - rect_points[(j+1)%4];
    	 printf("%f\n", cv::sqrt(diff.x*diff.x + diff.y*diff.y));  
    	 if(cv::sqrt(diff.x*diff.x + diff.y*diff.y) >= 25.0)   
         	line( drawing, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );
       }
     	
     }
*/


  /// Draw polygonal contour + bonding rects + circles
  Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );

  for( int i = 0; i< contours.size(); i++ )
     {

       Scalar color = Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255));
       //Scalar color = Scalar( 0, 255, 0 );
       //drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
      if ( ((boundRect[i].width * boundRect[i].height) > 1000) )           
		    {
			     rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );
		    }
      }
  //Scalar color = Scalar(0, 255, 0);
  //drawContours( drawing, contours_poly, -1, color, 3);
  
  return drawing;
  
}