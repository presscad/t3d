 
 
 
 
 
 
 

#if !defined(AFX_3DSMODEL_H__98FC8CCA_A44F_4C45_9C99_CAC11614A519__INCLUDED_)
#define AFX_3DSMODEL_H__98FC8CCA_A44F_4C45_9C99_CAC11614A519__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "load3ds.h"

 
class C3DSModel
{
public:
	
	char m_sFileName[100];
	
	BOOL m_bModelOK;

	C3DSModel(void);
	virtual ~C3DSModel(void);
	
	BOOL LoadModelFromFile(char* sfilename);	
	
	BOOL Draw(int m_drawStyle,double *minx,double *maxx,double *miny,double *maxy,double *minz,double *maxz);

public:
	void AlignBottom();
	
	CLoad3DS::t3DModel m_3DModel;		
private:
	float m_Color_R,m_Color_G,m_Color_B;
	
	void GetColorRGB(double minY, double maxY, double y);
};

#endif // !defined(AFX_3DSMODEL_H__98FC8CCA_A44F_4C45_9C99_CAC11614A519__INCLUDED_)
