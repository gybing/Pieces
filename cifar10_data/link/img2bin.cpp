#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "opencv2/legacy/legacy.hpp"
#include "img2bin.h"

#pragma warning(disable: 4996)		// Function _ftime() may be unsafe

//���Լ���ͼƬ�ļ�������cifar10���ݼ���ʵ�ַ������£�
//1���ɼ�����ͼ�񣬰Ѳ�ͬ����ͼ���ļ��ֱ���ڲ�ͬ���ļ����£��ļ�����������Ϊ��������ļ������⡣
//2����renBatchImag��������������������������ļ���������ͼ���ļ����ļ������磺"cat_1.jpg"��"cat_1.jpg"�ȡ�
//3�������ȫ��׼���õ�����ͼ��������Ҫ�Ķ��������ݼ���
//4���� tensorflow/models/image/cifar10 ģ���л�ȡ���ݵĲ��ֲ����޸ĳ�Ϊ�ʺ��Լ����ݼ���
//5��������Զ������ݼ����� tensorflow/models/image/cifar10 ģ���Դ��ѵ������
//CCifar10 binData;	binData.img2bin( "f:/dl/images");
bool CCifar10::img2bin(void)const
{
	std::vector<std::string> class_name_list = listFolders();
	const int size_list = class_name_list.size();
	if(size_list==0)return false;

	//����_strWorkingFolderĿ¼����Ŀ¼��������ͬ������ͼ���ļ�������_strBatchesMeta�ļ�
	//build batches_meta.txt
	std::string fnmeta= _strWorkingFolder + "/" + _strBatchesMeta;
	std::ofstream oFile(fnmeta);
	if (!oFile.is_open())
	{
		std::cout<<"open file error!  "<< fnmeta <<std::endl;
		return false;
	}
	for(vector<std::string>::iterator iter = class_name_list.begin(); iter != class_name_list.end(); ++iter)
	{
		if(*iter!= _strBatchesMeta && *iter!=_strDataBatchBin)	
		{	
			oFile << *iter << std::endl;
		}
	}
	oFile.close();

	//build data_batch_1.bin
	FILE *fp;
	fopen_s(&fp, (_strWorkingFolder+"/"+_strDataBatchBin).c_str(), "wb" );
	if ( fp == NULL )
	{
		std::cout << "Open error! file: " <<  (_strWorkingFolder+_strDataBatchBin) << std::endl;
		fclose(fp);
		return false;
	}

	int index=0;
	int totals=0;
	for(vector<std::string>::iterator iter_typename = class_name_list.begin(); iter_typename != class_name_list.end(); ++iter_typename)
	{
		std::string imgFolder = _strWorkingFolder + "/" + *iter_typename ;
		std::vector<std::string> img_list = listImgFiles(imgFolder);
		long size_img_list = img_list.size();
		totals += size_img_list;
		for ( long idx = 0; idx <size_img_list; ++idx )
		{
			if(mat2bin(fp, img_list[idx], index))
			{
				std::cout << idx+1<< "/" << size_img_list<<"/"<< totals <<"��image " << img_list[idx] << " saved. " << *iter_typename <<" = "<< index << std::endl;
			}
		}
		index++;
	}

	fclose(fp);
	return true;
}

//д�뵥��ͼ���ļ�
bool CCifar10::mat2bin( FILE*& fp, std::string& image_file, unsigned char label)const
{
	cv::Mat image = cv::imread( image_file, IMREAD_UNCHANGED );
	if ( !image.data )
	{
		return false;
	}

	cv::cvtColor(image, image, image.channels() == 1? CV_GRAY2RGB : CV_BGR2RGB);
	cv::resize( image, image, cv::Size(_iWidth, _iHeight), CV_INTER_LINEAR );

	fwrite(&label, sizeof(char), 1, fp);
	for ( int i=0; i<image.rows * image.cols; i++ )
	{
		fwrite( (char*)&image.data[i*3],	sizeof(char), 1, fp );		// R
	}
	for ( int i=0; i<image.rows * image.cols; i++ )
	{
		fwrite( (char*)&image.data[i*3+1],	sizeof(char), 1, fp );		// G
	}
	for ( int i=0; i<image.rows * image.cols; i++ )
	{
		fwrite( (char*)&image.data[i*3+2],	sizeof(char), 1, fp );		// B
	}

	return true;
}

