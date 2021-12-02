#include <opencv2\opencv.hpp>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

	CascadeClassifier faceCascade;
	CascadeClassifier eyesCascade;
	faceCascade.load("C:\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");
	eyesCascade.load("C:\\opencv\\build\\etc\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml");

	VideoCapture cap(0);

	if (!cap.isOpened())   {

		cout << "Failed to open Camera. " << "\n";
		return - 1; 

	}
	for (;;)  {

		Mat frame, gray;
		cap >> frame;

		cvtColor(frame, gray, COLOR_BGR2GRAY);
		//imshow("Frame", frame);

		vector<Rect> dect;
		faceCascade.detectMultiScale(gray, dect);
		for (size_t i = 0; i < dect.size(); i++)   {

			Point faceCenter	{
				dect[i].x + dect[i].width / 2, dect[i].y + dect[i].height / 2
			};
			Size halfFace	{

				dect[i].width / 2, dect[i].height / 2

			};

				ellipse(frame, faceCenter, halfFace, 0, 0, 360, Scalar(255, 0, 0), 3);
			
				Mat ROI	  {

					gray(dect[i])

				};

			vector<Rect> ey;
				eyesCascade.detectMultiScale(ROI, ey);

			for (size_t j = 0; j < ey.size(); ++j)	 {

				Point eyeCenter{

					dect[i].x + ey[j].x + ey[j].width / 2, dect[i].y + ey[j].y + ey[j].height / 2

				};

				int r{

					cvRound((ey[j].width + ey[j].height) * 0.25)

				};

				circle(frame, eyeCenter, r, Scalar(255, 0, 0), 3);

			}

		}

		imshow("Face detection. ", frame);

		
		if (waitKey(30) == 27 || waitKey(30) == 'q')   {

			break;

		}

	}

	return 0;
}