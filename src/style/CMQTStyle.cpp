#include<QStringList>
#include<QStyle>
#include<QStyleFactory>
#include<QApplication>

#ifdef USE_EXTRA_QT_STYLE

QT_BEGIN_NAMESPACE
QStyle *CreateBB10BrightStyle();
QStyle *CreateBB10DarkStyle();
QStyle *CreateCleanlooksStyle();
QStyle *CreateCDEStyle();
QStyle *CreateMotifStyle();
QStyle *CreatePlastiqueStyle();
QT_END_NAMESPACE

#endif//USE_EXTRA_QT_STYLE

namespace hgl
{
    namespace qt
    {
        QT_USE_NAMESPACE
            
#ifdef USE_EXTRA_QT_STYLE
        struct CreateQTExtraStyleConfig
        {
            QString name;
            QStyle *(*create)();
        };

        const CreateQTExtraStyleConfig qt_extra_styles[]=
        {
        #define DEF_QT_EXTRA_STYLE(name)    {#name,Create##name##Style},

            //DEF_QT_EXTRA_STYLE(BB10Bright)
            //DEF_QT_EXTRA_STYLE(BB10Dark)
            DEF_QT_EXTRA_STYLE(Cleanlooks)
            DEF_QT_EXTRA_STYLE(CDE)
            DEF_QT_EXTRA_STYLE(Motif)
            DEF_QT_EXTRA_STYLE(Plastique)

        #undef DEF_QT_EXTRA_STYLE
        };
#endif//USE_EXTRA_QT_STYLE

        const QString GetApplicationStyle()
        {
            return QApplication::style()->objectName();
        }

        const QStringList GetStyleList()
        {
            QStringList list=QStyleFactory::keys();
            
#ifdef USE_EXTRA_QT_STYLE
            for(int i = 0;i < sizeof(qt_extra_styles) / sizeof(CreateQTExtraStyleConfig);i++)
                list << qt_extra_styles[i].name;
#endif//USE_EXTRA_QT_STYLE

            return list;
        }

        bool SetApplicationStyle(const QString &style_name)
        {
            QStyle *s=nullptr;
            
#ifdef USE_EXTRA_QT_STYLE
            for(int i = 0;i < sizeof(qt_extra_styles) / sizeof(CreateQTExtraStyleConfig);i++)
            {
                if(style_name.compare(qt_extra_styles[i].name, Qt::CaseInsensitive) == 0)
                {
                    s=qt_extra_styles[i].create();
                    break;
                }
            }

            if(!s)
#endif//USE_EXTRA_QT_STYLE
                s=QStyleFactory::create(style_name);

            if(s)
            {
                QApplication::setStyle(s);
                return(true);
            }

            return(false);
        }
    }//namespace qt
}//namespace hgl
