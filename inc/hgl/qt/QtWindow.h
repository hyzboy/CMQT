#pragma once

#include<hgl/platform/Window.h>

class QWindow;

namespace hgl
{
    class QtWindowSurface;   ///< 内部 QWindow 子类（事件源），定义见 QtWindow.cpp

    /**
    * Qt 窗口后端适配：让 hgl::Window 抽象运行在 Qt 提供的 QWindow 之上。
    *
    * 用途：
    *   1. 自建：QtWindow 内部创建一个 QWindow，外部通过 GetQWindow() 放入
    *      QWidget::createWindowContainer 等 Qt 布局。
    *   2. 注入：将 Qt 程序已创建的 QWindow 包装为 hgl::Window（窗口归 Qt 管）。
    *
    * 与原生窗口的差异：
    *   - 事件循环由 Qt（QApplication::exec）驱动：MessageProc() 恒 false，
    *     Update() 不做消息泵，帧循环应由外部（QTimer 等）驱动 WorkManager::Tick/Render。
    *   - Vulkan surface：GetNativeHandle() 返回 QWindow 的 winId()（Win32=HWND），
    *     由 ULRE platform 层查询，无需知道本类。
    */
    class QtWindow:public Window
    {
        QtWindowSurface *surface=nullptr;
        bool owns_surface=true;

    public:

        QtWindow(const OSString &name);
        ~QtWindow() override;

        /** 取内部 QWindow，交给 QWidget::createWindowContainer 嵌入 Qt 布局 */
        QWindow *GetQWindow()const;

        /** 事件注入入口：供内部 QtWindowSurface 及外部适配器将 Qt 事件送入 hgl 事件链 */
        io::EventProcResult SendEvent(const io::EventHeader &header,const uint64 data){return OnEvent(header,data);}

    public: // hgl::Window 接口

        bool Create(uint w,uint h) override;
        bool Create(uint,uint,uint) override{return(false);}     ///< 全屏模式暂不支持
        void Close() override;

        void SetCaption(const OSString &caption) override;

        void Show() override;
        void Hide() override;

        void ToMinWindow() override;
        void ToMaxWindow() override;

        bool MessageProc() override{return(false);}              ///< Qt 事件循环驱动，无需泵消息
        bool WaitMessage() override{return(true);}               ///< 不阻塞（Qt 循环负责挂起）

        bool Update() override{return(!is_close);}               ///< 不做消息泵，仅报告存活

    public: // 平台原生句柄（ULRE platform 层查询）

        void *GetNativeHandle()const override;
        void *GetNativeDisplay()const override;
    };//class QtWindow
}//namespace hgl
