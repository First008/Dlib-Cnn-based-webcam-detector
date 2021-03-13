// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
// Author : Ahmet Yusuf Birinci

//             ***Thanks to Davis King and all DLIB contributors***
/*

    This example program shows how to find rear end of a airplane in an image and
    estimate their pose.  The pose takes the form of 5 landmarks.  These are
    points on the control surfaces.
    

    This example is essentially just a version of the Deep Learning Vehicle Detection example 
    modified using face_landmark_detection_ex.cpp to be able to use OpenCV's VideoCapture object with CNN
    to read from a camera instead of files. 

    Also, since this is a CNN, you really should use a GPU to get the
    best execution speed.  For instance, when run on a NVIDIA 1080ti, this detector
    runs at 98fps when run on the provided test image.  That's more than an order
    of magnitude faster than when run on the CPU. I trained model with 1050ti mobile version with 150 labeld image 
    and reduced the settings to train it in 10 hours. 
    So train it with high spec gpu that you can find to better result.

    Users who are just learning about dlib's deep learning API should read
    the dnn_introduction_ex.cpp and dnn_introduction2_ex.cpp examples to learn
    how the API works.  For an introduction to the object detection method you
    should read dnn_mmod_ex.cpp.

    You can also see some videos of this vehicle detector running on YouTube:
        https://www.youtube.com/watch?v=4B3bzmxMAZU
        https://www.youtube.com/watch?v=bP2SUo5vSlc
*/

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/image_processing.h>

#include <dlib/dir_nav.h>
#include "webcam.h"

using namespace dlib;
using namespace std;

template <long num_filters, typename SUBNET> using con5d = con<num_filters, 5, 5, 2, 2, SUBNET>;
template <long num_filters, typename SUBNET> using con5 = con<num_filters, 5, 5, 1, 1, SUBNET>;
template <typename SUBNET> using downsampler = relu<affine<con5d<32, relu<affine<con5d<32, relu<affine<con5d<16, SUBNET>>>>>>>>>;
template <typename SUBNET> using rcon5 = relu<affine<con5<55, SUBNET>>>;
using net_type = loss_mmod<con<1, 9, 9, 1, 1, rcon5<rcon5<rcon5<downsampler<input_rgb_image_pyramid<pyramid_down<6>>>>>>>>;

int main()
{
    try
    {
        net_type net;
        shape_predictor sp;

        cv::VideoCapture cap(); // 0 for webcam. "Wherewer:/your/video/file/.mp4" for video
        if (!cap.isOpened())
        {
            cerr << "Unable to connect to camera" << endl;
            return 1;
        }

        image_window win; // win form for visualization

        int a = 0;

        // Load trained model and shape prediction models.
		// if you trained both in one dat file (see Deep Learning Vehicle Detection Trainer example) then;
		// deserialize("your .dat file") >> net >> sp;

        deserialize("deneme.dat") >> net;
        deserialize("sp.dat") >> sp;
        correlation_tracker tracker; // Define correlation tracker


        // Grab and process frames until the main window is closed by the user.
        while(!win.is_closed())
        {
            // Grab a frame
            cv::Mat temp;
            if (!cap.read(temp))
            {
                break;
            }
            // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
            // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
            // long as temp is valid.  Also don't do anything to temp that would cause it
            // to reallocate the memory which stores the image as that will make cimg
            // contain dangling pointers.  This basically means you shouldn't modify temp
            // while using cimg.
			
            win.clear_overlay(); // clear overlay. I put this here bcause we are in loop
            rectangle recta((temp.cols / 4), (temp.rows / 10),(temp.cols*3/4), (temp.rows * 9/10) ); 
			// this makes a shooting square in win. %25 from sides and %10 from up and down.
            win.add_overlay(image_window::overlay_rect(recta, dlib::rgb_pixel(255, 0, 0), "Shooting zone"));
 
            matrix<rgb_pixel> dlibFrame;
            dlib::assign_image(dlibFrame, dlib::cv_image<bgr_pixel>(temp));
            /* to pass this image to dlib functions we have to convert that image to something that dlib can deal and
			   process. (assign_image)This global function copies one image into another and performs any necessary color space 
               conversions to make it work right */
			win.set_image(dlibFrame);

            for (auto&& d : net(dlibFrame))
            {
                a++;
				cout << "For_ici" << endl;
                // We use a shape_predictor to refine the exact shape and location of the detection
                // plane.  This shape_predictor is trained to simply output the 5control surfece points of
                // the plane. (Car example)So all we do is make a rectangle that tightly contains those 4 points
                // and that rectangle is our refined detection position.
                auto fd = sp(dlibFrame, d);
                rectangle rect;
                

                for (unsigned long j = 0; j < fd.num_parts(); ++j){
                    rect += fd.part(j);
                    
                }
                if (a == 1) {
                    tracker.start_track(dlibFrame, rect);
                    cout << "a 1 " << endl;

                }

               
                tracker.update(dlibFrame);
                win.add_overlay(tracker.get_position(), rgb_pixel(0, 255, 0));
                
                
                win.add_overlay(image_window::overlay_rect(rect, dlib::rgb_pixel(255, 0, 0),"Plane"));

                continue;
            }
            a = 0;
        }
    }
    catch(serialization_error& e)
    {
        cout << "You need dlib's default face landmarking model file to run this example." << endl;
        cout << "You can get it from the following URL: " << endl;
        cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
        cout << endl << e.what() << endl;
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }
}


