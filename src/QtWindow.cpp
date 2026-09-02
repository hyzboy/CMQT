#include<hgl/qt/QtWindow.h>

#include<QWindow>
#include<QEvent>
#include<QResizeEvent>
#include<QCloseEvent>
#include<QKeyEvent>
#include<QMouseEvent>
#include<QWheelEvent>
#include<QExposeEvent>
#include<QHideEvent>

#include<hgl/io/event/KeyboardEvent.h>
#include<hgl/io/event/MouseEvent.h>
#include<hgl/io/event/WindowEvent.h>

#ifdef _WIN32
#include<Windows.h>
#endif//_WIN32

namespace hgl
{
    using namespace io;

    namespace
    {
        // ── Qt::Key → hgl::KeyboardButton（布局相关键按 US 布局物理键位映射）──
        KeyboardButton ConvertQtKey(int k)
        {
            if(k>=Qt::Key_A&&k<=Qt::Key_Z)          return KeyboardButton(int(KeyboardButton::A)+(k-Qt::Key_A));
            if(k>=Qt::Key_0&&k<=Qt::Key_9)          return KeyboardButton(int(KeyboardButton::_0)+(k-Qt::Key_0));
            if(k>=Qt::Key_F1&&k<=Qt::Key_F12)       return KeyboardButton(int(KeyboardButton::F1)+(k-Qt::Key_F1));

            switch(k)
            {
                case Qt::Key_Escape:        return KeyboardButton::Esc;
                case Qt::Key_Tab:           return KeyboardButton::Tab;
                case Qt::Key_Backspace:     return KeyboardButton::BackSpace;
                case Qt::Key_Return:        return KeyboardButton::Enter;
                case Qt::Key_Space:         return KeyboardButton::Space;

                case Qt::Key_Shift:         return KeyboardButton::LeftShift;
                case Qt::Key_Control:       return KeyboardButton::LeftCtrl;
                case Qt::Key_Alt:           return KeyboardButton::LeftAlt;
                case Qt::Key_Meta:          return KeyboardButton::LeftOS;

                case Qt::Key_CapsLock:      return KeyboardButton::CapsLock;

                // 主键盘区符号（Qt 给 ASCII 字符键位）
                case Qt::Key_QuoteLeft:     return KeyboardButton::Grave;      // `
                case Qt::Key_Minus:         return KeyboardButton::Minus;      // -
                case Qt::Key_Equal:         return KeyboardButton::Equals;     // =
                case Qt::Key_Backslash:     return KeyboardButton::BackSlash;  // \
                case Qt::Key_BracketLeft:   return KeyboardButton::LeftBracket;// [
                case Qt::Key_BracketRight:  return KeyboardButton::RightBracket;// ]
                case Qt::Key_Semicolon:     return KeyboardButton::Semicolon;  // ;
                case Qt::Key_Apostrophe:    return KeyboardButton::Apostrophe; // '
                case Qt::Key_Comma:         return KeyboardButton::Comma;      // ,
                case Qt::Key_Period:        return KeyboardButton::Period;     // .
                case Qt::Key_Slash:         return KeyboardButton::Slash;      // /

                case Qt::Key_Print:         return KeyboardButton::PrintScreen;
                case Qt::Key_ScrollLock:    return KeyboardButton::ScrollLock;
                case Qt::Key_Pause:         return KeyboardButton::Pause;

                case Qt::Key_Insert:        return KeyboardButton::Insert;
                case Qt::Key_Delete:        return KeyboardButton::Delete;
                case Qt::Key_Home:          return KeyboardButton::Home;
                case Qt::Key_End:           return KeyboardButton::End;
                case Qt::Key_PageUp:        return KeyboardButton::PageUp;
                case Qt::Key_PageDown:      return KeyboardButton::PageDown;

                case Qt::Key_Up:            return KeyboardButton::Up;
                case Qt::Key_Down:          return KeyboardButton::Down;
                case Qt::Key_Left:          return KeyboardButton::Left;
                case Qt::Key_Right:         return KeyboardButton::Right;

                default:                    return KeyboardButton::NONE;
            }
        }

        MouseButton ConvertQtButton(Qt::MouseButton b)
        {
            switch(b)
            {
                case Qt::LeftButton:    return MouseButton::Left;
                case Qt::MiddleButton:     return MouseButton::Mid;
                case Qt::RightButton:   return MouseButton::Right;
                case Qt::XButton1:      return MouseButton::X1;
                case Qt::XButton2:      return MouseButton::X2;
                default:                return MouseButton::None;
            }
        }
    }//namespace

    // ────────────────────────────────────────────────────────────
    // 内部 QWindow 子类：Qt 事件 → hgl::io 事件
    // ────────────────────────────────────────────────────────────
    class QtWindowSurface:public QWindow
    {
        QtWindow *qt_window;

    private:

        void SendKeyEvent(KeyboardEventID id,QKeyEvent *e)
        {
            EventHeader header;
            header.type     =InputEventSource::Keyboard;
            header.index    =0;
            header.id       =(uint16)id;

            KeyboardEventData ked;
            ked.data=0;
            ked.key=(uint32)ConvertQtKey(e->key());

            if(ked.key!=(uint32)KeyboardButton::NONE)
                qt_window->SendEvent(header,ked.data);
        }

