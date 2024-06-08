#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include "WatcherMQ.hpp"
#include "SQLiteWrapper.hpp"
#include "ui_clipboardmemory.h"

static WatchMQ* s_mq;
static SQLiteWrapper* s_sql;
static Ui::ClipBoardMemory* s_ui;
static void writeDb(std::wstring str)
{
    if (s_mq != NULL && s_sql!= NULL)
    {
        s_mq->AddMessage(
            [str]
            {
                s_sql->storeWString(str);
            }
        );
    }

}

class ClipboardMonitor 
{

public:

    static ClipboardMonitor& getInstance(WatchMQ* mq, std::string& dbFileName, SQLiteWrapper* sql, Ui::ClipBoardMemory* ui)
    {
        static ClipboardMonitor instance(mq, dbFileName, sql, ui);
        return instance;
    }

    bool start() {
        if (m_running) return true;

        m_running = true;
        m_monitorThread = std::thread(&ClipboardMonitor::run, this);
        if (m_monitorThread.joinable())
        {
            return true;
        }
        return false;
    }

    void stop() {
        if (m_running) {
            m_running = false;
            if (m_hwnd) {
                PostMessage(m_hwnd, WM_CLOSE, 0, 0);
            }
            if (m_monitorThread.joinable()) {
                m_monitorThread.join();
            }
        }
    }

private:
    ClipboardMonitor(WatchMQ* mq, std::string& dbFileName, SQLiteWrapper* sql, Ui::ClipBoardMemory* ui) : m_hwnd(nullptr), m_running(false)
    {
        s_mq = mq;
        s_sql = sql;
        s_ui = ui;
        m_dbFileName = dbFileName;
    }
    ~ClipboardMonitor() 
    {
        
    };
    ClipboardMonitor(const ClipboardMonitor&) = delete;
    ClipboardMonitor& operator=(const ClipboardMonitor&) = delete;

    void run() {
        const wchar_t CLASS_NAME[] = L"ClipboardMonitorClass";

        WNDCLASS wc = {};
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = CLASS_NAME;

        RegisterClass(&wc);

        m_hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            L"Clipboard Monitor",
            0,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            nullptr, nullptr, GetModuleHandle(nullptr), nullptr
        );

        if (m_hwnd == nullptr) {
            std::wcerr << L"Failed to create window." << std::endl;
            m_running = false;
            return;
        }

        if (!AddClipboardFormatListener(m_hwnd)) {
            std::wcerr << L"Failed to add clipboard format listener." << std::endl;
            m_running = false;
            return;
        }

        MSG msg = {};
        while (m_running && GetMessage(&msg, nullptr, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
    }
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
        case WM_CLIPBOARDUPDATE:
            if (OpenClipboard(nullptr)) {
                HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
                if (hClipboardData) {
                    wchar_t* pwchData = static_cast<wchar_t*>(GlobalLock(hClipboardData));
                    if (pwchData) {
                        std::wstring clipboardText(pwchData);
                        GlobalUnlock(hClipboardData);
                        //std::wcout << L"Clipboard text: " << clipboardText << std::endl;

                        writeDb(clipboardText);
                    }
                }
                CloseClipboard();
            }
            break;
        case WM_DESTROY:
            RemoveClipboardFormatListener(hwnd);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
        return 0;
    }
private:

    HWND m_hwnd;
    std::atomic<bool> m_running;
    std::thread m_monitorThread;
    std::string m_dbFileName;

};
