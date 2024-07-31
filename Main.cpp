#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include <string>
#include<vector>


using namespace std;
using namespace cv;


Mat img, adjustedImage, savedimg;
int alphaSlider = 100; 
int betaSlider = 100;  
const int alphaMax = 200;
const int betaMax = 200;

void on_trackbar(int, void*) {
	double alpha = alphaSlider / 100.0; 
	int beta = betaSlider - 100;        

	img.convertTo(adjustedImage, -1, alpha, beta);
	imshow("Color Adjustment", adjustedImage);
}

void adjustColorWithTrackbars() {
	namedWindow("Color Adjustment", WINDOW_AUTOSIZE);
	
	createTrackbar("Contrast", "Color Adjustment", &alphaSlider, alphaMax, on_trackbar);
	createTrackbar("Brightness", "Color Adjustment", &betaSlider, betaMax, on_trackbar);

	on_trackbar(0, 0);
	waitKey(0);
	
	adjustedImage.copyTo(savedimg);
}

void resizeImage(Mat& img) {
	Mat imgresized;
	int width, height;
	cout << "Enter new width and height: ";
	cin >> width >> height;
	resize(img, imgresized, Size(width, height));
	imshow("resized image", imgresized);
	waitKey(0);
	imgresized.copyTo(savedimg);
}

void cropImage(Mat& img) {
	Mat imgcrop;
	int x, y, width, height;
	cout << "Enter x, y, width, height for cropping: ";
	cin >> x >> y >> width >> height;

	if (x >= 0 && y >= 0 && x + width <= img.cols && y + height <= img.rows) 
	{
		imgcrop = img(Rect(x, y, width, height));
		imshow("image croped", imgcrop);
		waitKey(0);
		imgcrop.copyTo(savedimg);
	}
	else {
		cout << "Invalid cropping dimensions!\n";
	}
}




Mat imggray, imgblur;
Mat sharpened;
Mat kernel;
int op, ip;


void main()
{
	
	String path;
	int ikey = waitKey(1);
	Mat img_temp;
	bool exit = false;
	String savePath;
	
	cout << "Please enter the path to the image file: ";
	getline(cin, path);
	img = imread(path);
	
	
	
	while (exit == false)
	{
		system("cls");
	cout << "-----------Imageprocessing-----------" << endl;
	cout << "choose a operation to be performed" << endl;
	cout << "1-Display image" << endl;
	cout << "2-Convert to gray image" << endl;
	cout << "3-convert to blur image" << endl;
	cout << "4 - to sharpen image" << endl;
	cout << "5-Adjut brightness and contrast" << endl;
	cout << "6-resize image" << endl;
	cout << "7-crop image" << endl;
	cout << "8-save image" << endl;
	cout << "0-Exit" << endl;
	cout << "Enter operation- ";
	cin >> op;
	
	
	
		switch (op)
		{
		case 1:
			imshow("image", img);
			waitKey(0);
			break;
		case 2:
			cvtColor(img, imggray, COLOR_BGR2GRAY);
			imshow("image gray", imggray);
			waitKey(0);
			imggray.copyTo(savedimg);
			break;
		case 3:
			GaussianBlur(img, imgblur, Size(5, 5), 3, 0);
			imshow("image blur", imgblur);
			waitKey(0);
			imgblur.copyTo(savedimg);
			break;
		case 4:
			kernel = (Mat_<float>(3, 3) <<
				0, -1, 0,
				-1, 5, -1,
				0, -1, 0);

			filter2D(img, sharpened, -1, kernel);
			imshow("image sharpen", sharpened);
			waitKey(0);
			sharpened.copyTo(savedimg);
			break;
			
		case 5:
			adjustColorWithTrackbars();
			break;
		
		case 6:
			resizeImage(img);
			break;
		case 7:
			cropImage(img);
			break;
		case 8:
			
			cout << "Enter the path to save the image: ";
			
			imwrite("image.jpg", savedimg);
			cout << "Image saved successfully!\n";
			break;

		case 0:
			exit = true;
			break;

		default:
			cout << "Invalid choice!" << endl;
			break;
		}
	}
}







	