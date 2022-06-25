#ifndef HGL_QT5_MAIN_INCLUDE
#define HGL_QT5_MAIN_INCLUDE

#include<hgl/platform/QT5Application.h>
#include<hgl/platform/ConsoleSystemInitInfo.h>

#define HGL_QT_MAIN(sii_name,app_name,arg_name) extern "C" int QT5AppMain(hgl::ConsoleSystemInitInfo &sii_name,hgl::QT5GuiApplication &app_name,const hgl::StringList<hgl::OSString> &arg_name)

#define QTConnect(obj,event,class_pointer,slot_func)    connect(obj,SIGNAL(event()),class_pointer,SLOT(slot_func()))

#define HGL_QT_MAIN_FUNC()                          HGL_QT_MAIN(sii,app,args)

#define HGL_QT_APPLICATION(name,code,start) using namespace hgl;    \
                                                    \
                                                    HGL_QT_MAIN_FUNC()\
                                                    {   \
                                                        sii.info.ProjectName=name;  \
                                                        sii.info.ProjectCode=code;  \
                                                        \
                                                        if(!app.Init(&sii)) \
                                                            return(-1); \
                                                        \
                                                        app.SetStart(start);    \
                                                        \
                                                        return app.Run();   \
                                                    }

#endif//HGL_QT5_MAIN_INCLUDE
