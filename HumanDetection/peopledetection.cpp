#include <iostream>
#include <opencv2/opencv.hpp>
#include <ctime>
#include "config.h"

using namespace std;
using namespace cv;

Config conf;

double getTime(clock_t start, clock_t end) {
	return double(end - start) / CLOCKS_PER_SEC;
}

//createsamples -vec samples.vec -w 30 -h 73
int main(int argc, const char * argv[]) {
	VideoCapture cap;
	//cap.open("C:\\Users\\XuanDuc\\Desktop\\VIDEO0042.mp4");
	cap.open(conf.getVideo());	
	cout << conf.getVideo() << endl;
	cout << cap.get(CV_CAP_PROP_FPS) << endl;
	cap.set(CV_CAP_PROP_FRAME_WIDTH , conf.getWidth());
	cap.set(CV_CAP_PROP_FRAME_HEIGHT , conf.getHeight());
	if (!cap.isOpened())
		return -1;

	Mat img, preImg;
	Detector* detector = conf.getDetector();
	Tracker* tracker = conf.getTracker();

	namedWindow("video capture", CV_WINDOW_AUTOSIZE);	
	vector<Rect> found_filtered;
	for(int step = 0; true; step++) {
		clock_t start = clock();
		bool ok = cap.read(img);
		if (!ok)
			break;
	
		resize(img, img, Size(conf.getWidth(), conf.getHeight()), 0, 0, INTER_CUBIC);
		cout << img.cols << " " << img.rows << endl;
		if (!img.data)
			continue;

		if (step%conf.getStep() == 0)
			found_filtered = detector->detect(img);
		else
			found_filtered = tracker->detect(preImg, img, found_filtered);
		
		
		for (size_t i = 0; i < found_filtered.size(); i++) {			
			Rect r = found_filtered[i];
			cout << r.tl() << " " << r.br() << endl;
			r.x += cvRound(r.width * 0.1);
			r.width = cvRound(r.width * 0.8);
			r.y += cvRound(r.height * 0.06);
			r.height = cvRound(r.height * 0.9);
			rectangle(img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);
		}
		//resize(img, img, Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT)), 0, 0, INTER_CUBIC);
		imshow("video capture", img);
		clock_t end = clock();
		cout << getTime(start, end) << endl;
		if (waitKey(20) >= 0)
			break;

		preImg = img;		
	}
	delete detector;
	return 0;
}