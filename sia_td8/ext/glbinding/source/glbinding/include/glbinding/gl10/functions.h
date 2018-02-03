#pragma once

#include <glbinding/nogl.h>
#include <glbinding/gl/functions.h>


namespace gl10
{


using gl::glAccum;
using gl::glAlphaFunc;
using gl::glBegin;
using gl::glBitmap;
using gl::glBlendFunc;
using gl::glCallList;
using gl::glCallLists;
using gl::glClear;
using gl::glClearAccum;
using gl::glClearColor;
using gl::glClearDepth;
using gl::glClearIndex;
using gl::glClearStencil;
using gl::glClipPlane;
using gl::glColor3b;
using gl::glColor3bv;
using gl::glColor3d;
using gl::glColor3dv;
using gl::glColor3f;
using gl::glColor3fv;
using gl::glColor3i;
using gl::glColor3iv;
using gl::glColor3s;
using gl::glColor3sv;
using gl::glColor3ub;
using gl::glColor3ubv;
using gl::glColor3ui;
using gl::glColor3uiv;
using gl::glColor3us;
using gl::glColor3usv;
using gl::glColor4b;
using gl::glColor4bv;
using gl::glColor4d;
using gl::glColor4dv;
using gl::glColor4f;
using gl::glColor4fv;
using gl::glColor4i;
using gl::glColor4iv;
using gl::glColor4s;
using gl::glColor4sv;
using gl::glColor4ub;
using gl::glColor4ubv;
using gl::glColor4ui;
using gl::glColor4uiv;
using gl::glColor4us;
using gl::glColor4usv;
using gl::glColorMask;
using gl::glColorMaterial;
using gl::glCopyPixels;
using gl::glCullFace;
using gl::glDeleteLists;
using gl::glDepthFunc;
using gl::glDepthMask;
using gl::glDepthRange;
using gl::glDisable;
using gl::glDrawBuffer;
using gl::glDrawPixels;
using gl::glEdgeFlag;
using gl::glEdgeFlagv;
using gl::glEnable;
using gl::glEnd;
using gl::glEndList;
using gl::glEvalCoord1d;
using gl::glEvalCoord1dv;
using gl::glEvalCoord1f;
using gl::glEvalCoord1fv;
using gl::glEvalCoord2d;
using gl::glEvalCoord2dv;
using gl::glEvalCoord2f;
using gl::glEvalCoord2fv;
using gl::glEvalMesh1;
using gl::glEvalMesh2;
using gl::glEvalPoint1;
using gl::glEvalPoint2;
using gl::glFeedbackBuffer;
using gl::glFinish;
using gl::glFlush;
using gl::glFogf;
using gl::glFogfv;
using gl::glFogi;
using gl::glFogiv;
using gl::glFrontFace;
using gl::glFrustum;
using gl::glGenLists;
using gl::glGetBooleanv;
using gl::glGetClipPlane;
using gl::glGetDoublev;
using gl::glGetError;
using gl::glGetFloatv;
using gl::glGetIntegerv;
using gl::glGetLightfv;
using gl::glGetLightiv;
using gl::glGetMapdv;
using gl::glGetMapfv;
using gl::glGetMapiv;
using gl::glGetMaterialfv;
using gl::glGetMaterialiv;
using gl::glGetPixelMapfv;
using gl::glGetPixelMapuiv;
using gl::glGetPixelMapusv;
using gl::glGetPolygonStipple;
using gl::glGetString;
using gl::glGetTexEnvfv;
using gl::glGetTexEnviv;
using gl::glGetTexGendv;
using gl::glGetTexGenfv;
using gl::glGetTexGeniv;
using gl::glGetTexImage;
using gl::glGetTexLevelParameterfv;
using gl::glGetTexLevelParameteriv;
using gl::glGetTexParameterfv;
using gl::glGetTexParameteriv;
using gl::glHint;
using gl::glIndexMask;
using gl::glIndexd;
using gl::glIndexdv;
using gl::glIndexf;
using gl::glIndexfv;
using gl::glIndexi;
using gl::glIndexiv;
using gl::glIndexs;
using gl::glIndexsv;
using gl::glInitNames;
using gl::glIsEnabled;
using gl::glIsList;
using gl::glLightModelf;
using gl::glLightModelfv;
using gl::glLightModeli;
using gl::glLightModeliv;
using gl::glLightf;
using gl::glLightfv;
using gl::glLighti;
using gl::glLightiv;
using gl::glLineStipple;
using gl::glLineWidth;
using gl::glListBase;
using gl::glLoadIdentity;
using gl::glLoadMatrixd;
using gl::glLoadMatrixf;
using gl::glLoadName;
using gl::glLogicOp;
using gl::glMap1d;
using gl::glMap1f;
using gl::glMap2d;
using gl::glMap2f;
using gl::glMapGrid1d;
using gl::glMapGrid1f;
using gl::glMapGrid2d;
using gl::glMapGrid2f;
using gl::glMaterialf;
using gl::glMaterialfv;
using gl::glMateriali;
using gl::glMaterialiv;
using gl::glMatrixMode;
using gl::glMultMatrixd;
using gl::glMultMatrixf;
using gl::glNewList;
using gl::glNormal3b;
using gl::glNormal3bv;
using gl::glNormal3d;
using gl::glNormal3dv;
using gl::glNormal3f;
using gl::glNormal3fv;
using gl::glNormal3i;
using gl::glNormal3iv;
using gl::glNormal3s;
using gl::glNormal3sv;
using gl::glOrtho;
using gl::glPassThrough;
using gl::glPixelMapfv;
using gl::glPixelMapuiv;
using gl::glPixelMapusv;
using gl::glPixelStoref;
using gl::glPixelStorei;
using gl::glPixelTransferf;
using gl::glPixelTransferi;
using gl::glPixelZoom;
using gl::glPointSize;
using gl::glPolygonMode;
using gl::glPolygonStipple;
using gl::glPopAttrib;
using gl::glPopMatrix;
using gl::glPopName;
using gl::glPushAttrib;
using gl::glPushMatrix;
using gl::glPushName;
using gl::glRasterPos2d;
using gl::glRasterPos2dv;
using gl::glRasterPos2f;
using gl::glRasterPos2fv;
using gl::glRasterPos2i;
using gl::glRasterPos2iv;
using gl::glRasterPos2s;
using gl::glRasterPos2sv;
using gl::glRasterPos3d;
using gl::glRasterPos3dv;
using gl::glRasterPos3f;
using gl::glRasterPos3fv;
using gl::glRasterPos3i;
using gl::glRasterPos3iv;
using gl::glRasterPos3s;
using gl::glRasterPos3sv;
using gl::glRasterPos4d;
using gl::glRasterPos4dv;
using gl::glRasterPos4f;
using gl::glRasterPos4fv;
using gl::glRasterPos4i;
using gl::glRasterPos4iv;
using gl::glRasterPos4s;
using gl::glRasterPos4sv;
using gl::glReadBuffer;
using gl::glReadPixels;
using gl::glRectd;
using gl::glRectdv;
using gl::glRectf;
using gl::glRectfv;
using gl::glRecti;
using gl::glRectiv;
using gl::glRects;
using gl::glRectsv;
using gl::glRenderMode;
using gl::glRotated;
using gl::glRotatef;
using gl::glScaled;
using gl::glScalef;
using gl::glScissor;
using gl::glSelectBuffer;
using gl::glShadeModel;
using gl::glStencilFunc;
using gl::glStencilMask;
using gl::glStencilOp;
using gl::glTexCoord1d;
using gl::glTexCoord1dv;
using gl::glTexCoord1f;
using gl::glTexCoord1fv;
using gl::glTexCoord1i;
using gl::glTexCoord1iv;
using gl::glTexCoord1s;
using gl::glTexCoord1sv;
using gl::glTexCoord2d;
using gl::glTexCoord2dv;
using gl::glTexCoord2f;
using gl::glTexCoord2fv;
using gl::glTexCoord2i;
using gl::glTexCoord2iv;
using gl::glTexCoord2s;
using gl::glTexCoord2sv;
using gl::glTexCoord3d;
using gl::glTexCoord3dv;
using gl::glTexCoord3f;
using gl::glTexCoord3fv;
using gl::glTexCoord3i;
using gl::glTexCoord3iv;
using gl::glTexCoord3s;
using gl::glTexCoord3sv;
using gl::glTexCoord4d;
using gl::glTexCoord4dv;
using gl::glTexCoord4f;
using gl::glTexCoord4fv;
using gl::glTexCoord4i;
using gl::glTexCoord4iv;
using gl::glTexCoord4s;
using gl::glTexCoord4sv;
using gl::glTexEnvf;
using gl::glTexEnvfv;
using gl::glTexEnvi;
using gl::glTexEnviv;
using gl::glTexGend;
using gl::glTexGendv;
using gl::glTexGenf;
using gl::glTexGenfv;
using gl::glTexGeni;
using gl::glTexGeniv;
using gl::glTexImage1D;
using gl::glTexImage2D;
using gl::glTexParameterf;
using gl::glTexParameterfv;
using gl::glTexParameteri;
using gl::glTexParameteriv;
using gl::glTranslated;
using gl::glTranslatef;
using gl::glVertex2d;
using gl::glVertex2dv;
using gl::glVertex2f;
using gl::glVertex2fv;
using gl::glVertex2i;
using gl::glVertex2iv;
using gl::glVertex2s;
using gl::glVertex2sv;
using gl::glVertex3d;
using gl::glVertex3dv;
using gl::glVertex3f;
using gl::glVertex3fv;
using gl::glVertex3i;
using gl::glVertex3iv;
using gl::glVertex3s;
using gl::glVertex3sv;
using gl::glVertex4d;
using gl::glVertex4dv;
using gl::glVertex4f;
using gl::glVertex4fv;
using gl::glVertex4i;
using gl::glVertex4iv;
using gl::glVertex4s;
using gl::glVertex4sv;
using gl::glViewport;


} // namespace gl10
