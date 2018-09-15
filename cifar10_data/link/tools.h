#pragma once

//��opencv�йص�һЩʵ�ú�������
#include <windows.h>
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

extern int g_biBitCount;

void hwnd2mat(cv::Mat& dst, HWND hwnd);		//��GetDIBitsȡ��ͼ�����ݡ��������ڣ�win7�¿�����Ч��ʱ�����赲��Ҳ�ܽ�ȡ
void hwnd5mat(cv::Mat& dst, HWND hwnd);		//��GetBitmapBitsȡ��ͼ������

//���º�����link�����õ�
double match(cv::Mat image, cv::Mat templ, cv::Point &matchLoc, int method);
cv::Mat mergeRows(cv::Mat A, cv::Mat B);
cv::Mat mergeCols(cv::Mat A, cv::Mat B);

//ϵͳtools(ȫ�ֺ���)
void StrToClip(char* pstr); //����FEN����������
void ClipToStr(char* pstr); //�Ӽ����忽����pstr
void start_bh(string fen, bool turn=true);		//�ҵ����Ӵ��ڲ�ģ���½���ճ�����棬��ʼ����(turn==trueʱ)
void deledge(cv::Mat& src, float scale);//����͸��ͨ����ͼƬ�뾶r����͸����

int hist();
int hist1();
int hist_hsv();
double hist_comp(Mat srcImage_base, Mat srcImage_test1);

void load_images( const String & dirname, vector< Mat > & img_lst, bool showImages = false );

int dnn();
bool  MultiChannelBlending();
bool  ROI_LinearBlending();

int png();
int copyPNGtoMat(cv::Mat &dst, cv::Mat &scr, double scale);
int test_add_alpha();

int checkboard();
void checkdxdy(void);