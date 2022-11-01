#include "utils.h"

#include <QProcess>
#include <QTextStream>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QDir>

QString Utils::exec(const QString &cmd, QByteArray data) {
    QProcess *process = new QProcess;
    process->start("/bin/bash", QStringList() << "-c" << cmd);

    if (!data.isEmpty()) {
        process->write(data);
        process->waitForBytesWritten();
        process->closeWriteChannel();
    }
    process->waitForFinished();  //等待运行结束，以不阻塞的形式

    QTextStream res(process->readAllStandardOutput());  //命令行执行结果

    process->kill();
    process->close();

    return res.readAll().trimmed();
}

QString Utils::sudo(const QString &cmd, QByteArray data) {
    return Utils::exec("pkexec " + cmd, data);
}

QString Utils::writeFile(const QString &filePath, const QString &text) {
    return Utils::exec("tee " + filePath, text.toUtf8());
}

QString Utils::writeSystemFile(const QString &filePath, const QString &text) {
    return Utils::sudo("tee " + filePath, text.toUtf8());
}

QString Utils::readFile(const QString &filePath) {
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString text = stream.readAll();
    file.close();
    return text;
}
QString Utils::awk(const QString &F,const QString &col) {
    return QString(" | awk -F '%1' '{print $%2}'").arg(F,col);
}
bool Utils::isFileExist(const QString &filePath) {
    QFileInfo fileInfo(filePath);
    return fileInfo.isFile();
}
