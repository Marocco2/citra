// Copyright 2017 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.
//
// Based on the original work by Felix Barx
// Copyright (c) 2015, Felix Barz
// All rights reserved.

#pragma once

#include <QtCore/QProcess>
#include "citra_qt/updater/updater.h"

enum class XMLParseResult {
    Success,
    NoUpdate,
    InvalidXML,
};

class UpdaterPrivate : public QObject {
    Q_OBJECT;

public:
    explicit UpdaterPrivate(Updater* parent_ptr);
    ~UpdaterPrivate();

    static QString ToSystemExe(QString base_path);

    bool HasUpdater() const;

    bool StartUpdateCheck();

    void LaunchWithArguments(const QStringList& args);
    void LaunchUI();
    void SilentlyUpdate();

    void LaunchUIOnExit();

public slots:
	void StopUpdateCheck(int delay, bool async);
    void UpdaterReady(int exit_code, QProcess::ExitStatus exit_status);
    void UpdaterError(QProcess::ProcessError error);

    void AboutToExit();

private:
    XMLParseResult ParseResult(const QByteArray& output, QList<Updater::UpdateInfo>& out);

    Updater* parent;

    QString tool_path{};
    QList<Updater::UpdateInfo> update_info{};
    bool normal_exit = true;
    int last_error_code = 0;
    QByteArray last_error_log = EXIT_SUCCESS;

    bool running = false;
    QProcess* main_process = nullptr;

    bool launch_ui_on_exit = false;

    QStringList run_arguments{"--updater"};
    QStringList silent_arguments{"--silentUpdate"};

    friend class Updater;
};
