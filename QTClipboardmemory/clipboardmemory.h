#ifndef CLIPBOARDMEMORY_H
#define CLIPBOARDMEMORY_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <Windows.h>
#include "WatcherMQ.hpp"
#include "SQLiteWrapper.hpp"
#include "clipboardMonitor.hpp"

#define TEMPPATHNAME   "{25B290C1-989C-443A-AF10-FBE84A8165EC}"
#define DBFILENAME     "clipdb.db"

QT_BEGIN_NAMESPACE
namespace Ui { class ClipBoardMemory; }
QT_END_NAMESPACE

class ClipBoardMemory : public QMainWindow
{
    Q_OBJECT

public:
    ClipBoardMemory(QWidget *parent = nullptr);
    ~ClipBoardMemory();
    bool init();

private:
    bool createTempPath();
    bool initDbFileName();
private slots:
    void on_Previous_clicked();
    void on_Next_clicked();
    void on_Clear_clicked();
    void on_Stop_clicked();
    void on_Start_clicked();

private:
    Ui::ClipBoardMemory *ui;


    std::string m_tempPath;
    std::string  m_dbFileName;
    SQLiteWrapper* m_sql;
    WatchMQ* m_mq;
    ClipboardMonitor* m_clpMon;

    int m_index;
    bool m_firstButton = true;
};
#endif // CLIPBOARDMEMORY_H
