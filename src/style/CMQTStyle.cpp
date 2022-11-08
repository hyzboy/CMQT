#include<QStringList>
#include<QStyle>

QT_BEGIN_NAMESPACE
QStyle *CreateBB10BrightStyle();
QStyle *CreateBB10DarkStyle();
QStyle *CreateCleanlooksStyle();
QStyle *CreateCDEStyle();
QStyle *CreateMotifStyle();
QStyle *CreatePlastiqueStyle();
QT_END_NAMESPACE

namespace hgl
{
    namespace qt
    {
        QT_USE_NAMESPACE
            
        struct CreateQTExtraStyleConfig
        {
            QString name;
            QStyle *(*create)();
        };

        const CreateQTExtraStyleConfig qt_extra_styles[]=
        {
        #define DEF_QT_EXTRA_STYLE(name)    {#name,Create##name##Style},

            DEF_QT_EXTRA_STYLE(BB10Bright)
            DEF_QT_EXTRA_STYLE(BB10Dark)
            DEF_QT_EXTRA_STYLE(Cleanlooks)
            DEF_QT_EXTRA_STYLE(CDE)
            DEF_QT_EXTRA_STYLE(Motif)
            DEF_QT_EXTRA_STYLE(Plastique)

        #undef DEF_QT_EXTRA_STYLE
        };

        const QStringList GetExtraGUIStyleList()
        {
            QStringList list;

            for(int i = 0;i < sizeof(qt_extra_styles) / sizeof(CreateQTExtraStyleConfig);i++)
                list << qt_extra_styles[i].name;

            return list;
        }

        QStyle *CreateQTExtraStyle(const QString &style_name)
        {
            for(int i = 0;i < sizeof(qt_extra_styles) / sizeof(CreateQTExtraStyleConfig);i++)
            {
                if(style_name.compare(qt_extra_styles[i].name, Qt::CaseInsensitive) == 0)
                    return qt_extra_styles[i].create();
            }

            return(nullptr);
        }
    }//namespace qt
}//namespace hgl