//��ȡ��ǰĿ¼�����ݼ��ļ���_strDataBatchBin����i_th��ͼƬ���Ŵ�scale������ʾ3�Ų�ȫ�������ڲ�ͬ����Ŀ¼��(�������ֱ���)
bool CCifar10::bin2img(const int i_th, const float scale, const int method)const
{
	int index = 10;
	string classname[10];								//����
	int numofclass[10]={0,0,0,0,0,0,0,0,0,0};			//ÿһ�����
	string strtemp;

	string fnmeta= _strWorkingFolder+"/"+_strBatchesMeta;
	string fndata= _strWorkingFolder+"/"+_strDataBatchBin;;

	std::ifstream infile(fnmeta,ios::in);
	if (!infile.is_open())	
	{
		cout<< "error open file:" << fnmeta <<endl;
		return false;
	}
	while(index--)
	{
		getline(infile, classname[9-index]);
		cout <<  10-index << "  " << classname[9-index] << endl;
	}
	infile.close();


	std::ifstream iFile(fndata, ios::in|ios::binary|ios::ate);
	if (!iFile.is_open())	
	{
		cout<< "error open file:" << fndata <<endl;
		return false;
	}
	long size = (long) iFile.tellg();  
	iFile.seekg (0, ios::beg);  
	cout<< "�ļ�����: " << size <<endl;
	cout<< "���ݼ�������ͼ������: " << size/3073 <<endl;

	unsigned char label;
	unsigned char rdata[32*32];
	unsigned char gdata[32*32];
	unsigned char bdata[32*32];
	cv::Mat image(32, 32, CV_8UC3);		//����3ͨ��ͼ��

	std::vector<cv::Mat> srcChannels;
	cv::split(image, srcChannels);		//����ͨ��

	int totals=0;
	for(int x=0; x<(size/3073); x++)
	{
		if(++totals>i_th)break;		//����Ԥ����������ֹ

		if(method==0)
		{
			//��һ�ְ취��
			//1���ȶ�ȡһ����¼��label,images)
			iFile.read((char*)&label, 1);				
			iFile.read((char*)srcChannels[2].data, 32*32);				
			iFile.read((char*)srcChannels[1].data, 32*32);				
			iFile.read((char*)srcChannels[0].data, 32*32);				
			cv::merge(srcChannels, image);		//�ϲ�ͨ��
			numofclass[label]++;
		}
		else
		{

			//�ڶ��ְ취
			//�ȶ���������
			iFile.read((char*)&label, 1);				
			iFile.read( (char*)rdata, 32*32 );		//��ɫͨ��
			iFile.read( (char*)gdata, 32*32 );		//��ɫͨ��
			iFile.read( (char*)bdata, 32*32 );		//��ɫͨ��
			numofclass[label]++;

			//��������Mat
			if(method==1)
			{
				//��1�ַ�ʽ
				for(int i=0;i<image.rows;i++)  
				{  
					for(int j=0;j<image.cols;j++)  
					{  
						Vec3b pixel(bdata[i*32+j],gdata[i*32+j],rdata[i*32+j]);
						image.at<Vec3b>(i,j) = pixel; 
					}  
				}  
			}
			else
			{
				//��2�ַ�ʽ
				for(int i=0;i<32*32;i++)
				{
					image.data[i*3+0]= bdata[i];		//��ɫͨ��
					image.data[i*3+1]= gdata[i];		//��ɫͨ��
					image.data[i*3+2]= rdata[i];		//��ɫͨ��
				}
			}
		}

		resize(image, image, Size(int(32*scale), int(32*scale)), (0,0), (0,0), INTER_AREA);

		char buffer[2054];
		sprintf(buffer, "%s/%s_%d.jpg", _strWorkingFolder.c_str(), classname[label].c_str(), numofclass[label]);
		cv::imwrite(buffer, image);
#ifdef _DEBUG
		if(x<3)		//����ʾ3��
		{
			namedWindow(buffer, 0);				//����Ϊ�㣬����������϶�
			cv::imshow(buffer,image);
		}
#endif
	}

#ifdef _DEBUG
	waitKey(3000);
#endif
	iFile.close();
	return true;
}

const std::string CCifar10::getFileName( std::string & filename )
{
	int iBeginIndex = filename.find_last_of("/")+1;
	int iEndIndex   = filename.length();

	return filename.substr( iBeginIndex, iEndIndex - iBeginIndex );
}

const std::vector<std::string> CCifar10::listFolders( void )const
{
	std::vector<std::string> folderlist;
	WIN32_FIND_DATA fileData;

	HANDLE file = FindFirstFile( (_strWorkingFolder +"/*.*").c_str(), &fileData );
	FindNextFile( file, &fileData );
	while(FindNextFile( file, &fileData ))
	{
		if((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			folderlist.push_back(string(fileData.cFileName));
		}
	}

	return folderlist ;  
}

const std::vector<std::string> CCifar10::listImgFiles( std::string imgFolder )const
{
	std::vector<std::string> filelist;
	std::vector<std::string> extName;
	extName.push_back("jpg");
	extName.push_back("JPG");
	extName.push_back("bmp");
	extName.push_back("png");
	extName.push_back("gif");

	HANDLE file;
	WIN32_FIND_DATA fileData;
	file = FindFirstFile( (char*)((imgFolder+"/*.*").c_str()), &fileData );
	FindNextFile( file, &fileData );
	while(FindNextFile( file, &fileData ))
	{
		if(!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			std::string lineStr(fileData.cFileName);
			// only files which are images
			for (int i = 0; i < 4; i ++)
			{
				if(lineStr.find(extName[i]) < 999)
				{
					filelist.push_back(imgFolder+"/"+lineStr);  
					break;
				}
			}
		}
	}

	return filelist ;  
}

const std::vector<std::string> CCifar10::getBatchesMeta(void)const
{
	std::vector<std::string> classlist;
	std::string fnmeta= _strWorkingFolder+"/"+_strBatchesMeta;

	std::ifstream infile(fnmeta,ios::in);
	if (!infile.is_open())	
	{
		std::cout<< "error open file:" << fnmeta << std::endl;
		return classlist;
	}

	int index=0;
	while(!infile.eof())
	{
		string classname;
		getline(infile, classname);
		classlist.push_back(classname);
		index++;
		std::cout <<  index << "  " << classname << std::endl;
	}

	infile.close();

	return classlist;
}
