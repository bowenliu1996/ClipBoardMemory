#pragma once
#include <QtWidgets/QMessageBox>
#include <Windows.h>

void ShowWarningMessage(const QString& Text, const QString& Title)
{
	QMessageBox msgBox;
	msgBox.setText(Text);
	msgBox.setWindowTitle(Title);
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.exec();
}

void ShowOKMessage(const QString& Text, const QString& Title)
{
	QMessageBox msgBox;
	msgBox.setText(Text);
	msgBox.setWindowTitle(Title);
	msgBox.setIcon(QMessageBox::Information);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.exec();
}

