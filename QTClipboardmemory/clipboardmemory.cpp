#pragma warning(disable:4996)
#include "clipboardmemory.h"
#include "ui_clipboardmemory.h"
#include "QShowMessage.hpp"
#include <direct.h>
#include <io.h>

ClipBoardMemory::ClipBoardMemory(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClipBoardMemory)
{
    ui->setupUi(this);
    //connect(ui->Previous, &QPushButton::clicked, this, &ClipBoardMemory::on_Previous_clicked);
    //connect(ui->Next, &QPushButton::clicked, this, &ClipBoardMemory::on_Next_clicked);
    //connect(ui->Clear, &QPushButton::clicked, this, &ClipBoardMemory::on_Clear_clicked);

    if (!init())
    {
        
        ShowWarningMessage("This program has insufficient permissions, please ensure sufficient permissions.", "warning");
        exit(0);
    }
}

ClipBoardMemory::~ClipBoardMemory()
{
    delete ui;
    if (m_clpMon != NULL)
    {
        m_clpMon->stop();
        
    }
    if (m_sql != NULL)
    {
        delete m_sql;
        m_sql = NULL;
    }
    if (m_mq != NULL)
    {
        m_mq->stop();
        delete m_mq;
        m_mq = NULL;
    }

    std::remove(m_dbFileName.c_str());
   
}

void ClipBoardMemory::on_Previous_clicked()
{
    if (m_firstButton == true)
    {
        m_index = m_sql->getCurrentId();
    }
    if (m_index > 1)
    {
        if (!m_firstButton)
        {
            m_index--;
        }
    }
    else
    {
        return;
    }

    std::wstring sqlStr = m_sql->getWStringById(m_index);
    QString qString = QString::fromUtf16((const ushort*)sqlStr.c_str());
    ui->Text->setText(qString);
    m_firstButton = false;
}

void ClipBoardMemory::on_Next_clicked()
{
    if (m_firstButton == true)
    {
        m_index = m_sql->getCurrentId();
    }
    if (m_index < m_sql->getCurrentId())
    {
        if (!m_firstButton)
        {
            m_index++;
        }
        
    }
    else
    {
        return;
    }
    std::wstring sqlStr = m_sql->getWStringById(m_index);
    QString qString = QString::fromUtf16((const ushort*)sqlStr.c_str());
    ui->Text->setText(qString);

    m_firstButton = false;
}

void ClipBoardMemory::on_Clear_clicked()
{
    if (!m_sql->clearDatabase())
    {
        ShowWarningMessage("Cleaning database failed!", "warning");
    }
    else
    {
        ShowOKMessage("Cleanup successful", "tips");
    }
}

void ClipBoardMemory::on_Stop_clicked()
{
    m_clpMon->stop();
    ui->Previous->setDisabled(true);
    ui->Next->setDisabled(true);
    ui->Clear->setDisabled(true);
    ui->Stop->setDisabled(true);
    ui->Start->setDisabled(false);

}
void ClipBoardMemory::on_Start_clicked()
{
    m_clpMon->start();
    ui->Previous->setDisabled(false);
    ui->Next->setDisabled(false);
    ui->Clear->setDisabled(false);
    ui->Stop->setDisabled(false);
    ui->Start->setDisabled(true);
}

bool ClipBoardMemory::init()
{
    if (!initDbFileName())
    {
        return false;
    }
    
    if (!m_dbFileName.empty())
    {
        m_sql = new SQLiteWrapper(m_dbFileName);
        if (m_sql == NULL)
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    m_mq = new WatchMQ();
    if (m_mq == NULL || !m_mq->start())
    {
        return false;
    }

    m_clpMon = &ClipboardMonitor::getInstance(m_mq, m_dbFileName, m_sql, ui);
    if (m_clpMon == NULL || !m_clpMon->start())
    {
        return false;
    }
    return true;
    
}

bool ClipBoardMemory::createTempPath()
{
    char strTemp[MAX_PATH];
    GetTempPathA(sizeof(strTemp), strTemp);
    m_tempPath = strTemp + std::string(TEMPPATHNAME);
    if (access(m_tempPath.c_str(), 0) == -1)
    {
        int flag = mkdir(m_tempPath.c_str());
        if (flag == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
    return false;
}


bool ClipBoardMemory::initDbFileName()
{
    if (createTempPath())
    {
        m_dbFileName = m_tempPath + "\\" + DBFILENAME;
        return true;
    }
    return false;
    
}



