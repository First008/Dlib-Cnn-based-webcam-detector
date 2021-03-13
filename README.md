# Dlib-Cnn-based-webcam-detector

             ***Thanks to Davis King and all DLIB contributors***


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
