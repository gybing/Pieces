//���Լ���ͼƬ�ļ�������cifar10���ݼ���ʵ�ַ������£�
//1���ɼ�����ͼ�񣬰Ѳ�ͬ����ͼ���ļ��ֱ���ڹ���Ŀ¼ _strWorkingFolder �²�ͬ�����ļ����У����ļ�����������Ϊ���������cat��dog֮�ࣩ��ͼ���ļ��������⡣
//2����renBatchImag�����������ա������_˳���.jpg������ʽ������������������ļ���������ͼ���ļ����磺"cat_1.jpg"��"cat_2.jpg"��"dog_1.jpg"��"dog_2.jpg"��
//3����img2bin()������ȫ��׼���õ�����ͼ��������Ҫ�Ķ��������ݼ�(��data_batch_1.bin��makeBatchesMeta.txt�ļ�)��
//	 CCifar10 binData;	binData.img2bin( "f:\\dl\\images");
//4���� tensorflow/models/image/cifar10 ģ���л�ȡ���ݵĲ��ֲ����޸ĳ�Ϊ�ʺ��Լ����ݼ���
//5��������Զ������ݼ����� tensorflow/models/image/cifar10 ģ���Դ��ѵ������

#pragma once
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

class CCifar10
{
public:
	CCifar10()
	{
		_strWorkingFolder = ".";						//��ǰĿ¼
		_strDataBatchBin = "data_batch_1.bin"; 
		_strBatchesMeta =  "batches.meta.txt";
		_iHeight = 32;	_iWidth  = 32; 
	}

	~CCifar10(){}
	
	//��_strWorkingFolderĿ¼��������Ŀ¼����Ŀ¼Ϊ���������е�ͼ���ļ�������cifar10���ݼ������ݼ�����ļ������Ŀ¼ _strWorkingFolder ��
	bool img2bin(void)const;	
	
	//��ȡ_strWorkingFolderĿ¼�����ݼ��ļ���_strDataBatchBin����i_th��ͼƬ���Ŵ�scale������ʾ3�Ų�ȫ�������ڲ�ͬ����Ŀ¼��(�������ֱ���)
	bool bin2img(const int i_th, const float scale = 1, const int method=0)const;	

	std::string	_strWorkingFolder;
	std::string	_strDataBatchBin;
	std::string	_strBatchesMeta;

private:
	bool mat2bin( FILE*& fp, std::string& image_file,unsigned char  label)const;//д�뵥��ͼ���ļ�
	const std::vector<std::string> getBatchesMeta(void)const;					//��_strWorkingFolderĿ¼��_strBatchesMeta�ļ���ȡ�÷������б�
	const std::vector<std::string> listFolders( void)const;						//��ù���Ŀ¼_strWorkingFolder�µ�������Ŀ¼��
	const std::vector<std::string> listImgFiles( std::string Folder)const;		//���Ŀ¼folder�µ�����ͼ���ļ���
	static const std::string getFileName( std::string & filename );				//�Ӵ�·�����ļ����зֽ���������ļ���

	int			_iHeight;
	int			_iWidth;
};