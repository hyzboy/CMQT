#pragma once

#include<QPixmap>
#include<QString>
#include<QSvgRenderer>

namespace hgl
{
    namespace qt
    {
        class SVGPixmap
        {
            QSvgRenderer *svg;

        public:

            const QSize size()const
            {
                return svg?svg->defaultSize():QSize(0,0);
            }

        public:

            SVGPixmap(){svg=nullptr;}
            ~SVGPixmap(){if(svg)delete svg;}

            bool Load(const QString &);

            QPixmap bitmap(const uint size);
        };//class SVGPixmap

        QPixmap LoadSVG(const QString &filename,const uint size);
    }//namespace qt
}//namespace hgl