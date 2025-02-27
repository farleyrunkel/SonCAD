// Copyright [2024] SunCAD

#ifndef COMM_PIXMAPHELPER_H_
#define COMM_PIXMAPHELPER_H_

#include <QImage>
#include <Image_PixMap.hxx>



class PixMapHelper {

public: 
	static Handle(Image_PixMap) ConvertFromBitmap(const QImage& bitmap);
};

#endif  // COMM_PIXMAPHELPER_H_
