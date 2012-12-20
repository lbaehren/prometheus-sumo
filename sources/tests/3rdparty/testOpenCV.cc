/***************************************************************************
 *   Copyright (C) 2012                                                    *
 *   Lars B"ahren (lbaehren@gmail.com)                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/*!
  \file testOpenCV.cc
  \brief Test working with OpenCV library
  \ingroup prometheus
  \ingroup tests
  \author Lars Baehren
  \date 2012-12-20

  **OpenCV documentation:**
  \li [Basic structures](http://opencv.willowgarage.com/documentation/basic_structures.html)
  \li [Histograms](http://opencv.willowgarage.com/documentation/cpp/imgproc_histograms.html)
 */

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <opencv2/highgui/highgui_c.h>

// === Helper functions =========================================================

//____________________________________________________________________
//                                                     show_image_info

/*!
  \brief Show contents of IPL image header
  \param filename -- Name of image file to work with.
*/
void show_image_info (std::string const &filename)
{
  // Load image ...
  std::cout << "--> Loading image " << filename << std::endl;
  IplImage* img = cvLoadImage(filename.c_str());

  std::cout << "Summary of image properties:" << std::endl;
  std::cout << "-- sizeof(IplImage) = " << img->nSize     << std::endl;
  std::cout << "-- Dimensions [w,h] = " << img->width << " x " << img->height << " pixels" << std::endl;
  std::cout << "-- Data size        = " << img->imageSize << " bytes" << std::endl;
  std::cout << "-- nof. channels    = " << img->nChannels << std::endl;
  std::cout << "-- Alpha channel    = " << img->alphaChannel << std::endl;
  std::cout << "-- Pixel depth      = " << img->depth     << std::endl;
  std::cout << "-- Data order       = " << img->dataOrder << std::endl;
}

//____________________________________________________________________
//                                                      calc_histogram

/*!
  \brief Compute HSV histogram for the image
  \param filename -- Name of image file to work with.
  \return status  -- Return status of the function.
*/
int calc_histogram (std::string const &filename,
		    bool const &displayImage=true)
{
  int status = 0;
  cv::Mat image = cv::imread(filename.c_str(), CV_LOAD_IMAGE_COLOR);

  // Check for invalid input
  if (image.data) {
    std::cout << "--> Succesfully read image " << filename << std::endl;
  } else {
    std::cout <<  "Could not open or find the image" << std::endl ;
    return -1;
  }

  cv::Mat hsv;
  cv::cvtColor(image, hsv, CV_BGR2HSV);

  int hbins = 64;  /* nof quantization level for Hue        */
  int sbins = 64;  /* nof quantization level for Saturation */
  int histSize[] = {hbins, sbins};
  // hue varies from 0 to 179, see cvtColor
  float hranges[] = { 0, 180 };
  // saturation varies from 0 (black-gray-white) to
  // 255 (pure spectrum color)
  float sranges[] = { 0, 256 };
  const float* ranges[] = { hranges, sranges };
  cv::MatND hist;
  // we compute the histogram from the 0-th and 1-st channels
  int channels[] = {0, 2};

  cv::calcHist (&hsv,      /* HSV channelized image         */
		1,
		channels,  /* Channels for which to compute */
		cv::Mat(), /* Do not use mask               */
		hist,
		2,
		histSize,  /* Histogram quantization levels */
		ranges,
		true, // the histogram is uniform
		false);
  double maxVal=0;
  minMaxLoc(hist, 0, &maxVal, 0, 0);

  int scale = 10;
  cv::Mat histImg = cv::Mat::zeros(sbins*scale, hbins*10, CV_8UC3);

  for( int h = 0; h < hbins; h++ )
    for( int s = 0; s < sbins; s++ ) {
      float binVal = hist.at<float>(h, s);
      int intensity = cvRound(binVal*255/maxVal);
      cv::rectangle( histImg, cv::Point(h*scale, s*scale),
		     cv::Point( (h+1)*scale - 1, (s+1)*scale - 1),
		     cv::Scalar::all(intensity),
		     CV_FILLED );
    }

  if (displayImage) {
    cv::namedWindow( "Image", 1 );
    cv::imshow( "Image", image );
  }

  cv::namedWindow( "H-S Histogram", 1 );
  cv::imshow( "H-S Histogram", histImg );
  cv::waitKey(0);

  return status;
}

// === Program main function ===================================================

//! Program main function
int main (int argc, char *argv[])
{
  int status = 0;
  std::string filename;

  /* Check for command line arguments */
  if (argc>1) {
    filename = std::string(argv[1]);
    // ... and provide a short summary
    show_image_info (filename);
    // Compute histogram
    calc_histogram (filename);
  } else {
    std::cerr << "Now input image specified - aborting!" << std::endl;
    status = -1;
  }

  return status;
}

