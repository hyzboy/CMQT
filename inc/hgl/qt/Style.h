#pragma once
#include<QStringList>

namespace hgl
{
    namespace qt
    {
        const QString GetApplicationStyle();
        const QStringList GetStyleList();
        bool SetApplicationStyle(const QString &style_name);
    }//namespace qt
}//namespace hgl