        void SendMouseEvent(MouseAction action,int x,int y,MouseButton button=MouseButton::None)
        {
            EventHeader header;
            header.type     =InputEventSource::Mouse;
            header.index    =0;
            header.id       =(uint16)action;

            MouseEventData med;
            med.data=0;
            med.x      =int16(x);
            med.y      =int16(y);
            med.button =uint8(button);
            med.action =uint8(action);

            qt_window->SendEvent(header,med.data);
        }

    public:

        QtWindowSurface(QtWindow *w)
            :QWindow(),qt_window(w)
        {
        }

    protected:

        void resizeEvent(QResizeEvent *e) override
        {
            const QSize sz=e->size();

            EventHeader header;
            header.type     =InputEventSource::Window;
            header.index    =0;
            header.id       =(uint16)WindowEventID::Resize;

            WindowEventData wed;
            wed.data=0;
            wed.width =uint16(sz.width());
            wed.height=uint16(sz.height());

            qt_window->SendEvent(header,wed.data);

            QWindow::resizeEvent(e);
        }

        void closeEvent(QCloseEvent *e) override
        {
            EventHeader header;
            header.type     =InputEventSource::Window;
            header.index    =0;
            header.id       =(uint16)WindowEventID::Close;

            WindowEventData wed;
            wed.data=0;

            qt_window->SendEvent(header,wed.data);

            QWindow::closeEvent(e);
        }

        void exposeEvent(QExposeEvent *e) override
        {
            EventHeader header;
            header.type     =InputEventSource::Window;
            header.index    =0;
            header.id       =(uint16)WindowEventID::Active;

            WindowEventData wed;
            wed.data=0;
            wed.active=isExposed();

            qt_window->SendEvent(header,wed.data);

            QWindow::exposeEvent(e);
        }

        void hideEvent(QHideEvent *e) override
        {
            EventHeader header;
            header.type     =InputEventSource::Window;
            header.index    =0;
            header.id       =(uint16)WindowEventID::Active;

            WindowEventData wed;
            wed.data=0;
            wed.active=false;

            qt_window->SendEvent(header,wed.data);

            QWindow::hideEvent(e);
        }

        void keyPressEvent(QKeyEvent *e) override
        {
            SendKeyEvent(KeyboardEventID::Pressed,e);
            QWindow::keyPressEvent(e);
        }

        void keyReleaseEvent(QKeyEvent *e) override
        {
            SendKeyEvent(KeyboardEventID::Released,e);
            QWindow::keyReleaseEvent(e);
        }

        void mousePressEvent(QMouseEvent *e) override
        {
            SendMouseEvent(MouseAction::Pressed,e->position().x(),e->position().y(),ConvertQtButton(e->button()));
            QWindow::mousePressEvent(e);
        }

        void mouseReleaseEvent(QMouseEvent *e) override
        {
            SendMouseEvent(MouseAction::Released,e->position().x(),e->position().y(),ConvertQtButton(e->button()));
            QWindow::mouseReleaseEvent(e);
        }

        void mouseMoveEvent(QMouseEvent *e) override
        {
            SendMouseEvent(MouseAction::Move,e->position().x(),e->position().y());
            QWindow::mouseMoveEvent(e);
        }

        void wheelEvent(QWheelEvent *e) override
        {
            const QPoint delta=e->angleDelta();

            SendMouseEvent(MouseAction::Wheel,0,delta.y()!=0?(delta.y()>0?1:-1):0);
            QWindow::wheelEvent(e);
        }
    };//class QtWindowSurface

    // ────────────────────────────────────────────────────────────
    // QtWindow
    // ────────────────────────────────────────────────────────────

    QtWindow::QtWindow(const OSString &name)
        :Window(name)
    {
        surface=new QtWindowSurface(this);
        owns_surface=true;
    }

    QtWindow::~QtWindow()
    {
        if(owns_surface)
            delete surface;

        surface=nullptr;
    }

    QWindow *QtWindow::GetQWindow()const
    {
        return surface;
    }

    bool QtWindow::Create(uint w,uint h)
    {
        if(!surface)
            return(false);

        // 记录初始尺寸（Qt 布局最终尺寸经 resizeEvent 校正）
        width =surface->width()?surface->width():w;
        height=surface->height()?surface->height():h;

        // 强制创建原生窗口（winId），保证 Vulkan surface 可取得 HWND
        surface->winId();

        is_close=false;
        return(true);
    }

    void QtWindow::Close()
    {
        is_close=true;

        if(surface)
            surface->close();
    }

    void QtWindow::SetCaption(const OSString &caption)
    {
        win_name=caption;

        if(surface)
            surface->setTitle(QString::fromWCharArray(caption.c_str(),caption.Length()));
    }

    void QtWindow::Show()
    {
        if(surface)
            surface->show();
    }

    void QtWindow::Hide()
    {
        if(surface)
            surface->hide();
    }

    void QtWindow::ToMinWindow()
    {
        if(surface)
            surface->showMinimized();
    }

    void QtWindow::ToMaxWindow()
    {
        if(surface)
            surface->showMaximized();
    }

    void *QtWindow::GetNativeHandle()const
    {
        if(!surface)return(nullptr);

#ifdef _WIN32
        return(void *)surface->winId();         // HWND
#else
        return(nullptr);
#endif//_WIN32
    }

    void *QtWindow::GetNativeDisplay()const
    {
#ifdef _WIN32
        return(void *)GetModuleHandleW(nullptr);
#else
        return(nullptr);
#endif//_WIN32
    }
}//namespace hgl
