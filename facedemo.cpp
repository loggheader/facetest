#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <unistd.h>
using namespace std;
using namespace cv;
using namespace cv::face;


/******************************* some defines ************************************/
#define SIZE_ROW 200
#define SIZE_COL 200

/***************************** actual code ***********************************/

void help(void)
{
	printf("Usage:\n"
		   "./facedemo [image to identify] [csv file to load] [alogrithm to use \"eigen\" or \"fisher\" or \"lbph\"]\n"
		);
	exit(0);
}

void resize_img(Mat &inp, Mat &outp, int row, int col)
{
	int flag;
	if(inp.rows > row || inp.cols > col) flag = INTER_AREA;
	else flag = INTER_CUBIC;
	cv::resize(inp,outp,Size(row,col),0,0,flag);
}

void read_from_csv_file(const char *name, vector<Mat> &img, vector<int> &labels)
{
	int count = 0;
	FILE *fp = fopen(name,"r"); if(fp == NULL) { printf("no such csv file\n"); exit(0);}
	char input[4096]; memset(input,0,sizeof(input));
	while(!feof(fp)){
		fgets(input,4000,fp);
		char * semicolumn = strchr(input,';');
		if(semicolumn == NULL) {
			//printf("error in csv format in line %d (zero indexed)\n",count);
			break;
		}
		*semicolumn = '\0'; semicolumn++;
		if(access(input,F_OK)){
			printf("Error in line %d\n",count);
			printf("No such file :\n%s\n",input);
			break;
		}
		int id; sscanf(semicolumn,"%d",&id);
		Mat help=imread(string(input),CV_LOAD_IMAGE_GRAYSCALE);
		resize_img(help,help,SIZE_ROW,SIZE_COL);
		img.push_back(help);
		labels.push_back(id);
		count++;
	}
	fclose(fp);
}

#include <ctime>
#include <iostream>
int main(int argc, char **argv)
{
	clock_t time1= clock();
	if(argc != 4) help();
	vector<Mat> images;
	vector<int> labels;
	read_from_csv_file(argv[2],images,labels);
	char * alg = argv[3];
	Ptr<cv::face::FaceRecognizer> model;
	if(strcmp(alg,"lbph") == 0) model = LBPHFaceRecognizer::create();
	else if (!strcmp(alg,"eigen")) model = EigenFaceRecognizer::create();
	else if(! strcmp(alg,"fisher")) model = FisherFaceRecognizer::create();
	else help();
	model->train(images,labels);
	//printf("done training\n");

	Mat sample = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

	resize_img(sample,sample,SIZE_ROW,SIZE_COL);
	clock_t time2= clock();
	int prediction = model->predict(sample);
	clock_t time3=clock();
	printf("prediction %d\n",prediction);
	cout<< ((double )(time2-time1))/ CLOCKS_PER_SEC<<endl;
	cout<< ((double )(time3-time2))/ CLOCKS_PER_SEC<<endl;
	cout<< ((double )(time3-time1))/ CLOCKS_PER_SEC<<endl;
	model->save("model.xml");
}



































