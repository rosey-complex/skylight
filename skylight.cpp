//Qt
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QFileDialog>
#include <QCheckBox>
#include <QObject>

// libc
#include <iostream>
#include <string>
#include <filesystem>

// internal
#include "skylight.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("Skylight");
    QGridLayout *L_Window = new QGridLayout(&window);
    window.setFixedSize(500, 360);

    QLineEdit *LE_File = new QLineEdit;
    L_Window -> addWidget(LE_File, 0, 0);
    QPushButton *BTN_SelFile = new QPushButton("Select File");
    L_Window -> addWidget(BTN_SelFile, 0, 1);
    QPushButton *BTN_Run = new QPushButton("Generate");
    L_Window -> addWidget(BTN_Run, 0, 2);

    QLineEdit *LE_Name = new QLineEdit;
    L_Window -> addWidget(LE_Name, 1, 0);
    LE_Name -> setText("(Your Figure Name Here)");

    QTextEdit *TE_Output = new QTextEdit;
    L_Window -> addWidget(TE_Output, 2, 0, 2, 0);
    
    QFont monofont("Monospace");
    TE_Output -> setFont(monofont);

    TE_Output -> setReadOnly(true);

    QObject::connect(BTN_SelFile, &QPushButton::clicked, [&LE_File, &window] {
        QString filePath = QFileDialog::getOpenFileName(&window, "Select File", QDir::homePath());
        LE_File -> setText(filePath);
    });

    QObject::connect(BTN_Run, &QPushButton::clicked, [&TE_Output, &window, &LE_Name, &LE_File] {
        if (std::filesystem::exists(LE_File -> text().toStdString()))
            {if (std::filesystem::file_size(LE_File -> text().toStdString()) != 1024)
                TE_Output -> setText("Hm... \nThe file doesn't seem quite right\nMake sure you have the right one selected and try again.");
            else
                TE_Output -> setText(QString::fromStdString(getData(LE_File -> text().toStdString(), LE_Name -> text().toStdString())));}
        else TE_Output -> setText("File does not exist or cannot be found.");
    });

    window.show();
    return app.exec();
}