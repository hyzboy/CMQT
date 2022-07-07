#include<hgl/qt/SVGPixmap.h>
#include<QFile>
#include<QtXml/QDomDocument>
#include<QPainter>

namespace hgl
{
    namespace qt
    {
        bool SVGPixmap::Load(const QString &filename)
        {
            QFile file(filename);

            if(!file.open(QIODevice::ReadOnly))
                return(false);

            QByteArray baData = file.readAll();

            QDomDocument doc;
            doc.setContent(baData);

            if(svg)delete svg;

            svg=new QSvgRenderer(doc.toByteArray());

            return(true);
        }

        QPixmap SVGPixmap::bitmap(const uint size)
        {
            if(!svg||size==0)
                return QPixmap(0,0);

            QPixmap pix(size,size);

            pix.fill(Qt::transparent);

            QPainter pixPainter(&pix);

            svg->render(&pixPainter);

            return pix;
        }        

        QPixmap LoadSVG(const QString &filename,const uint size)
        {
            QFile file(filename);

            if(!file.open(QIODevice::ReadOnly))
                return(QPixmap(size,size));

            QByteArray baData = file.readAll();

            QDomDocument doc;
            doc.setContent(baData);

            QSvgRenderer svg(doc.toByteArray());
            QPixmap pix(size,size);

            pix.fill(Qt::transparent);

            QPainter pixPainter(&pix);

            svg.render(&pixPainter);

            return pix;
        }
    }//namespace qt
}//namespace hgl