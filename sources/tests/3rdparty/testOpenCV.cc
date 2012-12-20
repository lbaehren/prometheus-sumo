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
 */

#include <iostream>
#include <opencv2/highgui/highgui_c.h>

// === Helper functions =========================================================

/*!
  \brief Show contents of IPL image header
  \param img -- IPL image.
*/
void show_image_info (IplImage* img)
{
  std::cout << "Summary of image properties:" << std::endl;
  std::cout << "-- sizeof(IplImage) = " << img->nSize     << std::endl;
  std::cout << "-- Dimensions [w,h] = " << img->width << " x " << img->height << " pixels" << std::endl;
  std::cout << "-- Data size        = " << img->imageSize << " bytes" << std::endl;
  std::cout << "-- nof. channels    = " << img->nChannels << std::endl;
  std::cout << "-- Alpha channel    = " << img->alphaChannel << std::endl;
  std::cout << "-- Pixel depth      = " << img->depth     << std::endl;
  std::cout << "-- Data order       = " << img->dataOrder << std::endl;
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
    // Load image ...
    std::cout << "--> Loading image " << filename << std::endl;
    IplImage* img = cvLoadImage(filename.c_str());
    // ... and provide a short summary
    show_image_info (img);
  } else {
    std::cerr << "Now input image specified - aborting!" << std::endl;
    status = -1;
  }

  return status;
}

